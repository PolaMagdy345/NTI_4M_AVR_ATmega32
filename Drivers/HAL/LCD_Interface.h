#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_Init(void);
void LCD_Clear(void);
void LCD_WriteChar(c8 ch);
void LCD_WriteString(u8*str);
void LCD_WriteNumber(s32 num);
void LCD_GoTo(u8 line,u8 cell);



#endif /* LCD_INTERFACE_H_ */