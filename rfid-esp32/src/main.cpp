#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// ======= CONFIG =======
const char* ssid = "Galaxy A15 5G DA3D";
const char* password = "u2umwcci44u2d9j";

// Backend server URL (your PC IP + port 3000)
const char* backendURL = "http://192.168.58.101:3000";

// Blockchain node RPC URL (usually your local node)
const char* rpcURL = "http://192.168.58.101:8545";

// Simulated RFID tags
String tagIds[] = {"123456789", "987654321", "555555555"};
int currentTag = 0;

// ======= FUNCTIONS =======

// Send signed tx to blockchain node RPC
bool sendSignedTransaction(String signedTx) {
  HTTPClient http;
  http.begin(rpcURL);
  http.addHeader("Content-Type", "application/json");

  StaticJsonDocument<512> jsonDoc;
  jsonDoc["jsonrpc"] = "2.0";
  jsonDoc["method"] = "eth_sendRawTransaction";
  JsonArray params = jsonDoc.createNestedArray("params");
  params.add(signedTx);
  jsonDoc["id"] = 1;

  String requestBody;
  serializeJson(jsonDoc, requestBody);

  int httpCode = http.POST(requestBody);
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println("Broadcast Response: " + payload);
    http.end();
    return true;
  } else {
    Serial.println("Failed to send transaction");
    http.end();
    return false;
  }
}

// Verify tag via backend
bool verifyTag(String tagId) {
  HTTPClient http;
  String url = String(backendURL) + "/verify/" + tagId;
  http.begin(url);

  int httpCode = http.GET();
  if (httpCode == 200) {
    String payload = http.getString();
    Serial.println("Verify Response: " + payload);

    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, payload);
    if (!error && doc.containsKey("exists")) {
      http.end();
      return doc["exists"];
    }
  }
  Serial.println("Verification failed");
  http.end();
  return false;
}

// Get signed transaction from backend for a given tagId
String getSignedTx(String tagId) {
  HTTPClient http;
  String url = String(backendURL) + "/getTx/" + tagId;
  http.begin(url);

  int httpCode = http.GET();
  if (httpCode == 200) {
    String payload = http.getString();
    Serial.println("GetTx Response: " + payload);

    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, payload);
    if (!error && doc.containsKey("signedTx")) {
      String tx = doc["signedTx"].as<String>();
      http.end();
      return tx;
    }
  } else {
    //Serial.printf("Failed to get signed transaction. HTTP code: %d\n", httpCode);
  }
  http.end();
  return "";
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
}

void loop() {
  String tagId = tagIds[currentTag];
  Serial.println("\n=== Simulating tag scan: " + tagId + " ===");

  // 1) Request signed transaction from backend
  String signedTx = getSignedTx(tagId);

  if (signedTx != "") {
    // 2) Broadcast signed transaction to blockchain node
    if (sendSignedTransaction(signedTx)) {
      Serial.println("Transaction sent!");
    }
  } else {
    //Serial.println("No signed transaction for this tag");
  }

  // 3) Verify tag via backend
  bool exists = verifyTag(tagId);
  if (exists) {
    Serial.println("✅ Right Drug");
  } else {
    Serial.println("❌ Counterfeit Drug");
  }

  // Cycle to next tag
  currentTag = (currentTag + 1) % (sizeof(tagIds) / sizeof(tagIds[0]));

  delay(10000); // wait 20 seconds before next simulated scan
}
