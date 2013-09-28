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
#include <Rele.h>
#include <TimeAlarms.h>

#define MSG_LEN  14
#define RELAY_MSG_LEN 3
#define RELAY_MSG_LEN_TIMED  5 
#define TIME_HEADER  'T' 
#define SHOW_SATUS_HEADER  'S' 
#define PROG_HEADER  'P' 
#define RELAY_HEADER  'R'
#define RELAY_ON  'E'  
#define RELAY_OFF  'A'
#define DURATION 'D'
#define RELAY_COUNT 4







int numrele[RELAY_COUNT] = { 5 ,  6, 7 , 8}; //rele numbers upto 4
Rele reles[RELAY_COUNT];

void setup()  {
  Alarm.delay(3000);
  Serial.begin(9600);
  Serial.println("Iniciando control de regleta...");
  //setReles
  for(int i = 0;i<=RELAY_COUNT-1;i++){
	 reles[i].setRele(i+1);
   	 reles[i].setPin(numrele[i]);
   	 reles[i].setOutput();
   	 reles[i].releOff();
  }

  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");
  digitalClockDisplay();

}


void loop()
{
  if(Serial.available())
  {
    processMessage();
  } 
  Alarm.delay(1000);
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
	char command[MSG_LEN-1]; 
    char cmd = Serial.read() ;  
    //Serial.print(cmd);
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

    //Programar
    if( cmd == PROG_HEADER ) {
        
       for(int i=0; i < MSG_LEN -1; i++){   
        command[i] = Serial.read();           
      }
        switch (command[0]) {
           case '1':
        	    reles[0].setProg(juntarChar(command[1],command[2]),juntarChar(command[3],command[4]),juntarChar(command[5],command[6]),juntarChar(command[7],command[8]),juntarChar(command[9],command[10]),juntarChar(command[11],command[12]));
        	    Alarm.alarmRepeat(juntarChar(command[1],command[2]),juntarChar(command[3],command[4]),juntarChar(command[5],command[6]), encender1); 
        	    Alarm.alarmRepeat(juntarChar(command[7],command[8]),juntarChar(command[9],command[10]),juntarChar(command[11],command[12]), apagar1); 
        	   break;
           case '2':
        	   reles[1].setProg(juntarChar(command[1],command[2]),juntarChar(command[3],command[4]),juntarChar(command[5],command[6]),juntarChar(command[7],command[8]),juntarChar(command[9],command[10]),juntarChar(command[11],command[12]));
        	   Alarm.alarmRepeat(juntarChar(command[1],command[2]),juntarChar(command[3],command[4]),juntarChar(command[5],command[6]), encender2); 
        	   Alarm.alarmRepeat(juntarChar(command[7],command[8]),juntarChar(command[9],command[10]),juntarChar(command[11],command[12]), apagar2); 
        	   break;
           case '3':
         	   reles[2].setProg(juntarChar(command[1],command[2]),juntarChar(command[3],command[4]),juntarChar(command[5],command[6]),juntarChar(command[7],command[8]),juntarChar(command[9],command[10]),juntarChar(command[11],command[12]));
        	   Alarm.alarmRepeat(juntarChar(command[1],command[2]),juntarChar(command[3],command[4]),juntarChar(command[5],command[6]), encender3); 
        	   Alarm.alarmRepeat(juntarChar(command[7],command[8]),juntarChar(command[9],command[10]),juntarChar(command[11],command[12]), apagar4);  
         	   break;
           case '4':
           	   reles[3].setProg(juntarChar(command[1],command[2]),juntarChar(command[3],command[4]),juntarChar(command[5],command[6]),juntarChar(command[7],command[8]),juntarChar(command[9],command[10]),juntarChar(command[11],command[12]));
        	   Alarm.alarmRepeat(juntarChar(command[1],command[2]),juntarChar(command[3],command[4]),juntarChar(command[5],command[6]), encender4); 
        	   Alarm.alarmRepeat(juntarChar(command[7],command[8]),juntarChar(command[9],command[10]),juntarChar(command[11],command[12]), apagar4);                     
           	   break;
       }
     }

    //hora y estado
    if( cmd == SHOW_SATUS_HEADER ) {
       
       for(int i=0; i < MSG_LEN -1; i++){   
        command[i] = Serial.read();           
      }
      digitalClockDisplay();
      muestraEstado();
     }

     
    //Relay On-OF
    if( cmd == RELAY_HEADER  ) { 
   
       for(int i=0; i < MSG_LEN -1; i++){   
        command[i] = Serial.read();           
      }

      if(command[0] == RELAY_ON ){
          //Encender relay sin tiempo
         switch (command[1]) {
            case '1':
            	reles[0].releOn();
                break;
            case '2':
            	reles[1].releOn();
                break;
            case '3':
            	reles[2].releOn();
                break;
            case '4':
            	reles[3].releOn();
                break;   
                     
        }
       }  
       
       
      if(command[0]== RELAY_OFF ){
         switch (command[1]) {
            case '1':
            	reles[0].releOff();
            	break;
            case '2':
            	reles[1].releOff();
            	break;
            case '3':
            	reles[2].releOff();
            	break;
            case '4':
            	reles[3].releOff();
            	break;
        } 
       }  
      } 
  } 
  
}

void muestraEstado(){
	Serial.println("Estado Programación Reles");
	for(int i=0;i<=RELAY_COUNT-1;i++)
		reles[i].muestraProg();

	Serial.println("Estado Actual Reles");
	for(int i=0;i<=RELAY_COUNT-1;i++){
		if(reles[i].isOn()){
			//Serial.print
			Serial.println("ON");
		}else{
			//Serial.print
			Serial.println("OFF");
		}
	}
}

//funciones programar reles
void encender1(){
	reles[0].releOn();
}


void encender2(){
	reles[1].releOn();
}

void encender3(){
	reles[2].releOn();
}

void encender4(){
	reles[3].releOn();
}

void apagar1(){
	reles[0].releOff();
}

void apagar2(){
	reles[1].releOff();
}

void apagar3(){
	reles[2].releOff();
}

void apagar4(){
	reles[3].releOff();
}

//utilidades
int juntarChar(char h1,char h2){
  int decenas = aEntero(h1);
  int unidades = aEntero(h2);
  int suma = (decenas * 10) + unidades; 
  return suma;
}

int aEntero(char c){
    int salida;
    if( c >= '0' && c <= '9'){
      salida = c - '0' ; // convert digits to a number
    }
    return salida;
}

