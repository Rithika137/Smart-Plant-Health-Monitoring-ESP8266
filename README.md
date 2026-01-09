# Smart Plant Health Monitoring System

An IoT-based plant health monitoring system that measures temperature, humidity, and soil moisture in real time and displays the data on a black-themed web dashboard hosted by ESP8266.

---

## 🔍 Project Overview

This system continuously monitors plant conditions using sensors and provides live updates through a responsive web interface. It helps in deciding irrigation timing and identifying plant health status remotely.

---

## ✨ Features

- Real-time temperature monitoring using DHT11
- Live humidity measurement
- Soil moisture sensing
- Automatic plant health status indication
- Black-themed responsive web dashboard
- ESP8266-hosted local web server
- Auto-refresh data every 2 seconds

---

## 🧰 Hardware Components

- ESP8266 (NodeMCU)
- DHT11 Temperature & Humidity Sensor
- Soil Moisture Sensor
- Jumper wires
- Breadboard

---

## 💻 Software Used

- Arduino IDE
- ESP8266 Board Package
- Adafruit DHT Sensor Library
- HTML, CSS, JavaScript (embedded)

---

## ⚙️ Working Principle

1. ESP8266 reads temperature and humidity from DHT11.
2. Soil moisture value is read via analog pin.
3. ESP8266 hosts a web server on port 80.
4. Sensor data is sent as JSON using HTTP.
5. Web dashboard fetches data every 2 seconds and updates UI.
6. Plant health status is determined based on soil moisture threshold.

---

## 🌐 Web Dashboard

Displayed parameters:
- 🌡 Temperature (°C)
- 💧 Humidity (%)
- 🌱 Soil Moisture (raw units)
- 🚿 Irrigation Timing
- 📊 Plant Health Status

Dashboard uses a **black neon UI** for better visibility and aesthetics.

---

## 🧪 Sample Output

### Serial Monitor

Connected to WiFi
IP Address: 192.168.28.3
Temperature: 29 °C
Humidity: 71 %
Soil Moisture: 664
Plant Status: Healthy


### Web Output
- Temperature: 29 °C
- Humidity: 71 %
- Soil Moisture: 664 units
- Status: Healthy

---

## 📌 Applications

- Smart agriculture
- Home gardening
- Greenhouse monitoring
- IoT-based automation systems

---

## 🚀 Future Enhancements

- Automatic irrigation using relay & motor
- Cloud data logging
- Mobile app integration
- Graphical analytics

---

## 👩‍💻 Author

**Rithika**  
Electronics and Instrumentation Engineering  
IoT Project using ESP8266

---

## 📜 License

This project is open-source and free to use for academic purposes.

