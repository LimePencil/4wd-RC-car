#define in1 4
#define in2 5
#define in3 6
#define in4 7
#define xaxis A0
#define yaxis A1
#define button 2
void setup() {
Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(xaxis, INPUT);
  pinMode(yaxis, INPUT);
  pinMode(button, INPUT_PULLUP);
}
void loop(){

     digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // Set Motor B forward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

}
