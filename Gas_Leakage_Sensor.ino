
//Gas Leakage Sensor
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
SoftwareSerial mySerial(9, 10);

int sensor=7;
int speaker=8;
int gas_val,Gas_alert, Gas_shut;
int Gas_Leak_Status;
int sms_count=0;

void setup()
{

pinMode(sensor,INPUT);
pinMode(speaker,OUTPUT);
mySerial.begin(9600);   
Serial.begin(9600);
lcd.begin(16,2);  
delay(500);

}

void loop()
{
CheckGas();
CheckShutDown();
}

void CheckGas()
{

lcd.setCursor(0,0);
lcd.print("Gas Scan - ON");
Gas_alert=ScanGasLevel();
if(Gas_alert==LOW)
{
 SetAlert(); // Function to send SMS Alerts
}}

int ScanGasLevel()
{
gas_val=digitalRead(sensor); // reads the sensor output (Vout of LM35)

return gas_val; // returns temperature value in degree celsius
}

void SetAlert()
{
digitalWrite(speaker,HIGH);  
while(sms_count<3) //Number of SMS Alerts to be sent
{  
SendTextMessage(); // Function to send AT Commands to GSM module
}
Gas_Leak_Status=1; 
lcd.setCursor(0,1);
lcd.print("Gas Alert! SMS Sent!");
}

void CheckShutDown()
{
if(Gas_Leak_Status==1)
{

Gas_shut=ScanGasLevel();
if(Gas_shut==HIGH)
{

lcd.setCursor(0,1);
lcd.print("No Gas Leaking");
digitalWrite(speaker,LOW);
sms_count=0;
Gas_Leak_Status=0;
}}}

void SendTextMessage()
{
  mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  mySerial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r"); // change to the phone number you using 
  delay(1000);
  mySerial.println("Gas Leaking!");//the content of the message
  delay(200);
  mySerial.println((char)26);//the stopping character
  delay(1000);
   mySerial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r"); // change to the phone number you using 
  delay(1000);
  mySerial.println("Gas Leaking!");//the content of the message
  delay(200);
  mySerial.println((char)26);//the message stopping character
  delay(1000);
  sms_count++;
}
