#include "WiFi.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif




class blue
{
  private:
    String ssid = "";
    String pass = "";
    String entrainDeSeconnecter = "echecConnect";
    int n;
    int a=0;
    String Info = "";
    String scan[50];
    void wificonnect();
    void scanWifiNets();
    
BluetoothSerial SerialBT;
  public:
    void begin(String aa);
    void saisie_wifi();
    int button_bluetooth(int butStatus1);
	void ecrire(String aa);
};