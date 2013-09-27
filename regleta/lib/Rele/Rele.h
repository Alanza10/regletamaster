#ifndef Rele_h
#define Rele_h

#include "Arduino.h"

class Rele{
	private:
	 int pin;
	 int rele;
	 int hi,mi,si,hf,mf,sf;
     boolean prog,estado;

	public:
	 void setRele(int rel);
  	 void setPin(int p);
	 void setOutput();
	 void setInput();
	 void releOn();
	 void releOff();
	 void setProg(int horai,int mini,int segi,int horaf,int minf,int segf);
     void muestraProg();
     boolean isOn();
};

#endif

