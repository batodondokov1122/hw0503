#if defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <WiFiUdp.h>
#include <ArtnetWifi.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

//вариант, если работаешь с одной светодиодной палкой
const bool apMode = true;             // если apMode = true,то наш контроллер - сервер, он раздает вайфай; если apMode = false, то контроллер подключается к внешней точке доступа
const String apName = "Lamp";         //имя точки доступа (работает, если apMode = true)
const char WiFiAPPSK[] = "jj454545";  //пароль (работает, если apMode = true)

// Wifi settings - настройка внешней точки доступа, если apMode = false
const char* ssid = "402";            //имя внешней точки доступа
const char* password = "402402402";  //пароль внешней точки дотупа

const bool DHCP = true;  //автоматическое назначение IP адресов, если true, то IP выдает внешний модем, его можно узнать через монитор com порта в IDE (115200)
// Set your Static IP if DHCP = false
IPAddress ip(192, 168, 1, 180);      // 2, 0, 0, 10
IPAddress gateway(192, 168, 1, 1);   // 2, 0, 0, 1
IPAddress subnet(255, 255, 255, 0);  // 255, 0, 0, 0

// LED settings
const int numLeds = 14;                   // CHANGE FOR YOUR SETUP
const int numberOfChannels = numLeds * 3 +1;  // Total number of channels you want to receive (1 led = 3 channels)
const byte DATA_PIN = D4;
CRGB leds[numLeds];

// Art-Net settings
ArtnetWifi artnet;
const int startUniverse = 0;  // CHANGE FOR YOUR SETUP most software this is 1, some software send out artnet first universe as 0.

// Check if we got all universes
const int maxUniverses = numberOfChannels / 512 + ((numberOfChannels % 512) ? 1 : 0);
bool universesReceived[maxUniverses];
bool sendFrame = 1;
int previousDataLength = 0;


void ConnectWifi() {
  WiFi.setSleepMode(WIFI_NONE_SLEEP);

  if (apMode) {
    WiFi.mode(WIFI_AP);
    // Do a little work to get a unique-ish name. Append the last two bytes of the MAC (HEX'd) to "Thing-":
    uint8_t mac[WL_MAC_ADDR_LENGTH];
    WiFi.softAPmacAddress(mac);
    String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
    macID.toUpperCase();
    String AP_NameString = apName + " " + macID;
    char AP_NameChar[AP_NameString.length() + 1];
    memset(AP_NameChar, 0, AP_NameString.length() + 1);
    for (int i = 0; i < AP_NameString.length(); i++) {
      AP_NameChar[i] = AP_NameString.charAt(i);
    }
    WiFi.softAP(AP_NameChar, WiFiAPPSK);
    Serial.println();
    Serial.printf("Wi-Fi access point: %s\n", AP_NameChar);
    Serial.print("IP adress: 192.168.4.1");
  } else {
    if (!DHCP) {
      WiFi.config(ip, gateway, subnet);
    }
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    boolean hasConnected = true;
    int i = 0;
    Serial.println();
    Serial.print("Connecting to ");
    Serial.print(ssid);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      if (i > 20) {
        hasConnected = false;
        break;
      }
      i++;
    }
    Serial.println();
    if (hasConnected) {
      Serial.print("Connected! IP address: ");
      Serial.print(WiFi.localIP());
    } else {
      Serial.println("Connection failed IP address!");
    }
  }
}

void initTest() {
  for (int i = 0; i < numLeds; i++) {
    leds[i] = CRGB(127, 0, 0);
  }
  FastLED.show();
  delay(500);
  for (int i = 0; i < numLeds; i++) {
    leds[i] = CRGB(0, 127, 0);
  }
  FastLED.show();
  delay(500);
  for (int i = 0; i < numLeds; i++) {
    leds[i] = CRGB(0, 0, 127);
  }
  FastLED.show();
  delay(500);
  for (int i = 0; i < numLeds; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data) {
  sendFrame = 1;
  // set brightness of the whole strip
  FastLED.setBrightness(data[42]);
  FastLED.show();

  // Store which universe has got in
  if ((universe - startUniverse) < maxUniverses) {
    universesReceived[universe - startUniverse] = 1;
  }

  for (int i = 0; i < maxUniverses; i++) {
    if (universesReceived[i] == 0) {
      //Serial.println("Broke");
      sendFrame = 0;
      break;
    }
  }

  // read universe and put into the right part of the display buffer
  for (int i = 0; i < length / 3; i++) {
    Serial.println(length);
    int led = i + (universe - startUniverse) * (previousDataLength / 3);
    if (led < numLeds)
      leds[led] = CRGB(data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
//    Serial.println(leds[led]);
  }
  previousDataLength = length;

  if (sendFrame) {
    FastLED.show();
    // Reset universeReceived to 0
    memset(universesReceived, 0, maxUniverses);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Setup whith ");
  Serial.print(maxUniverses);
  if (maxUniverses > 1) Serial.print(" universes");
  else Serial.print(" universe");
  ConnectWifi();
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, numLeds).setCorrection(TypicalLEDStrip);
  initTest();
  Serial.println("Test passed");
  artnet.begin();
  // this will be called for each packet received
  artnet.setArtDmxCallback(onDmxFrame);
}

void loop() {
  // we call the read function inside the loop
  artnet.read();
}
