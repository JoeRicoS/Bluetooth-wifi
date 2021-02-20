#include "WiFi.h"
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "blue.h"

char auth[] = "";
int butStatus = 0, lastbutStatus = 0;
int bloque = 1, frmnt = 1;
blue blue;
WidgetLCD lcd(V0);
BlynkTimer timer;
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if (bloque) butStatus = pinValue;
  else Blynk.virtualWrite(V1, 0);
  Serial.println(pinValue);
}


void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  blue.begin("Projet_fenetre");
  blue.saisie_wifi();
  Blynk.config(auth);
  lcd.clear(); //Use it to clear the LCD Widget

}

void loop()
{
  if (Serial2.available()) {
    String Info1 = Serial2.readString();
    if (Info1.indexOf("bloque") == 0) {
      bloque = !bloque;
    }
    if (Info1.indexOf("ouvert") == 0) {
      blue.ecrire("Fenetre est ouvert");
      lcd.clear();
      lcd.print(0, 0, "Etat :");
      lcd.print(5, 1, "ouvert");
    }
  }
  Blynk.run();  //with internet
  butStatus = blue.button_bluetooth( butStatus); // with bluetooth
  if ((bloque == 0) && (frmnt == 1)) frmnt = 0;
  if ((bloque == 1) && (frmnt == 0)) {
    frmnt = 1;
    butStatus = 0;
    Serial.println(butStatus);
    blue.ecrire("Fenetre est fermee");
    lcd.clear();
    lcd.print(0, 0, "Etat :");
    lcd.print(5, 1, "fermee");
    Blynk.virtualWrite(V1, butStatus);
  }
  if (bloque) {
    if (lastbutStatus != butStatus) {
      Blynk.virtualWrite(V1, butStatus);
      if (butStatus == 1) {
        blue.ecrire("En train d'ouvrir");
        lcd.clear();
        lcd.print(0, 0, "Etat :");
        lcd.print(3, 1, "ouverture");
        Serial2.println("ouvrir");
        Serial.println("ouvrir");
      } else {
        blue.ecrire("En train de fermer");
        lcd.clear();
        lcd.print(0, 0, "Etat :");
        lcd.print(3, 1, "Fermeture");
        Serial2.println("fermer");
        Serial.println("fermer");
      }
    }
    lastbutStatus = butStatus;
  }
}
