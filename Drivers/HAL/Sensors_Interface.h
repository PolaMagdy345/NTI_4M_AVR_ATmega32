/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 1/11/2023                   */
/*     Version:	V.1                      */
/*     Description: Sensors_Interface.h  */
/*****************************************/

#ifndef SENSORS_INTERFACE_H_
#define SENSORS_INTERFACE_H_

#include "ADC_Interface.h"

/*return temp (c*10) */
u16 TEMP_Read(void);

s16 Result_Interpolation(u16 adc,u16 ADC1,u16 ADC2,u16 Sensor_Point1,u16 Sensor_Point2);
u16 PRESS_Read(void);			//MPX function pressure read
u16 TEMP_ReadSensors(ADC_Channel_type ch);




#endif /* SENSORS_INTERFACE_H_ */