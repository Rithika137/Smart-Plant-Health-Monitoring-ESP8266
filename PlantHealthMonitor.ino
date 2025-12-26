#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

/* -------- WiFi -------- */
const char* ssid = "R";
const char* password = "rithhh4726";

/* -------- DHT -------- */
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

/* -------- Soil Sensor -------- */
#define SOIL_PIN A0
#define SOIL_THRESHOLD 500   // adjust after testing

ESP8266WebServer server(80);

/* -------- HTML Dashboard -------- */
String webpage = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>Smart Plant Health Monitoring</title>
<meta name="viewport" content="width=device-width, initial-scale=1">

<style>
body{
  margin:0;
  font-family: 'Segoe UI', sans-serif;
  background: radial-gradient(circle at top, #0f1b2e, #050b17);
  color:#fff;
  text-align:center;
}
h1{
  margin:30px 0;
  color:#3fc1ff;
}
.container{
  display:grid;
  grid-template-columns: repeat(auto-fit, minmax(220px,1fr));
  gap:25px;
  max-width:900px;
  margin:auto;
  padding:20px;
}
.card{
  background: #050d1f;
  border-radius:20px;
  padding:25px;
  box-shadow: 0 0 25px rgba(0,170,255,0.15);
}
.card h2{
  font-size:18px;
  color:#7ad7ff;
}
.value{
  font-size:28px;
  margin-top:10px;
}
.status{
  margin:30px auto;
  width:300px;
}
.footer{
  margin-top:40px;
  font-size:14px;
  color:#aaa;
}
.healthy{ color:#00ff9c; }
.unhealthy{ color:#ff4d4d; }
</style>
</head>

<body>
<h1>🌱 Smart Plant Health Monitoring</h1>

<div class="container">
  <div class="card">
    <h2>🌡 Temperature</h2>
    <div class="value" id="temp">-- °C</div>
  </div>

  <div class="card">
    <h2>💧 Humidity</h2>
    <div class="value" id="hum">-- %</div>
  </div>

  <div class="card">
    <h2>🌱 Soil Moisture</h2>
    <div class="value" id="soil">--</div>
  </div>

  <div class="card">
    <h2>🚿 Irrigation Timing</h2>
    <div class="value">06:00 AM – 06:15 AM</div>
  </div>
</div>

<div class="card status">
  <h2>📊 Plant Status</h2>
  <div class="value" id="status">--</div>
</div>

<div class="footer">
  IoT Based Plant Monitoring System | ESP8266
</div>

<script>
async function getData(){
  const res = await fetch("/data");
  const d = await res.json();

  document.getElementById("temp").innerHTML = d.temp + " °C";
  document.getElementById("hum").innerHTML = d.hum + " %";
  document.getElementById("soil").innerHTML = d.soil + " units";

  const status = document.getElementById("status");
  if(d.healthy){
    status.innerHTML = "Healthy";
    status.className = "value healthy";
  }else{
    status.innerHTML = "Needs Irrigation";
    status.className = "value unhealthy";
  }
}
setInterval(getData,2000);
getData();
</script>

</body>
</html>
)rawliteral";

/* -------- Setup -------- */
void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());

  server.on("/", [](){ server.send(200,"text/html",webpage); });
  server.on("/data", sendData);

  server.begin();
}

/* -------- Loop -------- */
void loop() {
  server.handleClient();
}

/* -------- Sensor Data -------- */
void sendData(){
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int soil = analogRead(SOIL_PIN);

  bool healthy = (soil > SOIL_THRESHOLD);

  String json = "{";
  json += "\"temp\":" + String(t,1) + ",";
  json += "\"hum\":" + String(h,1) + ",";
  json += "\"soil\":" + String(soil) + ",";
  json += "\"healthy\":" + String(healthy ? "true":"false");
  json += "}";

  server.send(200,"application/json",json);
}
