/********************************************************************************/
/*								Author: Paula Magdy								*/
/*								Date:	26/10/2023								*/
/*								Version:	V.1									*/
/*								Description: EX_Interrupt_Interface.h			*/
/********************************************************************************/

#ifndef EX_INTERRUPT_INTERFACE_H_
#define EX_INTERRUPT_INTERFACE_H_

typedef enum{
	LOW_LEVEL=0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE,
}TriggerEdge_type;

typedef enum{
	EX_INT0=0,
	EX_INT1,
	EX_INT2
}ExInterruptSource_type;

void EXI_Init(void);

void EXI_Enable(ExInterruptSource_type Interrupt);
void EXI_Disable(ExInterruptSource_type Interrupt);
void EXI_TriggerEdge(ExInterruptSource_type Interrupt,TriggerEdge_type Edge);
void EXI_SetCallBack(ExInterruptSource_type Interrupt,void(*LocalPtr)(void));





#endif