#include <WiFi.h>
#include <WebServer.h>

#define THRESHOLD 5.0

const char* ssid = "inissid";
const char* password = "inipassword";

WebServer server(80);

const int trigPins[3] = {5, 19, 22};
const int echoPins[3] = {18, 21, 23};

float lastS1 = 0, lastS2 = 0, lastS3 = 0, lastMedian = 0, lastOutput = 0;

void setup() {
  Serial.begin(115200);

  for(int i = 0; i < 3; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
  }

  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Terkoneksi! IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/data", HTTP_GET, []() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    String json = "{";
    json += "\"s1\":" + String(lastS1) + ",";
    json += "\"s2\":" + String(lastS2) + ",";
    json += "\"s3\":" + String(lastS3) + ",";
    json += "\"median\":" + String(lastMedian) + ",";
    json += "\"output\":" + String(lastOutput);
    json += "}";
    server.send(200, "application/json", json);
    Serial.println("Data dikirim ke HTML");
  });

  server.begin();
}

float getDistance(int index) {
  digitalWrite(trigPins[index], LOW);
  delayMicroseconds(2);
  digitalWrite(trigPins[index], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPins[index], LOW);
  
  long dur = pulseIn(echoPins[index], HIGH, 30000);
  
  if(dur == 0) {
    return -1.0;
  }
  
  return dur / 58.0;
}

void sortArray(float a[], int size) {
  for(int i = 0; i < (size - 1); i++) {
    for(int o = 0; o < (size - (i + 1)); o++) {
      if(a[o] > a[o + 1]) {
        float t = a[o];
        a[o] = a[o + 1];
        a[o + 1] = t;
      }
    }
  }
}

void loop() {
  server.handleClient();

  static unsigned long lastUpdate = 0;
  if(millis() - lastUpdate >= 1000) {
    lastUpdate = millis();

    float distances[3];
    for(int i = 0; i < 3; i++) {
      distances[i] = getDistance(i);
      delay(30);
    }

    lastS1 = distances[0];
    lastS2 = distances[1];
    lastS3 = distances[2];

    float sorted[3];
    for(int i = 0; i < 3; i++) {
      sorted[i] = distances[i];
    }

    sortArray(sorted, 3);
    lastMedian = sorted[1];

    float sum = 0;
    int validCount = 0;

    for(int i = 0; i < 3; i++) {
      if(distances[i] != -1.0 && abs(distances[i] - lastMedian) <= THRESHOLD) {
        sum += distances[i];
        validCount++;
      }
    }

    if(validCount > 0) {
      lastOutput = sum / validCount;
    } else {
      lastOutput = -1.0;
    }

    Serial.print("S1:"); Serial.print(lastS1); Serial.print(" ");
    Serial.print("S2:"); Serial.print(lastS2); Serial.print(" ");
    Serial.print("S3:"); Serial.print(lastS3); Serial.print(" ");
    Serial.print("Median:"); Serial.print(lastMedian); Serial.print(" ");
    Serial.print("Output:"); Serial.println(lastOutput);
  }
}
