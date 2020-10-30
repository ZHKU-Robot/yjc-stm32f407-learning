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
	// u8 lcd_id[12]; //���LCD ID�ַ���
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����ϵͳ�ж����ȼ�����2
	delay_init(168);								//��ʼ����ʱ����
	uart_init(115200);								//��ʼ�����ڲ�����Ϊ115200

	LED_Init(); //��ʼ��LED
	LCD_Init(); //��ʼ��LCD FSMC�ӿ�

	// POINT_COLOR = RED;								   //������ɫ����ɫ
	// sprintf((char *)lcd_id, "LCD ID:%04X", lcddev.id); //��LCD ID��ӡ��lcd_id���顣

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
