int VRx1 = A0;
int VRy1 = A1;
int SW1 = 2;
int VRx2 = A2;
int VRy2 = A3;
int SW2 = 3;

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

void setup() {
  Serial.begin(9600); 
  
  pinMode(VRx1, INPUT);
  pinMode(VRy1, INPUT);
  pinMode(SW1, INPUT_PULLUP); 
  pinMode(VRx2, INPUT);
  pinMode(VRy2, INPUT);
  pinMode(SW2, INPUT_PULLUP); 
  
}

void loop() {
  xPosition1 = analogRead(VRx1);
  yPosition1 = analogRead(VRy1);
  SW_state1 = digitalRead(SW1);
  xPosition2 = analogRead(VRx2);
  yPosition2 = analogRead(VRy2);
  SW_state2 = digitalRead(SW2);
  mapX1 = map(xPosition1, 0, 1023, -512, 512);
  mapY1 = map(yPosition1, 0, 1023, -512, 512);
  mapX2 = map(xPosition2, 0, 1023, -512, 512);
  mapY2 = map(yPosition2, 0, 1023, -512, 512);  
  Serial.print("X1: ");
  Serial.print(mapX1);
  Serial.print(" | Y1: ");
  Serial.print(mapY1);
  Serial.print(" | Button1: ");
  Serial.println(SW_state1);
  Serial.print("X2: ");
  Serial.print(mapX2);
  Serial.print(" | Y2: ");
  Serial.print(mapY2);
  Serial.print(" | Button2: ");
  Serial.println(SW_state2);

  delay(1000);
  
}
