/*
* Control Regleta
*Encender y Apagar 4 reles
* R+[E|A]+[1-4][+SEC] 
* Set time
* T+unix time 
 */

//RTC libs
#include <Time.h>  
#include <Wire.h>  
#include <DS1307RTC.h> 



#define MSG_LEN  11 
#define RELAY_MSG_LEN 3
#define RELAY_MSG_LEN_TIMED  5 
#define TIME_HEADER  'T' 
#define SHOW_TIME_HEADER  'S' 
#define PROG_HEADER  'P' 
#define RELAY_HEADER  'R'
#define RELAY_ON  'E'  
#define RELAY_OFF  'A'
#define DURATION 'D'

int r1 = 13 , r2  = 11, r3 = 10 , r4 = 9;


void setup()  {
  delay(3000);
  Serial.begin(9600);
  Serial.println("Iniciando control de regleta...");
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");      
}

void loop()
{
  if(Serial.available())
  {
    processMessage();
  } 
   delay(1000);
}





//funciones RTC

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


// procesar mensajes serial

void processMessage(){

  while(Serial.available() >=  MSG_LEN ){  
    char cmd = Serial.read() ;  
    Serial.print(cmd); 
    //sync Time 
    if( cmd == TIME_HEADER ) {       
      time_t pctime = 0;
      for(int i=0; i < MSG_LEN -1; i++){   
        char c = Serial.read();          
        if( c >= '0' && c <= '9'){   
          pctime = (10 * pctime) + (c - '0') ; // convert digits to a number    
        }
      }   
       if(pctime >0)
       {
        RTC.set(pctime);   // set the RTC and the system time to the received value
        setTime(pctime);  
        digitalClockDisplay();       
       }
     }
    //show Time 
    if( cmd == SHOW_TIME_HEADER ) {       
       char command[10];   
       for(int i=0; i < MSG_LEN -1; i++){   
        command[i] = Serial.read();           
      }
      digitalClockDisplay();
     }

    //Programar
    if( cmd == PROG_HEADER ) {       
       char command[10];   
       for(int i=0; i < MSG_LEN -1; i++){   
        command[i] = Serial.read();           
      }
      digitalClockDisplay();
     }

     
    //Relay On-OF
    if( cmd == RELAY_HEADER  ) { 
       char command[10];   
       for(int i=0; i < MSG_LEN -1; i++){   
        command[i] = Serial.read();           
      }
   
      if(command[0] == RELAY_ON ){
        Serial.print(command[1]);
          //Encender relay sin tiempo
         switch (command[1]) {
            case '1':
                Serial.print("Encender Relay 1");
                digitalWrite(r1, HIGH);   // turn the LED on (HIGH is the voltage level)            
                break;
            case '2':
                Serial.print("Encender Relay 2");
                digitalWrite(r2, HIGH);   // turn the LED on (HIGH is the voltage level)            
                break;
            case '3':
                Serial.print("Encender Relay 3");
                digitalWrite(r3, HIGH);   // turn the LED on (HIGH is the voltage level)             
                break;
            case '4':
                Serial.print("Encender Relay 4"); 
                digitalWrite(r4, HIGH);   // turn the LED on (HIGH is the voltage level)               
                break;   
                     
        }
       }  
       
       
      if(command[0]== RELAY_OFF ){
        Serial.print(command[1]);
         switch (command[1]) {
            case '1':
                Serial.print("Apagar Relay 1");            
                digitalWrite(r1, LOW);    // turn the LED off by making the voltage LOW             
                break;
            case '2':
                Serial.print("Apagar Relay 2");
                digitalWrite(r2, LOW);                  
                break;
            case '3':
                Serial.print("Apagar Relay 3");
                digitalWrite(r3, LOW);              
                break;
            case '4':
                Serial.print("Apagar Relay 4");
                digitalWrite(r4, LOW);                
                break;                
        } 
       }  
     
     /*
      for(int i=0; i < MSG_LEN -1; i++){   
        Serial.print(command[i]);           
      }*/
      Serial.println();
      } 
  } 
  
}

