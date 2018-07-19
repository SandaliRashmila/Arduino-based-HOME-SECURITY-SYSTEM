#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3);

int sensor=7; //The output of PIR sensor connected to pin 7 of Arduino
int push_switch=6; // push button switch connected to pin 6 of Arduino
int buzzer=8; // buzzer connected to pin 8 of Arduino
int sensor_value; //variable to hold read sensor value
int sms_count=0;
int ledPin=13;

void setup()
{ pinMode(sensor,INPUT); // configuring pin 7 as Input
  pinMode(push_switch,INPUT); // configuring pin 6 as Input
  pinMode(buzzer,OUTPUT); // configuring pin 8 as OUTPUT
  
  mySerial.begin(9600);
  delay(500);                                         
    
}

void loop()
{
Check_Burglar();// subroutine to check sensor status and activation of outputs
Check_Reset(); // subroutine to check if alarm reset switch pressed or not
}

void Check_Burglar()
{
{
sensor_value=digitalRead(sensor); // Reading sensor value from pin 7
if(sensor_value==HIGH) // Checking if PIR sensor sends a HIGH signal to Arduino
{ 
  digitalWrite(ledPin, HIGH);  
    playTone(1000, 300);
    delay(150);
    
    while(sms_count<1) 
    {  
      SendTextMessage(); // Function to send AT Commands to GSM module
    }
    sensor_value=HIGH;
    
}}
}
void Check_Reset()
{
if(digitalRead(push_switch==HIGH))// Checking if pushbutton was pressed 
{
digitalWrite(buzzer,LOW); // turning OFF the buzzer 
     // We only want to print on the output change, not state
     
      sensor_value = LOW;

sms_count=0; // Reactivating the SMS Alert Facility
}}

void SendTextMessage()
{
  mySerial.println("AT+CMGF=1\r");    //To send SMS in Text Mode
  delay(1000);
  mySerial.println("AT+CMGS=\"0776943443\""); // change to the phone number you using 
  delay(1000);
  mySerial.println("INTRUDER ALERT!");//the content of the message
  delay(200);
  mySerial.println((char)26);//the stopping character
  delay(100);
  
  sms_count++;
}
// duration in mSecs, frequency in hertz
void playTone(long duration, int freq) 
{
    duration *= 1000;
    int period = (1.0 / freq) * 100000;
    long elapsed_time = 0;
    while (elapsed_time < duration) 
    {
        digitalWrite(buzzer,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(buzzer, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}

