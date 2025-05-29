#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// Wi-Fi
const char* ssid = "x";
const char* password = "x";

// MQTT
const char* mqtt_server = "broker.hivemq.com";
WiFiClient espClient;
PubSubClient client(espClient);

// DHT22
#define DHTPIN D5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// LCD I2C
LiquidCrystal_I2C lcd(0x27, 20, 4);

// ADS1115
Adafruit_ADS1115 ads;

// Variáveis de tempo
long lastMsg = 0;
char msg[50];

void setup_wifi() {
  delay(100);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP8266Client")) {
      client.subscribe("casa/sensores/#");
    } else {
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  Wire.begin();
  ads.begin();
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Monitorando...");
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;

    float temp = dht.readTemperature();
    float umid = dht.readHumidity();
    int mq135 = ads.readADC_SingleEnded(0);  // Qualidade do ar
    int tds = ads.readADC_SingleEnded(1);    // TDS

    // MQTT
    if (!isnan(temp)) {
      snprintf(msg, sizeof(msg), "%.2f", temp);
      client.publish("casa/sensores/temperatura", msg);
    }

    if (!isnan(umid)) {
      snprintf(msg, sizeof(msg), "%.2f", umid);
      client.publish("casa/sensores/umidade", msg);
    }

    snprintf(msg, sizeof(msg), "%d", mq135);
    client.publish("casa/sensores/ar", msg);

    snprintf(msg, sizeof(msg), "%d", tds);
    client.publish("casa/sensores/tds", msg);

    // LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp, 1);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Umid: ");
    lcd.print(umid, 1);
    lcd.print(" %");

    lcd.setCursor(0, 2);
    lcd.print("Ar: ");
    lcd.print(mq135);

    lcd.setCursor(0, 3);
    lcd.print("TDS: ");
    lcd.print(tds);
  }
}
