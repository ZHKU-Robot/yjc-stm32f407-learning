#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "animation.h"
int main(void)
{
	u8 x = 0;
	// u8 lcd_id[12]; //存放LCD ID字符串
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置系统中断优先级分组2
	delay_init(168);								//初始化延时函数
	uart_init(115200);								//初始化串口波特率为115200

	LED_Init(); //初始化LED
	LCD_Init(); //初始化LCD FSMC接口

	// POINT_COLOR = RED;								   //画笔颜色：红色
	// sprintf((char *)lcd_id, "LCD ID:%04X", lcddev.id); //将LCD ID打印到lcd_id数组。

	// POINT_COLOR=RED;
	KEY_Init();

	// LCD_Fill(200, 100, 250, 150, BLACK);
	while (1)
	{
		delay_ms(1000);
		LCD_Fill(200, 100, 250, 150, BLACK);
		animationMove(200, 100, 250, 150, -100, 1, 'y');
		LCD_Fill(200, 100, 250, 150, BLACK);
		animationMove(200, 100, 250, 150, 100, 1, 'y');
		LCD_Fill(200, 100, 250, 150, BLACK);
		animationMove(200, 100, 250, 150, -100, 1, 'x');
		LCD_Fill(200, 100, 250, 150, BLACK);
		animationMove(200, 100, 250, 150, 100, 1, 'x');
	}
}
