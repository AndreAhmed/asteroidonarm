 
#include "fsmc_sram.h"
#include "fonts.h"
#include "lcd.h"

#define Bank1_LCD_D		((uint32_t)0x60020000)		//disp Data ADDR
#define Bank1_LCD_C		((uint32_t)0x60000000)	 //disp Reg ADDR

unsigned long color1=0;
 

#define fbWidth		200
#define fbHeight	 110

u16 frameBuffer[fbWidth*fbHeight]; // 239*100*16bit

 
void LCD_WR_REG(unsigned int index)
{
	*(__IO uint16_t *) (Bank1_LCD_C)= index;

}
 
void LCD_WR_CMD(unsigned int index,unsigned int val)
{	
	*(__IO uint16_t *) (Bank1_LCD_C)= index;	
	*(__IO uint16_t *) (Bank1_LCD_D)= val;
}

unsigned int LCD_RD_data(void){
	unsigned int a=0;
 
	a=*(__IO uint16_t *) (Bank1_LCD_D); //L

	return(a);	
}
 
void		LCD_WR_Data(unsigned int val)
{	 
	*(__IO uint16_t *) (Bank1_LCD_D)= val; 	
}

void LCD_WR_Data_8(unsigned int val)
{
	*(__IO uint16_t *) (Bank1_LCD_D)= val;
}

void LCD_Reset(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_1);
	Delay(0xAFFFFf);					   
	GPIO_SetBits(GPIOE, GPIO_Pin_1 );		 	 
	Delay(0xAFFFFf);	
}

void Delay(__IO uint32_t nCount)
{
		for(; nCount != 0; nCount--);
}
	
void LCD_Init(void)
{
	
LCD_Reset();	 

//############# void Power_Set(void) ################//
LCD_WR_CMD(0x0000,0x0001);
Delay(10);

LCD_WR_CMD(0x0015,0x0030);
LCD_WR_CMD(0x0011,0x0040);
LCD_WR_CMD(0x0010,0x1628);
LCD_WR_CMD(0x0012,0x0000);
LCD_WR_CMD(0x0013,0x104d);
Delay(10);
LCD_WR_CMD(0x0012,0x0010);
Delay(10);
LCD_WR_CMD(0x0010,0x2620);
LCD_WR_CMD(0x0013,0x344d); //304d
Delay(10);

LCD_WR_CMD(0x0001,0x0100);
LCD_WR_CMD(0x0002,0x0300);
LCD_WR_CMD(0x0003,0x1030);
LCD_WR_CMD(0x0008,0x0604);
LCD_WR_CMD(0x0009,0x0000);
LCD_WR_CMD(0x000A,0x0008);

LCD_WR_CMD(0x0041,0x0002);
LCD_WR_CMD(0x0060,0x2700);
LCD_WR_CMD(0x0061,0x0001);
LCD_WR_CMD(0x0090,0x0182);
LCD_WR_CMD(0x0093,0x0001);
LCD_WR_CMD(0x00a3,0x0010);
Delay(10);

//################# void Gamma_Set(void) ####################//
 LCD_WR_CMD(0x30,0x0000);		
 LCD_WR_CMD(0x31,0x0502);		
 LCD_WR_CMD(0x32,0x0307);		
 LCD_WR_CMD(0x33,0x0305);		
 LCD_WR_CMD(0x34,0x0004);		
 LCD_WR_CMD(0x35,0x0402);		
 LCD_WR_CMD(0x36,0x0707);		
 LCD_WR_CMD(0x37,0x0503);		
 LCD_WR_CMD(0x38,0x1505);		
 LCD_WR_CMD(0x39,0x1505);
 Delay(10);

//################## void Display_ON(void) ####################//
 LCD_WR_CMD(0x0007,0x0001);
 Delay(10);
 LCD_WR_CMD(0x0007,0x0021);
 LCD_WR_CMD(0x0007,0x0023);
 Delay(10);
 LCD_WR_CMD(0x0007,0x0033);
 Delay(10);
 LCD_WR_CMD(0x0007,0x0133);
 	 
	 // fill the GRAM buffer
		*(__IO uint16_t *) (Bank1_LCD_C)= 34;
		for(color1=0;color1<76800;color1++)
		{
			LCD_WR_Data(LCD_Black);
		}
 
}
 
 void LCD_PutChar(unsigned int x,unsigned int y,u8 c,unsigned int charColor,unsigned int bkColor)
{


#define MAX_CHAR_POSX 232
#define MAX_CHAR_POSY 304
	u8 temp;
	u8 pos,t;
	if(x>MAX_CHAR_POSX||y>MAX_CHAR_POSY)return;
 
		LCD_WriteRegister(0x0050, x); // Horizontal GRAM Start Address
		LCD_WriteRegister(0x0051, x+5); // Horizontal GRAM End Address
		LCD_WriteRegister(0x0052, y); // Vertical GRAM Start Address
		LCD_WriteRegister(0x0053, y+11); // Vertical GRAM Start Address
		LCD_WriteRegister(32, x);
		LCD_WriteRegister(33, y);	//
		LCD_WriteIndex(34);
	 

	c=c-' ';
	for(pos=0;pos<12;pos++)
	{
		temp=asc2_1206[c][pos];
		for(t=0;t<6;t++)
		{
			if(temp&0x01)LCD_WR_Data(charColor);
			else LCD_WR_Data(bkColor);
			temp>>=1;
		}
	}
}

void LCD_Text(unsigned int x, unsigned int y, char *text, unsigned int charColor, unsigned int bkColor)
{
	u8 i=0;
	//for (i=0;i<len;i++)
	while(*text)
	{
		LCD_PutChar((x+8*i), y, *text++, charColor, bkColor);
		i++;
	}
}

 

 
void lcd_wr_pixel(unsigned int a, unsigned int b, unsigned int e)		
{
  LCD_WR_CMD(0x20, a);
	LCD_WR_CMD(0x21, b);
	LCD_WR_Data(e);
}
 
 

void LCD_WriteRegister(unsigned int index,unsigned int dat)
{
 
	*(__IO uint16_t *) (Bank1_LCD_C)= index;
	*(__IO uint16_t *) (Bank1_LCD_D)= dat;
}

__inline void LCD_SetCursor(unsigned int x,unsigned int y)
{


	LCD_WriteRegister(32, y);
	LCD_WriteRegister(33, 319-x);
}

__inline void LCD_WriteIndex(unsigned int idx)
{
 
	*(__IO uint16_t *) (Bank1_LCD_C)= idx;
}

void LCD_WritetoFB(int x, int y, int color)
{
	frameBuffer[x + y*fbWidth] = color;
}

void LCD_ClearFB()
{

	u16 pixel;
	for( pixel = 0; pixel< fbHeight*fbWidth; pixel++)
	{
		frameBuffer[pixel]= 0x0;

	}

}
void LCD_Flip()
{

	int	i;

	// set cursor to 0,0
	LCD_WriteRegister(32, 0);
  LCD_WriteRegister(33, 0);
	
	LCD_WriteRegister(0x0050,0x00);//GRAM horizontal start position
	LCD_WriteRegister(0x0051,fbWidth-1);//GRAM horizontal end position
	LCD_WriteRegister(0x0052,0);//Vertical GRAM Start position
	LCD_WriteRegister(0x0053,fbHeight-1);//Vertical GRAM end position
	LCD_WriteIndex(0x0022);
 
		for(i=0;i<fbWidth*fbHeight;i++)
		{
		 
			*(__IO uint16_t *) (Bank1_LCD_D)= frameBuffer[i];; 	

		}
	 
}


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
