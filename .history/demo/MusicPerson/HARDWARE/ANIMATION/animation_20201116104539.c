#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "dma.h"

//ALIENTEK 探索者STM32F407开发板 实验23
//DMA 实验-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司
//作者：正点原子 @ALIENTEK

#define SEND_BUF_SIZE 962 //发送数据长度,最好等于sizeof(TEXT_TO_SEND)+2的整数倍.
u8 TEXT_TO_SEND[960];
u8 SendBuff[SEND_BUF_SIZE]; //发送数据缓冲区

u8 send = 0;
u16 screenHeight = 800;
u16 screenWidth = 480;
u16 i, j, color;

int main(void)
{
    u16 i;
    u8 t = 0;
    u8 j, mask = 0;
    float pro = 0;                                  //进度
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置系统中断优先级分组2
    delay_init(168);                                //初始化延时函数
    uart_init(115200);                              //初始化串口波特率为115200
    LED_Init();                                     //初始化LED
    LCD_Init();                                     //LCD初始化
    KEY_Init();                                     //按键初始化

    POINT_COLOR = RED;
    LCD_ShowString(30, 50, 200, 16, 16, "Explorer STM32F4");
    LCD_ShowString(30, 70, 200, 16, 16, "DMA TEST");
    LCD_ShowString(30, 90, 200, 16, 16, "ATOM@ALIENTEK");
    LCD_ShowString(30, 110, 200, 16, 16, "2014/5/6");
    LCD_ShowString(30, 130, 200, 16, 16, "KEY0:Start");
    POINT_COLOR = BLUE; //设置字体为蓝色
    //显示提示信息
    j = 1;
    for (i = 0; i < SEND_BUF_SIZE; i++) //填充ASCII字符集数据
    {
        if (t >= j) //加入换行符
        {
            if (mask)
            {
                SendBuff[i] = 0x0a;
                t = 0;
            }
            else
            {
                SendBuff[i] = 0x0d;
                mask++;
            }
        }
        else //复制TEXT_TO_SEND语句
        {
            mask = 0;
            SendBuff[i] = TEXT_TO_SEND[t];
            t++;
        }
    }
    POINT_COLOR = BLUE; //设置字体为蓝色
    i = 0;
    while (1)
    {
        t = KEY_Scan(0);
        if (t == KEY0_PRES) //KEY0按下
        {
            printf("\r\nDMA DATA:\r\n");
            LCD_ShowString(30, 150, 200, 16, 16, "Start Transimit....");
            LCD_ShowString(30, 170, 200, 16, 16, "   %"); //显示百分号

            while (!send)
            {
                //sprintf((char*)p,"ATK-8266%s测试%02d\r\n",ATK_ESP8266_WORKMODE_TBL[netpro],t/10);//测试数据
                t = KEY_Scan(0);

                for (i = 0; i < screenHeight; i++)
                {
                    for (j = 0; j < screenWidth; j++)
                    {
                        color = LCD_ReadPoint(i, j);
                        TEXT_TO_SEND[j] = color >> 8;
                        TEXT_TO_SEND[j + 480] = color & 0x00ff;
                    }
                    printf("still transmitting");
                    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE); //使能串口 1 的 DMA 发送
                    MYDMA_Enable(DMA2_Stream7, SEND_BUF_SIZE);     //开始一次 DMA 传输！
                    while (1)
                    {
                        printf("still transmitting");
                        if (DMA_GetFlagStatus(DMA2_Stream7, DMA_FLAG_TCIF7) != RESET) //等待DMA2_Steam7传输完成
                        {
                            DMA_ClearFlag(DMA2_Stream7, DMA_FLAG_TCIF7); //清除DMA2_Steam7传输完成标志
                            break;
                        }
                        pro = DMA_GetCurrDataCounter(DMA2_Stream7); //得到当前还剩余多少个数据
                        pro = 1 - pro / SEND_BUF_SIZE;              //得到百分比
                        pro *= 100;                                 //扩大100倍
                        LCD_ShowNum(30, 170, pro, 3, 16);
                    }
                    LCD_ShowNum(30, 170, 100, 3, 16);                            //显示100%
                    LCD_ShowString(30, 150, 200, 16, 16, "Transimit Finished!"); //提示传送完成
                    //delay_ms(200);
                    if (t == KEY1_PRES)
                    {
                        send = 1;
                        LCD_ShowString(30 + 54, 100, 200, 12, 12, "end...");
                    }
                    i++;
                    delay_ms(10);
                    if (i == 20)
                    {
                        LED0 = !LED0; //提示系统正在运行
                        i = 0;
                    }
                }
            }
            //等待DMA传输完成，此时我们来做另外一些事，点灯
            //实际应用中，传输数据期间，可以执行另外的任务
        }
    }
}
