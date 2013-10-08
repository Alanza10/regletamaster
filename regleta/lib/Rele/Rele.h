#ifndef Rele_h
#define Rele_h

#include "Arduino.h"

class Rele{
	private:
	 int pin;
	 int rele;
     boolean prog,estado;

	public:
	 int hi,mi,si,hf,mf,sf;
	 void setRele(int rel);
  	 void setPin(int p);
	 void setOutput();
	 void setInput();
	 void releOn();
	 void releOff();
	 void setProg(int horai,int mini,int segi,int horaf,int minf,int segf);
	 void resetProg();
     void muestraProg();
     boolean isOn();
     boolean isProg();

};

#endif

