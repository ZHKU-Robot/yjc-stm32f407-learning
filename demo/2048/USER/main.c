#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "rng.h"
#include "key.h"
#include "game.h"
#include "mpu6050.h"

int main(void)
{
	//u8 x = 0;
	// u8 lcd_id[12]; //存放LCD ID字符串

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置系统中断优先级分组2
	delay_init(168);								//初始化延时函数
	uart_init(115200);								//初始化串口波特率为115200

	LED_Init(); //初始化LED
	LCD_Init(); //初始化LCD FSMC接口
	KEY_Init();
	MPU_Init();		   //初始化MPU6050
	POINT_COLOR = RED; //设置字体为红色
	LCD_ShowString(30, 50, 200, 16, 16, "Explorer STM32F4");
	LCD_ShowString(30, 70, 200, 16, 16, "MPU6050 TEST");
	LCD_ShowString(30, 90, 200, 16, 16, "ATOM@ALIENTEK");
	LCD_ShowString(30, 110, 200, 16, 16, "2020/10/29");
	LCD_ShowString(30, 130, 200, 16, 16, "MPU6050 OK");
	POINT_COLOR = BLUE; //设置字体为蓝色
	LCD_ShowString(250, 70, 200, 16, 16, "Pitch:    . C");
	LCD_ShowString(250, 90, 200, 16, 16, " Roll:    . C");
	LCD_ShowString(250, 110, 200, 16, 16, " Yaw :    . C");
	while (mpu_dmp_init())
	{
		LCD_ShowString(30, 130, 200, 16, 16, "MPU6050 Error");
		delay_ms(200);
		LCD_Fill(30, 130, 239, 130 + 16, WHITE);
		delay_ms(200);
	}
	initRandom();
	POINT_COLOR = RED;
	while (1)
	{

		rectPrint();
		moveListen();
		// delay_ms(10);
		// LED0 = !LED0; //LED闪烁
	}
}
