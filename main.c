#include "reg52.h"
#include "Beep.h"
#include "Utils.h"
#include "DigitalTube.h"
#include "Calculator.h"
sbit P1_0= P1^0;  //0x90
sbit P1_1= P1^1;  //0x90
sbit P1_2= P1^2;  //0x90
sbit P1_3= P1^3;  //0x90
void init_uart(); //���пڳ�ʼ����������
void init_uart(){
	TMOD=0x20;//��ʱ��
	TL1=0xfd;//9600bps
	TH1=0xfd;

	TR1=1;//������ʱ��

	SM0=0;//���ڹ�����ʽ
	SM1=1;//���ڹ�����ʽ
	REN=1;//�����ڽ���
	PCON=0x00;//�ޱ�Ƶ
	EA=1;
	ES=1;
}

unsigned char number=0; //���� ��ʾ ����
void uart_handler() interrupt 4 { 
	if(RI == 1){
		RI = 0; //�����0���ձ�־λ 
		number = SBUF; //�����յ�����Ϣ��ֵ�� num 
	}
	if(TI==1)
		TI=0;
}

void checkUART(){
   if(number != 0){
   	   if(TI==1){
	 	TI=0;
	   }
	   SBUF=number;
	   if(number<='9'&&number>='0')
	   		beep(number-'0');
	   else
			beep(1);
	   sleep(2);
	   if(TI==1){
	 	TI=0;
	   }
	   SBUF='\n';
	   calculate(number);
	   number=0;
	   UART_outStr("**");
   }
}
unsigned char code table0[]="Hello world\n";
void testUART_send(unsigned char c);
void testUART_send(unsigned char c){
	 unsigned char j = 0;
	 while(j<c){
	 	unsigned char i = 0;
	 	for(;i<13;i++){
	 		SBUF=table0[i];
	 		if(TI==1){
	 			TI=0;
	 		}
			sleep(2);
	 	} //for
		j++;
	 }
}
void main(){
	init_uart();
	sleep(10);
	testUART_send(2);
	//testDigitalTube();
    beep(10);
	digitalTubeOutput(9999);
	while(1){
	  checkUART();
	  digitalShow();
	};
}