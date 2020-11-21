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
	// u8 lcd_id[12]; //���LCD ID�ַ���
	Person *p = personInit();

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
