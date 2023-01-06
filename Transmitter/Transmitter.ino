#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

const char *msg1 = "UP";
const char *msg2 = "NEUTRAL";
const char *msg3 = "DOWN";

void setup()
{
    Serial.begin(9600);	  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    const char *msg = "Hello World!";
    driver.send((uint8_t *)msg, strlen(msg));
    Serial.println(msg);
    driver.waitPacketSent();
    delay(1000);
}
