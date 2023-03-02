
#include <Wire.h>
#include "LedControl.h"
#include "binary.h"


LedControl lc=LedControl(12,11,10,4); //Pin 12 Din, Pin 11 Clk, Pin 10, Load
int id, val;
int Time_Minutes =  00;
int Time_Seconds =  00;
int matched = 0; //Counts no. of matched numbers
bool sensed = false;
  
int address[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //IDs of slave module 
int location[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//Array for comparision
int original[16] = {0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7};//For serial monitor to show original sequence
int num[16] = {0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7};//Values to randomize
int compare[16] = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};//Stores values to be compared
int num1, num2;
int val1, val2;
int a, b, c, d, f, u, z, m, n;
float e, total;
int Update = 0;
int reset = 0;


void(* resetFunc)(void) = 0;

void setup()
{

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0 
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  Wire.begin();       
  Serial.begin(9600);  
  pinMode(13, OUTPUT);  
  randomSeed(analogRead(0));
  lc.shutdown(0,false);
  lc.shutdown(1,false);
  lc.shutdown(2,false);
  lc.shutdown(3,false);
  lc.setIntensity(0,2);
  lc.setIntensity(1,2);
  lc.setIntensity(2,2);
  lc.setIntensity(3,2);
  Random();
  Transmission();

  Wire.beginTransmission(16);
  Wire.write(10);
  Wire.endTransmission();


}  

void Random()
{ 
  for (int i= 0; i< 16; i++) 
  { 
    int pos = random(16);
    int t = address[i];   
    address[i] = address[pos];
    address[pos] = t;
  }
  for (int i= 0; i< 16; i++) 
  {
    int pos = random(16);
    int t = num[i];   
    num[i] = num[pos];
    num[pos] = t;
  }
  Serial.print("Original Sequence\n");
  Serial.print("SlaveID: ");
  for (int i= 0; i< 16; i++)
  {
    Serial.print(i);
    Serial.print(", ");
    
  }
  Serial.println();
  Serial.print("NumAssign: ");
  for(int i = 0; i<16; i++)
  {
    Serial.print(original[i]);
    Serial.print(", ");   
  }
  Serial.println();
  Serial.println();
 
  Serial.print("Randomized Sequence\n");
  Serial.print("SlaveID: ");
  for (int i =0; i<16; i++)
  {
    Serial.print(address[i]);
    Serial.print(", ");
  }
  Serial.println();
  Serial.print("NumAssign: ");
  for(int i=0; i<16; i++)
  {
    Serial.print(num[i]);
    Serial.print(", ");
  }
  Serial.println();
  Serial.println();
}
void Transmission()
{
       for(int x=0;x<16;x++){
       id = address[x];
       val = num[x];
       Wire.beginTransmission(id);//Begin transmission to slave id
       Wire.write(val);// Write to slave 
       Wire.endTransmission();
        
       Serial.print("ID: ");
       Serial.print(id);
       Serial.print("\tNumber assigned is: ");
       Serial.print(val);
       Serial.println();
       }
       Serial.print("============================================================================");
       Serial.println();
}
void Compare()
{  
for(int x=0;x<16;x++)
      {        
              z = location[x];
              if(z < 16){
              Wire.requestFrom(z,1);
              //Serial.print("Requesting from ID: ");
              //Serial.print(z);
              //Serial.println();
              }
              int value = Wire.read();
              if(value >= 0 && value <= 8 && Update < 2)
              {
                                
                 Serial.print("ID ");
                 Serial.print(z);
                 Serial.print(" = ");  
                 Serial.println(value);
                 compare[z] = value;
                 Update++;  
                 Serial.print("Update " );
                 Serial.print(Update);
                 Serial.println();
                 

                 if(Update == 1)
                 {
                      sensed = true;
                      for(int i=0; i<16; i++)
                      {               
                          num1 = compare[i];
                            if(num1 < 8)
                            {  
                               c = num1;
                               Wire.beginTransmission(16);
                               Wire.write(c);
                               Wire.endTransmission();
                                                    
                               Serial.print("First Number = " );
                               Serial.print(num1);
                               Serial.println();
                                
                                                                                   
                            }                    
                      }
                      for(int i=0; i<16; i++)
                      {
                             a = compare[i];
                         if(a<8)
                         {
                             b = i;
                             Serial.print("Number Location = ");
                             Serial.print(b);
                             Serial.println();
                         }
                      }
                 }
                  
                 if(Update == 2)
                 {                  
                          for(int u=0; u<16; u++)
                          {
                            if(u == b)
                            {
                              continue;
                            }

                                               
                             num2 = compare[u];
                             if(num2 < 8  )
                             {
                             d = num2;

                             Wire.beginTransmission(16);
                             Wire.write(d);
                             Wire.endTransmission();
                               
                             Serial.print("Second Number = ");
                             Serial.print(num2);
                             Serial.println();
                             } 
                             Serial.print(compare[u]);
                             Serial.print(", ");                          
                          }
                          for(int i=0; i<16; i++)
                          { 
                            if(i == b)
                            {
                              continue;
                            }
                            
                                a = compare[i];
                                if(a<8)
                                {
                                    f = i;
                                    Serial.println();
                                    Serial.print("Number Location = ");
                                    Serial.print(f);
                                    Serial.println();
                                }
                          }
                          total = c + d;
                          Serial.println();
                          Serial.print("Total = ");
                          Serial.print(total);
                          Serial.println();

                          e = total/2;
                          if(e == c)
                          {
                            val1 = b;
                            val2 = f;
                            m = b;
                            n = f;
                           
                            c = c + 10;
                            matched++;

                            location[m] = 20;
                            location[n] = 20;
                                                      
                            Serial.print("Divided Value = "); 
                            Serial.print(e);
                            Serial.println();

                            Serial.print("Position 1 = ");
                            Serial.print(val1);
                            Serial.println();
                            Serial.print("Position 2 = ");
                            Serial.print(val2);
                            Serial.println();

                            Wire.beginTransmission(val1);
                            Wire.write(c);
                            Wire.endTransmission();
                            
                            Wire.beginTransmission(val2);
                            Wire.write(c);
                            Wire.endTransmission();
                            } 
                     
                 }         
                
                                                  
                       for(int i=0; i<16; i++)
                       {
                       Serial.print(compare[i]);
                       Serial.print(", ");
                       }
                       Serial.println();
                       Serial.println();
                                                       
              }           
              else
   
              if(Update == 2)
              {
                Update =0;
                total =0;
                a = 0;
                b = 0;
                c = 0;
                d = 0; 
                e = 0;
                u = 0;
                num1 = 0;
                num2 = 0;
                val1 = 0;
                val2 = 0;

                Wire.beginTransmission(16);
                Wire.write(10);
                Wire.endTransmission();
                
                   for(int i=0; i<16; i++)
                   {
                   compare[i] = 10;
                   }
                   Serial.print("============================================================================");
                   Serial.println();
              }
           delay(100);  
      }
      


}

void Timer()
{
  DisplayTime();
  CalculateTime(1); 
  Time_Seconds++;
  
}

void SendTimerData(int DispNumber,int Digit)
{
     if(Digit == 0)
     { 
        //Display 0
        lc.setRow(DispNumber,0,0x00);
        lc.setRow(DispNumber,1,0x1c);
        lc.setRow(DispNumber,2,0x22);
        lc.setRow(DispNumber,3,0x22);
        lc.setRow(DispNumber,4,0x22);
        lc.setRow(DispNumber,5,0x22);
        lc.setRow(DispNumber,6,0x1c);
        lc.setRow(DispNumber,7,0x00);
      }
     if(Digit == 1)
     {
        //Display 1
        lc.setRow(DispNumber,0,0x00);
        lc.setRow(DispNumber,1,0x08);
        lc.setRow(DispNumber,2,0x18);
        lc.setRow(DispNumber,3,0x08);
        lc.setRow(DispNumber,4,0x08);
        lc.setRow(DispNumber,5,0x08);
        lc.setRow(DispNumber,6,0x3e);
        lc.setRow(DispNumber,7,0x00);
        }
     if(Digit == 2)
     {
        //Display 2
        lc.setRow(DispNumber,0,0x00);
        lc.setRow(DispNumber,1,0x1c);
        lc.setRow(DispNumber,2,0x22); 
        lc.setRow(DispNumber,3,0x04);
        lc.setRow(DispNumber,4,0x08);
        lc.setRow(DispNumber,5,0x10);
        lc.setRow(DispNumber,6,0x3e);
        lc.setRow(DispNumber,7,0x00);
     }
     if(Digit == 3)
     {
        //Display 3
        lc.setRow(DispNumber,0,0x00);
        lc.setRow(DispNumber,1,0x38);
        lc.setRow(DispNumber,2,0x04);
        lc.setRow(DispNumber,3,0x38);
        lc.setRow(DispNumber,4,0x04);
        lc.setRow(DispNumber,5,0x04);
        lc.setRow(DispNumber,6,0x38);
        lc.setRow(DispNumber,7,0x00);
     }
     if(Digit == 4)
     {
        //Display 4
        lc.setRow(DispNumber,0,0x00);
        lc.setRow(DispNumber,1,0x04);
        lc.setRow(DispNumber,2,0x0c);
        lc.setRow(DispNumber,3,0x14);
        lc.setRow(DispNumber,4,0x3e);
        lc.setRow(DispNumber,5,0x04);
        lc.setRow(DispNumber,6,0x04);
        lc.setRow(DispNumber,7,0x00);
     }
    if(Digit == 5)
    {
        //Display 5
        lc.setRow(DispNumber,0,0x00);
        lc.setRow(DispNumber,1,0x3e);
        lc.setRow(DispNumber,2,0x20);
        lc.setRow(DispNumber,3,0x3c);
        lc.setRow(DispNumber,4,0x02);
        lc.setRow(DispNumber,5,0x02);
        lc.setRow(DispNumber,6,0x3c);
        lc.setRow(DispNumber,7,0x00);
    }
    if(Digit == 6)
    { 
      //Display 6
      lc.setRow(DispNumber,0,0x00);
      lc.setRow(DispNumber,1,0x1e);
      lc.setRow(DispNumber,2,0x20);
      lc.setRow(DispNumber,3,0x3c);
      lc.setRow(DispNumber,4,0x22);
      lc.setRow(DispNumber,5,0x22);
      lc.setRow(DispNumber,6,0x1c);
      lc.setRow(DispNumber,7,0x00);
    }
    if(Digit == 7)
    {
      //Display 7
      lc.setRow(DispNumber,0,0x00);
      lc.setRow(DispNumber,1,0x3e);
      lc.setRow(DispNumber,2,0x02);
      lc.setRow(DispNumber,3,0x04);
      lc.setRow(DispNumber,4,0x08);
      lc.setRow(DispNumber,5,0x08);
      lc.setRow(DispNumber,6,0x08);
      lc.setRow(DispNumber,7,0x00);
    }
    if(Digit == 8)
    {
      //Display 8
      lc.setRow(DispNumber,0,0x00);
      lc.setRow(DispNumber,1,0x1c);
      lc.setRow(DispNumber,2,0x22);
      lc.setRow(DispNumber,3,0x1c);
      lc.setRow(DispNumber,4,0x22);
      lc.setRow(DispNumber,5,0x22);
      lc.setRow(DispNumber,6,0x1c);
      lc.setRow(DispNumber,7,0x00);
    }
    if(Digit == 9)
    {
      //Display 9
      lc.setRow(DispNumber,0,0x00);
      lc.setRow(DispNumber,1,0x1c);
      lc.setRow(DispNumber,2,0x22);
      lc.setRow(DispNumber,3,0x22);
      lc.setRow(DispNumber,4,0x1e);
      lc.setRow(DispNumber,5,0x02);
      lc.setRow(DispNumber,6,0x02);
      lc.setRow(DispNumber,7,0x00);
    }
  } 

void DisplayTime()
{
  
 SendTimerData(3,Time_Minutes / 10);
 if(Time_Minutes / 10 == 0)
 lc.shutdown(3,true);//Shut down leading zero
 else
 {
 lc.shutdown(3,false);
 SendTimerData(3,Time_Minutes / 10);
 }
 SendTimerData(2,Time_Minutes % 10);
 SendTimerData(1,Time_Seconds / 10);
 SendTimerData(0,Time_Seconds % 10);
 
 lc.setColumn(1,0,B00100100);
}

void CalculateTime(int Update)
{
  if(Time_Seconds == 59)
  {
  Time_Seconds = -1;
  Time_Minutes++; 
  }
  if(Time_Minutes == 60)
  {
  Time_Minutes = 00;
  }
}

ISR(TIMER1_COMPA_vect)  
{                       
       if(sensed == true && matched == 8)
       {
        return;
       }  
       if(sensed == true)
       {
           Timer();
       }                
}

void Reset()
{
  
   Wire.requestFrom(16,1);
   reset = Wire.read();

        /*Serial.print("Reset Number ");
        Serial.print(reset);
        Serial.println();*/
   

      if(reset == 3)
      {       
         resetFunc();  
 
      }

}
  

void loop() 
{          
        
       Compare();

       Reset();
       
       
} 
