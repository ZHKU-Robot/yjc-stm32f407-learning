#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "snake.h"
#include "key.h"
int main(void)
{
	u8 x = 0;
	// u8 lcd_id[12]; //存放LCD ID字符串

		snakeNode *snake;

	snake = initSnake();
	createFood();

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置系统中断优先级分组2
	delay_init(168);								//初始化延时函数
	uart_init(115200);								//初始化串口波特率为115200

	LED_Init(); //初始化LED
	LCD_Init(); //初始化LCD FSMC接口

	// POINT_COLOR = RED;								   //画笔颜色：红色
	// sprintf((char *)lcd_id, "LCD ID:%04X", lcddev.id); //将LCD ID打印到lcd_id数组。

	// POINT_COLOR=RED;
	KEY_Init();

	while (1)
	{
		snakeTurn();
		showTitle();
		if (x % 6 == 0)
		{
			snakeMove(snake);
			x=0;
		}
		foodPrint();
		LED0 = !LED0;
		x++;
		delay_ms(10);
	}
}
