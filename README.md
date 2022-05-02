# Sickomode Portal<br>
[![license mit](https://img.shields.io/badge/license-MIT-green)](LICENSE.md) [![traduzir](https://img.shields.io/badge/Traduzir-pt--BR-brightgreen)](README_ptBR.md) [![traduzir](https://img.shields.io/badge/Translate-en--US-blue)](README.md)<br>

Sickomode is a simple Captive Portal program wich runs on the **ESP8266** dev board.<br>

It is a powerful **Social Engineering** tool wich creates a open WiFi network with custom name/style alluring people to connect to it and enter some credential.<br>
## > DISCLAIMER<br>

The source code given in this repo is for **educational use only**.<br>

Stealing credential **IS ILLEGAL** and can get you in trouble.<br>

I am not liable for any actions on your behalf. This code is given with no warranties and liabilities.<br>

**Just be responsible OK?**<br>
## > Updates and References<br>
I probably won't release any updates unless there's a bug, you can [submit an issue](https://github.com/euMts/Sickomode/issues) in case you found one.<br>I used these two documentations as a reference to build my own, go take a look!<br>
- [ESP8266 First Web Server](https://tttapa.github.io/ESP8266/Chap10%20-%20Simple%20Web%20Server.html) by **tttapa**.<br>
- [ESPBug](https://github.com/willmendil/ESPBug) by **willmendil**.<br>

##### Sickomode is just a name, hope Travis isn't mad at me /o/<br>
## > Demonstration<br>
Here is an example of what would happen if someone connected to the network.<br>
![Imgur1](https://i.imgur.com/KAyL5Cw.gif)<br>

## > Installation<br>
I made a **[youtube video]()** about this project, feel free to ask me questions in the comments if you need to.<br>
### >> Hardware<br>
You will need these components and a way to connect them.<br>
- **FAT32 Micro SD Card**<br>
- **Micro SD Module**<br>
- **ESP8266**<br>

#### Connect the module into the board like this:<br>

| ESP8266 | Micro SD Module |
|:---:|:---:|
| D8 | CS |
| D7 | MOSI |
| D6 | MISO |
| D5 | SCK/clock |
| VIN | VCC |
| GND | GND |
### It should look like this:<br>
![Imgur2](https://i.imgur.com/JHkYb71.png)<br>

---
### >> Software<br>
Install the **[Arduino IDE](https://www.arduino.cc/en/software)**, go to **`File -> Preferences`**, look for the **`Additional Boards Manager URLS`** field and paste this url:
```
https://arduino.esp8266.com/stable/package_esp8266com_index.json
```
Click **`OK`**, and restart the Arduino IDE.<br>

Now you need to install the board, go to **`Tools -> Board:"" -> Boards Manager`** and in the search bar, type:
```
esp8266
```
by **ESP8266 Community**, install the **2.6.0** version.<br>

Now, go to **`Tools -> Manage Libraries`** and in the search bar, type:
```
Dictionary
```
by **Anatoli Arkhipenko**, install the **3.5.0** version.<br>

**Restart the Arduino IDE.**<br>

Now, select **`Generic ESP8266 Module`** on **`Tools -> Board:"" -> ESP8266 Boards (2.6.0)`**.<br>

Download the files with:
```
git clone https://github.com/euMts/Sickomode
```
Format your SD Card to **FAT32** and move the entire content of the **[SD folder](SD)** to it.<br>

Now, in your SD Card, move your custom html page into the **[pages](SD/pages)** folder.<br>Open **[config.json](SD/config.json)** and change the **`ssid`** and **`page`** values.<br>
Safely remove the SD Card from your computer and plug it into the module **before** turning the board on.<br>

Open **[captive_portal.ino](captive_portal/captive_portal.ino)** with the **[Arduino IDE](https://www.arduino.cc/en/software)** and upload the code into your board.<br>

Wait until load and then you're good to go! now you should see the WiFi network with the name that you previously set up on **[config.json](SD/config.json)**.<br>

```Obs. The code will ignore the json file in case its corrupted or malformed. The default value for the SSID is 'Captive Portal'.```<br>

The captured data will be stored on the SD Card inside the **[data.txt](SD/data.txt)** file.<br>


## > Custom Webpages<br>
You can put **any** html file inside the **[pages](SD/pages)** folder and refer to it on the **`page`** variable inside **[config.json](SD/config.json)**.<br>
The requirements for the html file to work are:<br>
- Have a form that send the data by **POST** request to **`/login`**, the request must have an **`username`** and **`password`**.<br>
- All the code must be inside the **.html** file, including **`<script>`** and **`<style>`**.<br>
- You must replace all the **`"`** (double quotes) with **`'`** (single quote).<br>

## > To Do List<br>
- [ ] - Publish the binary file on the [releases page](https://github.com/euMts/Sickomode/releases).<br>
- [ ] - Build a portal to control the board with any device.<br>
- [ ] - Build a function to controll the LED in case we want to see whats goin on.<br>
- [ ] - Make FTP server.<br>
## > License
**[MIT License](LICENSE.md)**<br>**[My Website](https://www.matheus-eduardo.com.br)**<br>

---
Made by **Matheus Eduardo**👋