#include "reg52.h"
#include "Beep.h"
#include "Utils.h"
#include "DigitalTube.h"
#define contentP P0
sbit seg1= P2^4; //定义数码 管 位 驱动 端 
sbit seg2= P2^5; //定义数码 管 位 驱动 端 
sbit seg3= P2^6; //定义数码 管 位 驱动 端
sbit seg4= P2^7; //定义数码 管 位 驱动 端 
unsigned char code codeTable[]={ 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f,0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};
#define EMPTY_CODE 0x00
#define MINUS_CODE 0x20
#define DARK 
 //共阳段码表
unsigned char curValue[4]={'E','E','E','E'};
unsigned char curIndex=0;
static void putCode(unsigned char whileSeg, unsigned char value);

void putCode(unsigned char whichSeg, unsigned char value){
	UART_outChar(value);
	switch(whichSeg){
		case 0:
		  seg1=1;
		  seg2=0;
	      seg3=0;
	      seg4=0;
		break;
		case 1:
		 seg1=0;
		  seg2=1;
	      seg3=0;
	      seg4=0;
		break;
		case 2:
		 seg1=0;
		  seg2=0;
	      seg3=1;
	      seg4=0;
		break;
		case 3:
		 seg1=0;
		  seg2=0;
	      seg3=0;
	      seg4=1;
		break;
		default:
		break;
	}

	 switch(value){
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			contentP=codeTable[value-'0'];
			break;
		case 'E':
		    contentP=0x79;
			break;
		case 0:
			contentP=0x00;
			break;
		case '-':
			contentP=MINUS_CODE;
			break;
		default:
			break;
	 }
}

unsigned char curSeg=0;
void digitalTubeOutput(int value){
  if(value>=9999){
	seg1=1;
	seg2=1;
	seg3=1;
	seg4=1;
	contentP=codeTable[9];
  }
  else if (value < -999){

  }
}

void  digitalShow(){
	 putCode(curIndex, curValue[curIndex]);
	 curIndex++;
	 if(curIndex == 4)
	   curIndex=0;
}
void setDigitalValue(int value){
	//beep(value);
	UART_outStr("Test\n");
	UART_out(value);
	if(value>9999){
	  	curValue[0]='E';
		curValue[1]='E';
		curValue[2]='E';
		curValue[3]='E';
	}
	else if(value >-1){
		curValue[0]=value/1000+'0';
		curValue[1]=value%1000/100+'0';
		curValue[2]=value%100/10+'0';
		curValue[3]=value%10+'0';
	}
	//todo
}