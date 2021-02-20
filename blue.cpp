
#include "blue.h"

void blue::begin(String aa) {
  SerialBT.begin(aa);
}

void blue::scanWifiNets() {
  n = WiFi.scanNetworks();
  SerialBT.println("scan done");
  if (n > 10) n == 48;
  if (n != 0) {
    for (int i = 0; i < n; i++) {
      scan[i] = String(WiFi.SSID(i));
      SerialBT.println(String(i) + " : " + scan[i] + " " + String(WiFi.RSSI(i)));
    }
  }
}

void blue::wificonnect() {
  SerialBT.println();
  SerialBT.println("Connecting to ");
  SerialBT.println(ssid);
  SerialBT.println("[SSID: *" + ssid + "*, PASSWORD: *" + pass + "*]");
  WiFi.begin(ssid.c_str(), pass.c_str());
  int tentative = 0;
  entrainDeSeconnecter = "Connect";
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    SerialBT.println(".");
    tentative = tentative + 1;
    if (tentative > 40) {
      entrainDeSeconnecter = "echecConnect";
      break;
    }
  }
  SerialBT.println("");
  if (entrainDeSeconnecter != "echecConnect") {
    entrainDeSeconnecter = "succesConnect";
    SerialBT.println("IP address: ");
    SerialBT.println(WiFi.localIP());
  }
  SerialBT.println("status: " + entrainDeSeconnecter);
}

void blue::saisie_wifi() {
  Info = "";
  if (a == 0) {
    while (Info.indexOf("scan") != 0) {
      if (SerialBT.available()) {
        Info = SerialBT.readString();
        a = 1;
      }
    }
  }
  while (entrainDeSeconnecter == "echecConnect") {
    SerialBT.println("En train de scan");
    scanWifiNets();

    SerialBT.println("Tapez le numero de votre WIFI");
    Info = "";
    while (Info == "") {
      if (SerialBT.available()) {
        Info = SerialBT.readString();
        ssid = scan[Info.toInt()];
        SerialBT.println(ssid);
      }
    }
    if (Info.indexOf("scan") != 0) {
      SerialBT.println("Tapez le PASSWORD");
      Info = "";
      while (Info == "") {
        if (SerialBT.available()) {
          Info = SerialBT.readString();
          pass = Info.substring(0, Info.length() - 2);
          SerialBT.println(pass);
        }
      }
      wificonnect();
    }
  }
}

int blue::button_bluetooth(int butStatus1) {
  if (SerialBT.available()) {
    Info = SerialBT.readString();
    Serial.println(Info);
    if (Info.substring(0, Info.length() - 2)== "butt") {
      butStatus1 = !butStatus1;
    }
    if (Info.indexOf("scan") == 0) {
      Serial.println("ok");
      entrainDeSeconnecter = "echecConnect";
      saisie_wifi();
    }
	if (Info.indexOf("rst") == 0) {
      Serial.println("ok1");
      ESP.restart();
    }
  }
  return butStatus1;
}

void blue::ecrire(String aa){
	SerialBT.println(aa);
}
