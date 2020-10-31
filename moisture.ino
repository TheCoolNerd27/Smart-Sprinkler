

#include <DS3231.h>

int Relay1=6;
int Relay2=7;
int soilpin=A0,output,output2;


// Init the DS3231 using the hardware interface
DS3231 rtc(SDA, SCL);
Time t;
const int onhour =8;//Time
const int onmin=00;
const int onsec=30;
const int offhour=8;
const int offmin=01;
const int offsec=00;

void setup()
{
  // Setup Serial connection
  Serial.begin(9600);
  rtc.begin();
  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
  digitalWrite(Relay1,LOW);
  digitalWrite(Relay2,LOW);
  Serial.print("Enter\n1.To Pump at Specific Time\n2.To Pump using Soil Moisture\n3.For Dripping irrigation\n0.To Switch Everything Off"); 
  
  // The following lines can be uncommented to set the date and time
  rtc.setDOW(MONDAY);       // Set Day-of-Week to SUNDAY
  rtc.setTime(8,00,00);        // Set the time to 12:00:00 (24hr format)
  rtc.setDate(7,03,2019);   // Set the date to January 1st, 2014
}

void loop()
{
  int flag=0;
  t=rtc.getTime();
  

 output=analogRead(soilpin);
 output2=map(output,1060,260,0,100);
 char ch=Serial.read();
  // Wait one second before repeating :)
 
switch(ch)
{
 case '1':
 while(ch!='0'){
  flag=0;
 
 while(flag!=1 && ch!='0'){
 t=rtc.getTime();
  Serial.print(t.hour);
  Serial.print(" Hours ");
  Serial.print(t.min);
  Serial.print(" Minutes ");
  Serial.print(t.sec);
  Serial.println(" Secs ");
  ch=Serial.read();
 if(t.hour==onhour && t.min==onmin && t.sec==onsec)
  {
    digitalWrite(Relay1,HIGH);
    Serial.println("PUMP ON");
  }
  else if(t.hour==offhour && t.min==offmin && t.sec==offsec)
  { flag=1;
    digitalWrite(Relay1,LOW);
    Serial.println("PUMP OFF");
    
  } 
   delay (1000);}}
  break;
  case '2':
  //Serial.println(output);
  while(ch!= '0'){
  while(output2<=30 )
  {  
     digitalWrite(Relay2,HIGH);
     digitalWrite(Relay1,HIGH);
    Serial.println("Moisture On ");
    //Serial.println(output);
    //Serial.println(output2);
    output=analogRead(soilpin);
 output2=map(output,1060,260,0,100);
 ch=Serial.read();
 if(ch=='0')
 {
  break;
 }
    
    
  }//Serial.println(output2);
  Serial.println("Moisture OFF!! Pretty Wet ");
  digitalWrite(Relay2,LOW);
     digitalWrite(Relay1,LOW);
     output=analogRead(soilpin);
 output2=map(output,1060,260,0,100);
 if(ch=='0')
 {
  break;
 }
 ch=Serial.read();}
  break;
  case '3':
  digitalWrite(Relay2,HIGH);
  Serial.print("Drippin'");
  break;
  case '0':
  digitalWrite(Relay2,LOW);
  digitalWrite(Relay1,LOW);
  
  
}
}
