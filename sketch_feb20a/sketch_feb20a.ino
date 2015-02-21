/*
  *
  * Udemy.com
  * Building an Arduino DC Voltmeter
  *
  */
 
 float vPow = 4.7;
 float r1 = 100000;
 float r2 = 10000;
 int potPin = 3;
 
 void setup() {
   Serial.begin(9600);
   
   digitalWrite(14 + potPin, HIGH);
   
   // Send ANSI terminal codes
//   Serial.print("\x1B");
//   Serial.print("[2J");
//   Serial.print("\x1B");
//   Serial.println("[H");
   // End ANSI terminal codes
   
   Serial.println("--------------------");
   Serial.println("DC VOLTMETER");
   Serial.print("Maximum Voltage: ");
   Serial.print((int)(vPow / (r2 / (r1 + r2))));
   Serial.println("V");
   Serial.println("--------------------");
   Serial.println("");
   
   delay(2000);
 }
 
 void loop() {
//   float v = (analogRead(3) * vPow) / 1024.0;
//   float v2 = v / (r2 / (r1 + r2));
   
   // Send ANSI terminal codes
//   Serial.print("\x1B");
//   Serial.print("[1A");
   // End ANSI terminal codes
   
//   Serial.println(analogRead(potPin));
   int val = analogRead(potPin);
   if (val < 100) {
     Serial.println("Ding-dong!!"); 
   }
   delay(100);
 }
