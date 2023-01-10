#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile


#define CH1_PIN 6
#define CH2_PIN 5
#define CH3_PIN 9
#define ANTENA_PIN 11

RH_ASK driver;

void erroredOut();

void setup()
{
    Serial.begin(9600);	// Debugging only
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(CH1_PIN, OUTPUT);
    pinMode(CH2_PIN, OUTPUT);
    pinMode(CH3_PIN, OUTPUT);
    while(!driver.init())
    {
      Serial.println("init failed");
      erroredOut();
    }
  Serial.println("Nice");
}

void loop()
{
  uint8_t buf[3];
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    Serial.println((char*)buf);
  }
    
  
  if((char*)buf == "500") //CH1 active
  {
    digitalWrite(CH1_PIN, HIGH);
    digitalWrite(CH1_PIN, LOW);      
    digitalWrite(CH1_PIN, LOW);
  }
  if((char*)buf == "005") // CH3 active
  {
    digitalWrite(CH1_PIN, LOW);
    digitalWrite(CH1_PIN, LOW);      
    digitalWrite(CH1_PIN, HIGH);
  }
  if((char*)buf == "050") // CH2 active 
  {
    digitalWrite(CH1_PIN, LOW);
    digitalWrite(CH1_PIN, HIGH);      
    digitalWrite(CH1_PIN, LOW);
  }
  else // none active
  {
    digitalWrite(CH1_PIN, LOW);
    digitalWrite(CH1_PIN, LOW);      
    digitalWrite(CH1_PIN, LOW);
  }

}


void erroredOut()
{
  int c = 0;
  while(c<5)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    c++;
  }
}