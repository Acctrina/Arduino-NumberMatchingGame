#include <Wire.h>
#include <EEPROM.h>
#include <NewPing.h>
#define TRIGGER_PIN   0
#define ECHO_PIN      1  
#define MAX_DISTANCE  300
#define R1 2
#define R2 8
#define R3 10
#define R4 3
#define R5 A1
#define R6 11
#define R7 4
#define R8 7
#define C1 6
#define C2 A2
#define C3 13
#define C4 A3
#define C5 12
#define C6 9
#define C7 A0
#define C8 5
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int value;
int x = 10;
int num = 0;
int address = 0;
const int COUNT_ADDR1 = 0; 
const int COUNT_ADDR2 = 1;
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
unsigned long lastLongMeasureTime;


void setup() {

  //Serial.begin(9600); //Undo to serial print board address
  byte hiByte = EEPROM.read(COUNT_ADDR1);
  byte lwByte = EEPROM.read(COUNT_ADDR2);
  address = word(hiByte, lwByte); //To acquire slave address
  Serial.print("Board address: ");
  Serial.print(address);
  Wire.begin(address);                
  Wire.onRequest(requestEvent); //Registers function requestEvent to be called when master requests data from slave
  Wire.onReceive(receiveEvent); //Registers function recieveEvent when a transmission is received from master
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);
  pinMode(C1, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(C3, OUTPUT);
  pinMode(C4, OUTPUT);
  pinMode(C5, OUTPUT);  
  pinMode(C6, OUTPUT);
  pinMode(C7, OUTPUT);
  pinMode(C8, OUTPUT); 
}

byte Empty[] = 
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

byte Reset[] = 
{
  B00111100,
  B01000010,
  B11100001,
  B01000001,
  B00000001,
  B00000001,
  B01000010,
  B00111100
};

byte Pattern[8][8] = {
  //Zero
  B00000000,
  B00111100,
  B01100110,
  B01101110,
  B01110110,
  B01100110,
  B01100110,
  B00111100,
  //One
  B00000000,
  B00011000,
  B00011000,
  B00111000,
  B00011000,
  B00011000,
  B00011000,
  B01111110,
  //Two
  B00000000,
  B00111100,
  B01100110,
  B00000110,
  B00001100,
  B00110000,
  B01100000,
  B01111110,
  //Three
  B00000000,
  B00111100,
  B01100110,
  B00000110,
  B00011100,
  B00000110,
  B01100110,
  B00111100,
  //Four
  B00000000,
  B00001100,
  B00011100,
  B00101100,
  B01001100,
  B01111110,
  B00001100,
  B00001100,
  //Five
  B00000000,
  B01111110,
  B01100000,
  B01111100,
  B00000110,
  B00000110,
  B01100110,
  B00111100,
  //Six
  B00000000,
  B00111100,
  B01100110,
  B01100000,
  B01111100,
  B01100110,
  B01100110,
  B00111100,
  //Seven
  B00000000,
  B01111110,
  B01100110,
  B00001100,
  B00001100,
  B00011000,
  B00011000,
  B00011000};

const byte rows[] = {
    R1, R2, R3, R4, R5, R6, R7, R8};
const byte col[] = {
    C1,C2, C3, C4, C5, C6, C7, C8};

void  drawScreen(byte buffer2[])
{
  // Turn on each row in series
  for (byte i = 0; i < 8; i++) 
  {
    setColumns(buffer2[i]); // Set columns for this specific row
    digitalWrite(rows[i], HIGH);
    delay(2);
    digitalWrite(rows[i], LOW);
  }
}

void setColumns(byte b) 
{
  digitalWrite(C8, (~b >> 0) & 0x01); // Get the 1st bit: 10000000
  digitalWrite(C7, (~b >> 1) & 0x01); // Get the 2nd bit: 01000000
  digitalWrite(C6, (~b >> 2) & 0x01); // Get the 3rd bit: 00100000
  digitalWrite(C5, (~b >> 3) & 0x01); // Get the 4th bit: 00010000
  digitalWrite(C4, (~b >> 4) & 0x01); // Get the 5th bit: 00001000
  digitalWrite(C3, (~b >> 5) & 0x01); // Get the 6th bit: 00000100
  digitalWrite(C2, (~b >> 6) & 0x01); // Get the 7th bit: 00000010
  digitalWrite(C1, (~b >> 7) & 0x01); // Get the 8th bit: 00000001
}


void loop() {

        value = sonar.ping_cm();

        if (value > 5) 
        {
           lastLongMeasureTime = millis(); // reset the clock if the distance is too great
        }
        else if(value < 5 && (millis() - lastLongMeasureTime)>=1000)
        {
          num = 3;
          Serial.println();
          Serial.print("Sent!");
          Serial.print(num);
          
          for(int i = 0; i<100; i++){
          drawScreen(Reset); 
          }
           if ((millis()- lastLongMeasureTime)>=1000)
              {
                num = 0;
                lastLongMeasureTime = millis(); 
                Serial.println();
                Serial.print("Reset!");
                Serial.print(num);
              } 
              
        }
     
    
         
   if(x >= 0 && x <= 7)
   {
    drawScreen(Pattern[x]);
   }
   else{
    drawScreen(Empty);
   }  

}
 
void receiveEvent(int howMany)
{
  x = Wire.read();
}

void requestEvent() 
{
    Wire.write(num);
}
