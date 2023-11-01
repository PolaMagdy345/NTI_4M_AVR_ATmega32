/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 1/11/2023                   */
/*     Version:	V.1                      */
/*     Description: Timers_Services.h    */
/*****************************************/

#ifndef TIMERS_SERVICES_H_
#define TIMERS_SERVICES_H_




void PWM_Init(void);
void PWM_Freq_KHZ(u16 freq);
void PWM_Freq_HZ(u16 freq);
void PWM_Duty(u16 duty);

void Timer1_SetInterruptTime_ms (u16 time,void(*LocalFptr)(void));
void Timer1_SetInterruptTime_us (u16 time,void(*LocalFptr)(void));
void Timer1_SetInterruptTime_s (u16 time,void(*LocalFptr)(void));
//void PWM_Measure(u32* Pfreq,u8* Pduty);
void PWM_Measure(u32* Pfreq,u8* Pduty,u32 timeout);
void PWM_Measure2(u32* Pfreq,u8* Pduty);
void Servo_ADC_SetPosition(u16 P);		//for timer1

#endif /* TIMERS_SERVICES_H_ */