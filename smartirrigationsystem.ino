#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <DHT.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd( 0x3f,16,2);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial1

// or Software Serial on Uno, Nano...
//#include <SoftwareSerial.h>
//SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

#define DHTPIN 2          // What digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
BlynkTimer timer1;
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  lcd.setCursor(0,0);
  lcd.print("Temperature=");
  lcd.print(t);
  lcd.print(" C");
  delay(500);
  lcd.setCursor(1,0);
  lcd.print("humidity=");
  lcd.print(h);
  lcd.print(" %");
  delay(500);
  lcd.clear();
  
 }

void setup()
{lcd.begin();
  // Debug console
  Serial.begin(9600);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
    timer1.setInterval(1000L, ultrasonic);
}

void loop()
{
  Blynk.run();
  timer.run();.
timer1.run();
}
void ultrasonic() {
   long duration, distance;
   digitalWrite(5,LOW);
   delayMicroseconds(2);
   digitalWrite(5, HIGH);   delayMicroseconds(10);
   digitalWrite(5, LOW);
   duration = pulseIn(6, HIGH);
   distance = duration * 340 / (2 * 10000);
   Blynk.virtualWrite(V10,distance);
   lcd.setCursor(1,0);
  lcd.print("distance=");
  lcd.print(distance);
  lcd.print("cm");
  delay(500);
  lcd.clear();
  int t= analogRead(A0);
  int light =map(t,0,1023,0,100);
  if(light<50){
    digitalWrrite(10,LOW);
  }
  else{
    digitalWrite(10,HIGH);
  }
  
}

