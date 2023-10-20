#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_Interface.h"
#include "Utils.h"


int main(void)
{
	u8 x=0;
	DIO_Init();

    while (1)
    {
		for(int i=0;i<10;i++)
		{
			for(int j=0;j<=50;j++)
			{
				PORTA=0x08;
				PORTB=((x<<1)&0xf0)|(x&0x0f);
				_delay_ms(5);
				PORTA=0x04;
				PORTB=0x60;
				_delay_ms(2);
				PORTB=0;
				PORTA=0x04;
				_delay_ms(3);
			}
				x++;
		}
		if(x>=9)
		{
			x=0;
			PORTB=0;
		}

    }
}