# **待机唤醒实验** 

## **1 STM32F4** **待机模式简介**

### 进入待机模式前，必须按如下操作处理：

1. 禁止 RTC 中断（ALRAIE、ALRBIE、WUTIE、TAMPIE 和 TSIE 等）。 
2. 清零对应中断标志位。 
3. 清除 PWR 唤醒(WUF)标志（通过设置 PWR_CR 的 CWUF 位实现）。 
4. 重新使能 RTC 对应中断。 
5. 进入低功耗模式。 

### 待机模式唤醒的方法。

1. **使能电源时钟。** 
2. **设置** **WK_UP** **引脚作为唤醒源。**
3. **设置** **SLEEPDEEP** **位，设置** **PDDS** **位，执行** **WFI** **指令，进入待机模式。** 
4. **最后编写** **WK_UP** **中断函数。**

## **2** **硬件设计**

### 本实验用到的硬件资源有： 

#### 1） 指示灯 DS0 

#### 2） KEY_UP 按键 

#### 3） TFTLCD 模块 

本章，我们使用了 KEY_UP 按键用于唤醒和进入待机模式。然后通过 DS0 和 TFTLCD 模 块来指示程序是否在运行。这几个硬件的连接前面均有介绍。 

## **3** **软件设计** 

打开待机唤醒实验工程，我们可以发现工程中多了一个 wkup.c 和 wkup.h 文件，相关的用 户代码写在这两个文件中。

同时，对于待机唤醒功能，我们需要引入 stm32f4xx_pwr.c 和 stm32f4xx_pwr.h 文件。 

打开 wkup.c，可以看到如下关键代码： 

#### void Sys_Enter_Standby(void)

//系统进入待机模式

#### u8 Check_WKUP(void) 

//检测WKUP脚的信号
//返回值1:连续按下3s以上
//      0:错误的触发	



#### void EXTI0_IRQHandler(void)

//中断,检测到PA0脚的一个上升沿.	  
//中断线0线上的中断检测



#### void WKUP_Init(void)

//PA0 WKUP唤醒初始化

```c
//系统进入待机模式
void Sys_Enter_Standby(void)
{		
  while(WKUP_KD);			//等待WK_UP按键松开(在有RTC中断时,必须等WK_UP松开再进入待机)
 
	RCC_AHB1PeriphResetCmd(0X04FF,ENABLE);//复位所有IO口
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//使能PWR时钟		 
	 
	PWR_BackupAccessCmd(ENABLE);//后备区域访问使能

	//这里我们就直接关闭相关RTC中断
	RTC_ITConfig(RTC_IT_TS|RTC_IT_WUT|RTC_IT_ALRB|RTC_IT_ALRA,DISABLE);//关闭RTC相关中断，可能在RTC实验打开了。
	RTC_ClearITPendingBit(RTC_IT_TS|RTC_IT_WUT|RTC_IT_ALRB|RTC_IT_ALRA);//清楚RTC相关中断标志位。
	
	PWR_ClearFlag(PWR_FLAG_WU);//清除Wake-up 标志
	
	PWR_WakeUpPinCmd(ENABLE);//设置WKUP用于唤醒
	
	PWR_EnterSTANDBYMode();	//进入待机模式
	 
}
//检测WKUP脚的信号
//返回值1:连续按下3s以上
//      0:错误的触发	
u8 Check_WKUP(void) 
{
	u8 t=0;
	u8 tx=0;//记录松开的次数
	LED0=0; //亮灯DS0 
	while(1)
	{
		if(WKUP_KD)//已经按下了
		{
			t++;
			tx=0;
		}else 
		{
			tx++; 
			if(tx>3)//超过90ms内没有WKUP信号
			{
				LED0=1;
				return 0;//错误的按键,按下次数不够
			}
		}
		delay_ms(30);
		if(t>=100)//按下超过3秒钟
		{
			LED0=0;	  //点亮DS0 
			return 1; //按下3s以上了
		}
	}
}  
//中断,检测到PA0脚的一个上升沿.	  
//中断线0线上的中断检测
void EXTI0_IRQHandler(void)
{ 		    		    				     		    
  EXTI_ClearITPendingBit(EXTI_Line0); // 清除LINE10上的中断标志位
	if(Check_WKUP())//关机?
	{		  
		Sys_Enter_Standby(); //进入待机模式 
	}
} 

//PA0 WKUP唤醒初始化
void WKUP_Init(void)
{	  
  GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //PA0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//输入模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化	

	//(检查是否是正常开)机    		 
  if(Check_WKUP()==0)
	{
		Sys_Enter_Standby();	//不是开机,进入待机模式  
	}
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 连接到中断线0
	
 
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
  EXTI_Init(&EXTI_InitStructure);//配置
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置NVIC
	
 
}
```

该部分代码比较简单，我们在这里说明两点： 

1，在 void Sys_Enter_Standby(void)函数里面，我们要在进入待机模式前把所有开启的外设全部关闭，我们这里仅仅复位了所有的 IO 口，使得 IO 口全部为浮空输入。

其他外设（比如 ADC 等），大家根据自己所开启的情况进行一一关闭就可，这样才能达到最低功耗！

然后我们 调用函数 `RCC_APB1PeriphClockCmd `来使能 PWR 时钟，调用函数 `PWR_WakeUpPinCmd `用来 设置 WK_UP 引脚作为唤醒源。

最后调用 PWR_EnterSTANDBYMode 函数进入待机模式。 

2，在` void WKUP_Init(void)`函数里面，我们首先要使能 `GPIOA `时钟，同时因为我们要使用到外部中断，所以必须先使能 `SYSCFG `时钟。

然后对 `GPIOA `初始化位下拉输入。同时调用 函数 `SYSCFG_EXTILineConfig` 配置 `GPIOA`.0 连接到中断线 0。最后初始化 `EXTI `中断线以及 `NVIC `中断优先级。

这上面的步骤实际上跟我们之前的外部中断实验知识是一样的，所以不理 解的地方大家可以翻到外部中断实验章节看看。在上面初始化的过程中，我们还先先判断WK_UP 是否按下了 3 秒钟，来决定要不要开机，如果没有按下 3 秒钟，程序直接就进入了待 机模式。所以在下载完代码的时候，是看不到任何反应的。我们**必须先按** **WK_UP** **按键** **3** **秒开** 

**机**，才能看到 DS0 闪烁。 

3，在中断服务函数EXTI0_IRQHandler 内，我们通过调用函数 Check_WKUP来判断 WK_UP 按下的时间长短，来决定是否进入待机模式，如果按下时间超过 3 秒，则进入待机，否则退出中断。 

最后我们看看 main 函数内容如下： 

```c
  
int main(void)
{ 
 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);    //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	LED_Init();				//初始化LED  
	WKUP_Init();				//待机唤醒初始化
 	LCD_Init();         //液晶初始化
	POINT_COLOR=RED; 
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"WKUP TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/6");	
	LCD_ShowString(30,130,200,16,16,"WK_UP:Stanby/WK_UP");	 
	while(1)
	{
		LED0=!LED0;
		delay_ms(250);//延时250ms
	}
}


```

这里我们先初始化 LED 和 WK_UP 按键（通过 WKUP_Init（）函数初始化），如果检测到有长按 WK_UP 按键 3 秒以上，则开机，并执行 LCD 初始化，在 LCD 上面显示一些内容

如 果没有长按，则在 `WKUP_Init `里面，调用 `Sys_Enter_Standby `函数，直接进入待机模式了。 

开机后，在死循环里面等待 WK_UP 中断的到来，在得到中断后，在中断函数里面判断 WK_UP 按下的时间长短，来决定是否进入待机模式，如果按下时间超过 3 秒，则进入待机， 

否则退出中断，继续执行 main 函数的死循环等待，同时不停的取反 LED0，让红灯闪烁。 

代码部分就介绍到这里，大家记住

**下载代码后，一定要长按 WK_UP 按键，来开机，否则 将直接进入待机模式，无任何现象****

## **4** **下载与测试** 

在代码编译成功之后，下载代码到探索者 STM32F4 开发板上，此时，看到开发板 DS0 亮了一下（Check_WKUP 函数执行了 LED0=0 的操作），就没有反应了。

其实这是正常的，在程序下载完之后，开发板检测不到 WK_UP 的持续按下（3 秒以上），所以直接进入待机模式，看 起来和没有下载代码一样。此时，我们长按 WK_UP 按键 3 秒钟左右，可以看到 DS0 开始闪烁， 液晶也会显示一些内容。然后再长按 WK_UP，DS0 会灭掉，液晶灭掉，程序再次进入待机模 式。