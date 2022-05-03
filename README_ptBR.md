# Sickomode Portal<br>
[![license mit](https://img.shields.io/badge/license-MIT-green)](LICENSE.md) [![traduzir](https://img.shields.io/badge/Traduzir-pt--BR-brightgreen)](README_ptBR.md) [![traduzir](https://img.shields.io/badge/Translate-en--US-blue)](README.md)<br>

Sickomode é um Captive Portal simples que roda na placa **ESP8266**.<br>

É uma poderosa ferramenta de **Engenharia Social** que cria uma rede WiFi aberta com nome/estilo personalizado, atraindo as pessoas a se conectarem e inserirem alguma credencial.<br>

## > AVISO LEGAL<br>

O código fonte disponibilizado neste repositório é **apenas para uso educacional**.<br>

Roubar credenciais **É ILEGAL** e pode causar problemas.<br>

Eu **não sou responsável** por quaisquer ações em seu nome. Este código é fornecido sem garantias e responsabilidades.<br>

**Seja responsável OK?**<br>
## > Atualizações e Referências<br>
Eu provavelmente não vou lançar nenhuma atualização a não ser que encontre um bug, você pode [reportar um problema](https://github.com/euMts/Sickomode/issues) caso encontre um.<br>Eu utilizei estas duas documentações como referência para desenvolver a minha própria, dê uma olhada!<br>
- [ESP8266 First Web Server](https://tttapa.github.io/ESP8266/Chap10%20-%20Simple%20Web%20Server.html) by **tttapa**.<br>
- [ESPBug](https://github.com/willmendil/ESPBug) by **willmendil**.<br>

##### Sickomode é apenas um nome, espero que Travis Scott não fique bravo comigo /o/<br>
## > Demonstação<br>
Aqui está um exemplo do que aconteceria caso alguém se conectasse a rede WiFi:<br>
![Imgur1](https://i.imgur.com/KAyL5Cw.gif)<br>

## > Instalação<br>
Eu fiz um **[video no youtube]()** a respeito deste projeto, sinta-se a vontade para me mandar perguntas nos comentários caso haja necessidade.<br>
### >> Hardware<br>
Você precisará destes componentes e de uma forma de conectá-los:<br>
- **Cartão Micro SD FAT32**<br>
- **Módulo Micro SD**<br>
- **ESP8266**<br>

#### Conecte o módulo na placa desta forma:<br>

| ESP8266 | Módulo Micro SD |
|:---:|:---:|
| D8 | CS |
| D7 | MOSI |
| D6 | MISO |
| D5 | SCK/clock |
| VIN | VCC |
| GND | GND |
### Deve ficar mais ou menos assim:<br>
![Imgur2](https://i.imgur.com/JHkYb71.png)<br>

---
### >> Software<br>
Installe o **[Arduino IDE](https://www.arduino.cc/en/software)**, vá para **`Arquivo-> Preferências`**, procure pelo campo **`Urls Adicionais para Gerenciadores de Placas`** e insira esta URL:
```
https://arduino.esp8266.com/stable/package_esp8266com_index.json
```
Clique **`OK`**, e reinicie a Arduino IDE.<br>

Agora precisamos instalar a placa, vá para **`Ferramentas -> Placa:"" -> Gerenciador de Placas`** e na barra de pesquisa escreva:
```
esp8266
```
by **ESP8266 Community**, instale a versão **2.6.0** .<br>

Agora, vá para **`Ferramentas -> Gerenciar Bibliotecas`** e pesquise por:
```
Dictionary
```
by **Anatoli Arkhipenko**, instale a versão **3.5.0**.<br>

**Reinicie a Arduino IDE.**<br>

Agora, selecione **`Generic ESP8266 Module`** em **`Ferramentas -> Placa:"" -> ESP8266 Boards (2.6.0)`**.<br>

Baixe os arquivos com:
```
git clone https://github.com/euMts/Sickomode
```
Formate o Cartão SD em **FAT32** e mova todo o conteúdo da **[pasta SD](SD)** para ele.<br>

Agora, no seu Cartão SD, mova sua **[página html personalizada](https://github.com/euMts/Sickomode/blob/main/README_ptBR.md#-html-personalizado)** para a pasta **[pages](SD/pages)**.<br>Abra **[config.json](SD/config.json)** e mude o valor de **`ssid`** e **`page`**.<br>
Remova o Cartão SD com segurança e coloque-o no Módulo **antes** de ligar a placa.<br>

Abra o arquivo **[captive_portal.ino](captive_portal/captive_portal.ino)** com a **[Arduino IDE](https://www.arduino.cc/en/software)** e carregue o código para a placa.<br>

Espere carregar e está pronto! Agora você deve ver a rede WiFi com o nome que você definiu anteriormente em **[config.json](SD/config.json)**.<br>

```Obs. O código irá ignorar o arquivo json caso ele esteja corrompido ou mal escrito, o valor padrão do ssid é 'Captive Portal'.```<br>

Os dados capturados serão salvos no seu Cartão SD dentro do arquivo **[data.txt](SD/data.txt)**.<br>


## > Html Personalizado<br>
Você pode colocar **qualquer** arquivo html dentro da pasta **[pages](SD/pages)** e referenciá-lo na variável **`page`** dentro de **[config.json](SD/config.json)**.<br>
Os requisitos para que o arquivo html funcione são:<br>
- Ter um formulário que envie uma requisição **POST** para **`/login`**, a requisição deve conter os campos **`username`** e **`password`**.<br>
- Todo o código deve estar dentro do arquivo **.html** incluindo **`<script>`** e **`<style>`**.<br>
- Você deve substituir  **`"`** (aspas duplas) por **`'`** (aspas simples).<br>

## > Lista de Afazeres<br>
- [x] - Publicar o arquivo binário na [página de releases](https://github.com/euMts/Sickomode/releases).<br>
- [ ] - Construir uma página para controlar o programa a partir de qualquer dispositivo.<br>
- [ ] - Criar uma função que controla a LED caso queira ver o que está acontecendo.<br>
- [ ] - Fazer um servidor FTP.<br>
## > Licença
**[Licença MIT](LICENSE.md)**<br>**[Meu Website](https://www.matheus-eduardo.com.br)**<br>

---
Feito por **Matheus Eduardo**👋
