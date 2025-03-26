#include "reg52.h"
#include "Utils.h"

#include "Beep.h"
#define ON 0
#define OFF 1
sbit buzzer=  P2^3;
sbit P1_0= P1^0;  //0x90
void beep(unsigned char  n){
	unsigned char i;
	i = 0;
	while(i<n){
		i++;
		P1_0=0;
		buzzer=ON;
		sleep(5);//beep
		buzzer=OFF;
		P1_0=1;
		//silence
		sleep(5);
	}
}