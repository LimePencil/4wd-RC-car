#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10
#define in1 4
#define in2 5
#define in3 6
#define in4 7
bool line1;
bool line2;
bool line3;
bool line4;

typedef struct {
  byte mapX1;
  byte mapX2;
  byte mapY1;
  byte mapY2;
  byte SW_state1;
  byte SW_state2; 
} Data_Package;
Data_Package data;

RF24 radio(CE_PIN, CSN_PIN);

const byte rxAddr[6] = "00001";

void setup()
{

  //Serial.begin(9600);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);




  //Serial.println("NRF24L01P Receiver Starting...");
 
 
  radio.begin();
  radio.setPALevel(RF24_PA_MIN); 
  radio.setDataRate( RF24_250KBPS );
  radio.setPayloadSize(6);
  radio.setRetries(15, 15);
  radio.openReadingPipe(0, rxAddr);
  radio.startListening();
 
}

void loop()
{
  /* Serial.print("joystickX1: ");
  Serial.print(data.mapX1);
  Serial.print("; joystickY1: ");
  Serial.print(data.mapY1);
  Serial.print("; joystickX2: ");
  Serial.print(data.mapX2);
  Serial.print("; joystickY2: ");
  Serial.print(data.mapY2);
  */
  if (radio.available())
  {
    radio.read(&data, sizeof(data));
   
    //Serial.print("Received Message: ");

    if (data.mapX1 > 200){//Serial.print("Up");
    line1 = true;
    line2 = false;
    line3 = false;
    line4 = true;
    }

    else if (data.mapX1 < 74){//Serial.print("down");
    line1 = false;
    line2 = true;
    line3 = true;
    line4 = false;
    }
    if (data.mapY2 > 200){//Serial.print("right");

        line1 = false;
    line2 = true;
    line3 = false;
    line4 = true;
    }
    else if (data.mapY2 < 74){//Serial.print("left");

        line1 = true;
    line2 = false;
    line3 = true;
    line4 = false;
    }
    if (data.mapX1 > 110 && data.mapX1 < 140 && data.mapY2 > 110 && data.mapY2 < 140){//Serial.print("stop");
    line1 = false;
    line2 = false;
    line3 = false;
    line4 = false;
    }

    if(line1 == true){ 
      digitalWrite(in1, HIGH);
    }
    else if (line1 == false){
      digitalWrite(in1, LOW);
    }
        if(line2 == true){ 
      digitalWrite(in2, HIGH);
    }
    else if (line2 == false){
      digitalWrite(in2, LOW);
    }
        if(line3 == true){ 
      digitalWrite(in3, HIGH);
    }
    else if (line3 == false){
      digitalWrite(in3, LOW);
    }
        if(line4 == true){ 
      digitalWrite(in4, HIGH);
    }
    else if (line4 == false){
      digitalWrite(in4, LOW);
    }

    //Serial.println("");
  }
}
