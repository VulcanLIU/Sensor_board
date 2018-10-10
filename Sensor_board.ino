#include <Wire.h>

//激光
volatile int sure=0,s,x,k,value1,value2;
uint8_t s_h,s_l,x_h,x_l,k_h,k_l;

float JG_R1[5];
float JG_R2[5];
float JG_B[5];
//光电对管
#define switch1 3
#define switch2 4

void setup()
{
	Wire.begin(8);
	Serial.begin(19200);
	Serial1.begin(19200);
	Serial2.begin(19200);
	Serial3.begin(19200);
	//光电对管
	pinMode(switch1,INPUT);
	pinMode(switch2,INPUT);
	//颜色

	Wire.onReceive(receive);
	Wire.onRequest(request);
}


void loop()
{
	if(sure==1)
	{ 
		//#第一激光
		Serial1.write("D");
		for (int i = 0; i < 2; i++)
		JG_R1[i] = Serial1.parseFloat();//0.01m 2.33m
		s =100*JG_R1[0];//变成233cm
		//分低八位高八位
		s_h = s>>8;s_l=(s&0xff);
		
		Serial.print(s);
		Serial.print("  ");
		
		//#第二激光
		Serial2.write("D");
		for (int i = 0; i < 2; i++)
		JG_R2[i] = Serial2.parseFloat();
		x =100*JG_R2[0];
		//分低八位高八位
		x_h = x>>8;x_l=(x&0xff);
		
		Serial.print(x);
		Serial.print("  ");
		
		//#第三激光
		Serial3.write("D");
		for (int i = 0; i < 2; i++)
		JG_B[i] = Serial3.parseFloat();
		k=100*JG_B[0];
		//分低八位高八位
		k_h = k>>8;k_l=(k&0xff);
		
		Serial.println(k);
		
		//#光电对管
		value1=digitalRead(switch1);
		value2=digitalRead(switch2);
	}
	sure=0;
}


void request()
{
	//bytes 1- 8
	Wire.write(s_h);
	Wire.write(s_l);
	Wire.write(x_h);
	Wire.write(x_l);
	Wire.write(k_h);
	Wire.write(k_l);
	Wire.write(value1);
	Wire.write(value2);
}

void receive()
{
	int a=Wire.read();
	if(a==8)
	{
		sure = 1;
	}
}
