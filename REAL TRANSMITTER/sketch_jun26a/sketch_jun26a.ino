
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Set the CE & CSN pins
#define VRx1 A0
#define VRy1 A1
#define SW1 2
#define VRx2 A2
#define VRy2 A3
#define SW2 3
#define CE_PIN   9
#define CSN_PIN 10


int xPosition1 = 0;
int yPosition1 = 0;
int SW_state1 = 0;
int mapX1 = 0;
int mapY1 = 0;

int xPosition2 = 0;
int yPosition2 = 0;
int SW_state2 = 0;
int mapX2 = 0;
int mapY2 = 0;

typedef struct {
  byte mapX1;
  byte mapX2;
  byte mapY1;
  byte mapY2;
  byte SW_state1;
  byte SW_state2;
} Data_Package;

Data_Package data;



// This is the address used to send/receive
const byte rxAddr[6] = "00001";

// Create a Radio
RF24 radio(CE_PIN, CSN_PIN); 

void setup() {
  pinMode(VRx1, INPUT);
  pinMode(VRy1, INPUT);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(VRx2, INPUT);
  pinMode(VRy2, INPUT);
  pinMode(SW2, INPUT_PULLUP);
data.mapX1 = 127;
data.mapX2 = 127;
data.mapY1 = 127;
data.mapY2 = 127;
data.SW_state1 = 1;
data.SW_state2 = 1;
  // Start up the Serial connection
  while (!Serial);
  Serial.begin(9600);
  
  // Start the Radio!
  radio.begin();
  
  // Power setting. Due to likelihood of close proximity of the devices, set as RF24_PA_MIN (RF24_PA_MAX is default)
  radio.setPALevel(RF24_PA_MIN); // RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  
  // Slower data rate for better range
  radio.setDataRate( RF24_250KBPS ); // RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  
  // Number of retries and set tx/rx address
  radio.setRetries(15, 15);
  radio.setPayloadSize(6);
  radio.openWritingPipe(rxAddr);

  // Stop listening, so we can send!
  radio.stopListening();
}

void loop() {
  xPosition1 = analogRead(VRx1);
  yPosition1 = analogRead(VRy1);
  SW_state1 = digitalRead(SW1);
  xPosition2 = analogRead(VRx2);
  yPosition2 = analogRead(VRy2);
  SW_state2 = digitalRead(SW2);
  data.mapX1 = map(xPosition1, 0, 1023, 0, 255);
  data.mapY1 = map(yPosition1, 0, 1023, 0, 255);
  data.mapX2 = map(xPosition2, 0, 1023, 0, 255);
  data.mapY2 = map(yPosition2, 0, 1023, 0, 255);
  Serial.print("joystickX1: ");
  Serial.print(data.mapX1);
  Serial.print("; joystickY1: ");
  Serial.print(data.mapY1);
  Serial.print("; joystickX2: ");
  Serial.print(data.mapX2);
  Serial.print("; joystickY2: ");
  Serial.println(data.mapY2);
  if (data.SW_state1 == 0) {
    Serial.println("button 1 pressed");
  }
  if (data.SW_state2 == 0) {
    Serial.println("button 2 pressed");
  }


  // Ace, let's now send the message
  radio.write(&data, sizeof(data));

  // Wait a short while before sending the other one
  delay(10);
}
 
