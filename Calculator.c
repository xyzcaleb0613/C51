#include <stdio.h>

#include "DigitalTube.h"
#include "Utils.h"
#include "Calculator.h"
#define POSITIVE 1
#define NEGATIVE 0
unsigned char operatorC=0;
int oprand1=0;
int oprand2=0;
bit oprand1Sign= POSITIVE;
bit oprand2Sign= POSITIVE;
bit hasLaunch = 0;//是否开始了
unsigned char code buffer[64];
static void update(int* oprand, unsigned char n){
	(*oprand)*=10;
	(*oprand)+=n;
} 
void calculate(unsigned char n){
	UART_outStr("start\n");
	if(n<':' && n > '/'){
	//number
		UART_out(1);
		if(operatorC == 0){
		   //oprand1
		  update(&oprand1,n-'0');
		}
		else{
			//oprand2
			update(&oprand2,n-'0');
		}
		if(hasLaunch==0) {
			hasLaunch=1;
		}
	}
	else if(n=='+' || n=='-'){
		UART_out(2);
	    if(hasLaunch==0) {
			hasLaunch=1;
			if(n=='+')
				oprand1Sign=POSITIVE;
			else
				oprand1Sign=NEGATIVE;	
		}
		else{
		  if(operatorC==0){
		  	operatorC=n;	   
		  }
		  else{
		  	 if(n=='+')
				oprand2Sign=POSITIVE;
			else
				oprand2Sign=NEGATIVE;
		  }
		}
	}
	else if(n=='='){
		UART_out(3);
		if(oprand1Sign==NEGATIVE){
			   oprand1*=-1;
		}
		if(oprand2Sign==NEGATIVE){
			   oprand2*=-1;
		}
		if(operatorC == '+'){
			 //digitalTubeOutput(oprand1+oprand2);
			 setDigitalValue(oprand1 + oprand2);
		}
		else if(operatorC == '-'){
			//digitalTubeOutput(oprand1-oprand2);
			setDigitalValue(oprand1 - oprand2);
		}
		operatorC=0;
		oprand1=0;
		oprand2=0;
		hasLaunch=0;
	}
	else{
	 	UART_outStr("4");
		//UART_out(n);
		sprintf(buffer,"Wrong code: %d!!!\n", n);
		UART_outStr(buffer);
	}
}