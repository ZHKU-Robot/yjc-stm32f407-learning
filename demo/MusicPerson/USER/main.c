#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "animation.h"
#include "musicperson.h"
int main(void)
{
	u8 x = 0;
	// u8 lcd_id[12]; //存放LCD ID字符串
	Person *p = personInit();

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

	p->x1 = 0;
	p->y1 = 550;
	p->x2 = 100;
	p->y2 = 700;
	while (1)
	{


		personMove(p);
		drawPerson(p);
		drawGround(p);
		keyListen();
		// if (x++ % 12 == 0)
		// {

		// 	x = 0;
		// }
	}
}
