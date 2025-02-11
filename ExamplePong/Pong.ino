#include "src/PongGame.h"

PongGame ponggame;

void setup() 
{  
    Serial.begin(9600);
    while(!Serial);

    ponggame.Init();
}

void loop() 
{
    ponggame.Update();
}