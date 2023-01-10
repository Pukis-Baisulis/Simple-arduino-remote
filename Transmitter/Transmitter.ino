#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

#define MIN_VOLTAGE 7200

#define UP_PIN 6
#define MID_PIN 5
#define DOWN_PIN 4
#define ANTENA_PIN 12
#define LED 13
#define BATTERY_PIN A0

//const char *msg1 = "500";
//const char *msg2 = "050";
//const char *msg3 = "005";
//const char *msgNeutral = "000";

int voltage;
bool btn_1;
bool btn_2;
bool btn_3;

void erroredOut();

void setup()
{
  Serial.begin(9600);	// Debugging only
  while(!driver.init())
  {
    Serial.println("init failed");   
    erroredOut();
  }    
  Serial.println("Transmitter confirmed");
               
}

void loop()
{
  // voltage reading and setting led on if voltage is low
  voltage = analogRead(BATTERY_PIN)*2;
  if(voltage < MIN_VOLTAGE)
    digitalWrite(LED, HIGH);
  else
    digitalWrite(LED, LOW);

  btn_1 = digitalRead(UP_PIN);
  btn_2 = digitalRead(MID_PIN);
  btn_3 = digitalRead(DOWN_PIN);
  
  if(btn_1 && btn_2 && btn_3) // none
    const char *msg = "000";
  if(!btn_1 && !btn_2 && !btn_3)// none
    const char *msg = "000";
  if(btn_1 && btn_2 && btn_3)// none
    const char *msg = "000";
  if(btn_1 && btn_2 && btn_3)// none
    const char *msg = "000";

    
  if(btn_1 && !btn_2 && !btn_3) // up
    const char *msg = "500";

  if(!btn_1 && btn_2 && !btn_3) // mid
    const char *msg = "050";

  if(!btn_1 && !btn_2 && btn_3) // down
    const char *msg = "005";

  driver.send((char *)msg, strlen(msg));
  Serial.println(msg);
  driver.waitPacketSent();
  
  delay(100);
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
