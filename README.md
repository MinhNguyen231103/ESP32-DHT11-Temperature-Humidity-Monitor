🌡 ESP32 DHT11 Temperature & Humidity Monitor

📖 Giới thiệu
Dự án này sử dụng **ESP32** và **cảm biến DHT11** để theo dõi nhiệt độ và độ ẩm, đồng thời hiển thị dữ liệu trực tiếp trên **WebServer nội bộ**.

Khi ESP32 kết nối WiFi, bạn có thể truy cập trang web hiển thị dữ liệu bằng **địa chỉ IP của ESP32** (hiển thị trên Serial Monitor).

---

## ⚙️ Phần cứng
| Thành phần| Mô tả                     | Ghi chú                    |
|-----------|---------------------------|----------------------------|
| ESP32     | Board xử lý chính         | DevKit v1 hoặc tương đương |
| DHT11     | Cảm biến nhiệt độ & độ ẩm | 3 chân: VCC, DATA, GND     |
| Dây nối   | Jumper male-male          |                            |

### 🪛 Sơ đồ nối chân
| DHT11 | ESP32 |
|--------|--------|
| VCC | 3.3V |
| GND | GND |
| DATA | GPIO4 |

---

## 💻 Phần mềm
- Arduino IDE (>= 1.8.13)
- Thư viện:
  - DHT sensor library (by Adafruit)
  - Adafruit Unified Sensor
  - WiFi (có sẵn trong ESP32 core)

---
