#include "reg52.h"
#include "Utils.h"
void sleep(unsigned int nMs){
	int i,j;
	for(i=0;i<nMs;i++){
		for(j=0;j<112;j++);
	}
}
void UART_outStr(unsigned char c[]){
	while(*c != 0){
		SBUF=*c;
		sleep(1);
		c++;
	}	
}
void UART_out(int value){
	SBUF=value/1000+'0';
	sleep(1);
	SBUF=value%1000/100+'0';
	sleep(1);
	SBUF=value%100/10+'0';
	sleep(1);
	SBUF=value%10+'0';
}

void UART_outChar(unsigned char c){
	SBUF=c;
	sleep(1);
}