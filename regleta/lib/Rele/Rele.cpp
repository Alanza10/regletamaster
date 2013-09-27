#include "Arduino.h"
#include "Rele.h"

void Rele::setRele(int rel){
	rele = rel;
}

void Rele::setPin(int p){
	pin = p;
}

void Rele::setOutput(){
	 pinMode(pin, OUTPUT);
}

void Rele::setInput(){
	 pinMode(pin, INPUT);
}

void Rele::releOn(){
    Serial.print("Encender Relay ");
    Serial.println(rele);
    digitalWrite(pin, HIGH);
	estado = true;
}

void Rele::releOff(){
    Serial.print("Apagar Relay ");
    Serial.println(rele);
    digitalWrite(pin, LOW);
	estado = false;
}

void Rele::muestraProg(){
	  if(prog){
 	      Serial.print("Estado rele ");
          Serial.print(rele);
          Serial.print(" Inicio ");
          Serial.print(hi);
          Serial.print(":");
          Serial.print(mi);
          Serial.print(".");
          Serial.print(si);
          Serial.print(" Fin ");
          Serial.print(hf);
          Serial.print(":");
          Serial.print(mf);
          Serial.print(".");
          Serial.println(sf);
	  }
	  else {
 	      Serial.print("Estado rele ");
          Serial.print(rele);
          Serial.println(" : NO PROGRAMADO");
	  }
}

void  Rele::setProg(int horai,int mini,int segi,int horaf,int minf,int segf){
          hi = horai;
          mi = mini;
          si = segi;
          hf = horaf;
          mf = minf;
          sf = segf;
	  Serial.print("Programando rele ");
          Serial.print(rele);
          Serial.print(" Inicio ");
          Serial.print(horai);
          Serial.print(":");
          Serial.print(mini);
          Serial.print(".");
          Serial.print(segi);
          Serial.print(" Fin ");
          Serial.print(horaf);
          Serial.print(":");
          Serial.print(minf);
          Serial.print(".");
          Serial.println(segf);
         // releOn();
	     // OnTick_t funcion[]={encender1,encender2,encender3,encender4};
	     // OnTick_t funcioff[]={apagar1,apagar2,apagar3,apagar4};
	      //alarmRepeat(horai,mini,segi,funcion);
	      //alarmRepeat(horaf,minf,segf,funcioff);
          prog = true;
}

boolean Rele::isOn(){
     return estado;
}




