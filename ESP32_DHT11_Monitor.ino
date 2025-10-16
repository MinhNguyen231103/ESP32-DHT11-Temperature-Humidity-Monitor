#include <WiFi.h>
#include "DHT.h"

// ---------------- Cấu hình DHT ----------------
#define DHTPIN 4          // Chân DATA của DHT11 nối ESP32 GPIO4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ---------------- Cấu hình WiFi ----------------
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// ---------------- WebServer ----------------
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();

  Serial.println("Đang kết nối WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nĐã kết nối WiFi!");
  Serial.print("Địa chỉ IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  Serial.println("Client mới kết nối");
  String request = client.readStringUntil('\r');
  client.flush();

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    client.println("HTTP/1.1 500 Internal Server Error");
    client.println("Content-Type: text/plain");
    client.println();
    client.println("Lỗi đọc cảm biến DHT11!");
    return;
  }

  // HTML đơn giản hiển thị nhiệt độ & độ ẩm
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><meta http-equiv='refresh' content='5'/>"
                "<title>ESP32 DHT11 Monitor</title>"
                "<style>body{font-family:Arial;text-align:center;background:#f2f2f2;padding:20px;}div{background:#fff;padding:20px;border-radius:15px;display:inline-block;}</style>"
                "</head><body><h2>ESP32 - DHT11 Temperature & Humidity</h2><div>"
                "<h3>🌡 Nhiệt độ: " + String(t) + " °C</h3>"
                "<h3>💧 Độ ẩm: " + String(h) + " %</h3>"
                "<p>Cập nhật mỗi 5 giây</p>"
                "</div></body></html>";

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(html);
  delay(100);
}
