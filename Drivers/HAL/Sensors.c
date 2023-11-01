/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 1/11/2023                   */
/*     Version:	V.1                      */
/*     Description: Sensors.c     		 */
/*****************************************/

#include "StdTypes.h"
#include "ADC_Interface.h"
#include "Sensors_Cfg.h"
#include "Sensors_Interface.h"

#define ADC_X 0
#define TEMP_Y 1
#define POINTS 100
u16 arr[POINTS][2]={{10,1},
				{30,5},
				{40,6},
				{60,10},
				{70,15},
				{100,25},
				{120,28},
				{150,35},
				{200,43},
				{300,60},
				{400,76}
				};
s16 Result_Interpolation(u16 adc,u16 ADC1,u16 ADC2,u16 Sensor_Point1,u16 Sensor_Point2)//500 204 816 15 120
{
	u16 Result;
	//slope=((Sensor_Point2-Sensor_Point1)/(ADC2-ADC1))*10;
	Result=((((u32)(Sensor_Point2-Sensor_Point1)*(adc-ADC1)*10)+((ADC2-ADC1)/2))/(ADC2-ADC1))+(Sensor_Point1*10); //(ADC2-ADC1)/2 for greater accuracy/
														 														  //if we need to get >=0.15 so equal 0.2 or <=0.15 equal 0.1
	
	return Result;		//it will return the result *10 for 0.1 percision
}

u16 temp(u16 adc)
{
	u8 i;
	s16 temp=0;
	for(i=0;i<POINTS;i++)
	{
		if(adc<arr[i][ADC_X])
		{
			temp=Result_Interpolation(adc,arr[i-1][ADC_X],arr[i][ADC_X],arr[i-1][TEMP_Y],arr[i][TEMP_Y]);
		}
	}
	return temp;
}

u16 TEMP_Read(void)
{
	u16 volt=ADC_VoltRead(LM35_CH);
	u16 temp;
	
	temp=volt;
	return temp;
}
u16 TEMP_ReadSensors(ADC_Channel_type ch)
{
	u16 volt=ADC_VoltRead(ch);
	u16 temp;
	
	temp=volt;
	return temp;
}


u16 PRESS_Read(void)			//MPX function pressure read
{
	u16 adc=ADC_Read(MPX_CH);
	u16	PRESSURE;
	
	PRESSURE=Result_Interpolation(adc,55,976,15,115);
	
	return PRESSURE;		//MPX result in Kpa *10
}