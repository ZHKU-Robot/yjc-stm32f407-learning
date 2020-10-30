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
	// u8 lcd_id[12]; //���LCD ID�ַ���

		snakeNode *snake;

	snake = initSnake();
	createFood();

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����ϵͳ�ж����ȼ�����2
	delay_init(168);								//��ʼ����ʱ����
	uart_init(115200);								//��ʼ�����ڲ�����Ϊ115200

	LED_Init(); //��ʼ��LED
	LCD_Init(); //��ʼ��LCD FSMC�ӿ�

	// POINT_COLOR = RED;								   //������ɫ����ɫ
	// sprintf((char *)lcd_id, "LCD ID:%04X", lcddev.id); //��LCD ID��ӡ��lcd_id���顣

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
