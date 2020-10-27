# yjc-stm32f407zg学习

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](.)

***
## 改变学习策略，不再注重底层驱动实现

欢迎懂行的兄弟(*说的就是你*)update

 ![img](img/20160426646095_UXPhRS.jpg) 

本仓库包含以下内容：

1. stm32学习笔记(虽然是搬运的，但是好歹看了一遍)
2. 自己写的一些stm32 **toy**

 ![img](img/20190629805285_CGPMBi.jpg) 

## 内容列表

- [前言](#前言)
- [TODO](#TODO)
- [更新](#更新)
- [目录](#目录)
- [背景](#背景)
- [安装](#安装)
- [示例](#示例)
- [相关仓库](#相关仓库)
- [维护者](#维护者)
- [如何贡献](#如何贡献)
- [使用许可](#使用许可)
## 前言
在学习前，推荐阅读[快速组织代码技巧](./contents/ch01-quickexample)
## TODO
- 游戏
    - 俄罗斯方块
    - 贪吃蛇必须要安排(已完成)
- 基础
    - 一大堆..不会啊

## 更新

- 2020年10月27日13:06:29更新  [chi-DAC](contents\chi-DAC) 
    1. #### **开启** **PA** **口时钟，设置** **PA4** **为模拟输入。**
    2. **使能** **DAC1** **时钟。** 
    3. **初始化** **DAC,****设置** **DAC** **的工作模式。** 
    4. **使能** **DAC** **转换通道**
    5. **设置** **DAC** **的输出值。** 
- 2020年10月27日13:06:23 更新 [chh-lightSensor](contents\chh-lightSensor) 
    - 读取` LIGHT_SENSOR（PF7）`上面的电压，即可得到环境光线的强弱。光线越强，电压越低，光 线越暗，电压越高。 
- 2020年10月27日13:06:04 更新  [chg-tempSensor](contents\chg-tempSensor) 
    1. **设置** **ADC1****，开启内部温度传感器。**
    2. **读取通道** **16** **的** **AD** **值，计算结果。** 
- 2020年10月27日13:05:54 更新  [chf-ADC](contents\chf-ADC) 
    1. 使能随机数发生器时钟。
    2. **使能随机数发生器。** 
    3. **判断** **DRDY** **位**
    4. **读取随机数值。** 
-  2020年10月27日13:05:39 更新[che-wakeup](contents\che-wakeup) 
    1. 禁止 RTC 中断（ALRAIE、ALRBIE、WUTIE、TAMPIE 和 TSIE 等）。 
    2. 清零对应中断标志位。 
    3. 清除 PWR 唤醒(WUF)标志（通过设置 PWR_CR 的 CWUF 位实现）。 
    4. 重新使能 RTC 对应中断。 
    5. 进入低功耗模式。 
- 2020年10月27日12:44:05 更新 [chd-random](contents\chd-random) 
    - 随机数发生器操作步骤如下： 
        1. 使能随机数发生器时钟。
        2. **使能随机数发生器。** 
        3. **判断** **DRDY** **位**
        4. **读取随机数值。** 
- 2020年10月27日12:43:15 自暴自弃了，**改变学习策略，不再注重底层驱动实现**
    - 太累了，而且关键是看不懂！！
    - stm32的知识海量繁杂，我想..这样做是明智的
    - 前面的还能看懂，后面开始的就太超纲了
- 2020年10月27日12:43:05 更新  [chc-RTC](contents\chc-RTC) 
    - RTC 一般配置步骤
        1. **使能电源时钟，并使能** **RTC** **及** **RTC** **后备寄存器写访问。**
        2. **开启外部低速振荡器，选择** **RTC** **时钟，并使能。**
        3. **初始化** **RTC****，设置** **RTC** **的分频，以及配置** **RTC** **参数。**
        4. **设置** **RTC** **的时间。** 
        5. **设置** **RTC** **的日期。** 
        6. **获取** **RTC** **当前日期和时间。**
- 2020年10月27日11:22:48 更新  [chb-usmart](contents\chb-usmart) 
    - 使用串口调试的步骤:
        - 第一步，添加需要调用的函数（在 usmart_config.c 里 面的 usmart_nametab 数组里面添加）；
        - 第二步，初始化串口；
        - 第三步，初始化 USMART（通过 usmart_init 函数实现）；
        - 第四步，轮询 usmart_scan 函数，处理串口数据。 
- 2020年10月26日19:41:56 更新 [ch7-PWM](contents\ch7-PWM) 
    - 显然PWM我们已经接触过两次了，那么32就比较复杂了
    - 开启PWM步骤为
        - **开启** **TIM14** **和** **GPIO** **时钟，配置** **PF9** **选择复用功能** **AF9****（****TIM14****）输出。** 
        - **初始化** **TIM14,****设置** **TIM14** **的** **ARR** **和** **PSC** **等参数。**
            - arr=自动重装载值
            - psc=预分频值 
        - **设置** **TIM14_CH1** **的** **PWM** **模式，使能** **TIM14** **的** **CH1** **输出。**
            - `TIM_OC1Init()。 `
            - `TIM_OCMode= TIM_OCMode_PWM1`
        - **使能** **TIM14****。** 
            - `TIM_Cmd(TIM14, ENABLE); `
        - **修改** **TIM14_CCR1** **来控制占空比。**
            - `TIM_SetComparex(x=1,2,3,4)`
- 2020年10月26日12:11:29 了解了32的[定时器中断](contents\ch6-timer) 
    - 发现也是差不多的，大概步骤一样
        1. ****TIM3** **时钟使能。**
        2. **初始化定时器参数****,****设置自动重装值，分频系数，计数方式等。** 
        3. **设置** **TIM3_DIER** **允许更新中断。**
        4. **TIM3** **中断优先级设置。** 
        5. **允许** **TIM3** **工作，也就是使能** **TIM3****。**
        6. **编写中断服务函数。**
- 2020年10月25日22:37:35 学了一下32的中断[外部中断实验](./contents/ch5-interruption)
    - 和51的思路是一样的，就是细化了一点，有了更多自由空间，大体步骤为
        1. 使能 IO 口时钟，初始化 IO 口为输入。
        2. 使能 SYSCFG 时钟，设置 IO 口与中断线的映射关系。
        3. 初始化线上中断，设置触发条件等。
        4. 配置中断分组（NVIC），并使能中断。
        5. 编写中断服务函数。
- 2020年10月25日15:19:42 成功运行[贪吃蛇](./demo/mYsnake)
    - 如有bug请提交issue麻烦了
    - 目前已知bug：
        - 随机数食物生成有bug
            - 因为不知道怎么生成随机数
- 2020年10月23日20:51:08 update cha-[TFTLCD显示屏](./contents/cha-TFTLCD) 
    - 这一章很难,推荐选读，我们只需要去知道怎么调函数就好hhh
- 2020年10月22日22:19:14 update ch4-[串口通信实验](./contents/ch4-serialPort) 和 ch01-[快速组织代码](./contents/ch01-quickExample)
    - 串口设置的一般步骤可以总结为如下几个步骤：
        1. 串口时钟使能，GPIO 时钟使能。 设置引脚复用器映射：调用` GPIO_PinAFConfig `函数。 
        3. GPIO 初始化设置：要设置模式为复用功能。 
        4. 串口参数初始化：设置波特率，字长，奇偶校验等参数。 
        5. 开启中断并且初始化 NVIC，使能中断（如果需要开启中断才需要这个步骤）。 
        6. 使能串口。 
        7. 编写中断处理函数：函数名格式为 `USARTxIRQHandler(x 对应串口号)。 `
- 2020年10月22日19:02:19 update ch2-[蜂鸣器](./contents/ch2-beep)和ch3-[键盘输入](./contents/ch3-keyinput)
    - 蜂鸣器
        - `#define BEEP PFout(8)`
        -  `GPIO_ResetBits(GPIOF,GPIO_Pin_8);  //蜂鸣器对应引脚GPIOF8拉低， `
    - 键盘输入
        - KEY0 连接在 PE4 上
        - KEY1 连接在 PE3 上
        - KEY2 连接在 PE2 上
        - KEY_UP连接在 PA0 上
        - **KEY0、KEY1 和 KEY2 是低电平有效的，而 KEY_UP 是高电平有效**
        - 使能GPIOA,GPIOE对应的脚即可
- 2020年10月21日23:25:30 update ch1-[跑马灯](./contents/ch1-ledwater)
    - **在配置 STM32 外设的时候，任何时候都要先使能该外设的时钟！**
    - 可使用3种方法获取引脚变量
        - `GPIO_SetBits(GPIOF, GPIO_Pin_9);`
            - GPIOX在原理图上已标注
        - `#define LED0 PFout(9)`
        - `GPIOF->BSRRH=GPIO_Pin_9;`
- 2020年10月21日12:08:58 update readme.md
## 目录
0. [项目模板](./contents/ch0-template)
1. [快速组织代码](./contents/ch01-quickexample)
1. [跑马灯](./contents/ch1-ledwater)
2. [蜂鸣器](./contents/ch2-beep)
3. [键盘输入](./contents/ch3-keyinput)
4. [串口通信实验](./contents/ch4-serialport)
5. [TFTLCD显示屏](./contents/cha-TFTLCD)  
7. [外部中断实验](./contents/ch5-interruption)
8. [贪吃蛇](./demo/mYsnake)



## 背景

感谢兴爷，感谢苍天，感谢父母，让我遇见如此的小幸运  

我一定不会辜负兴爷的


这个仓库的目标是：

1. 贪吃蛇（已完成)
2. 俄罗斯方块

## 安装

参考[这个比较全，啥都有](https://www.bilibili.com/video/BV1Rx411R75t?p=6)

```sh
如果出现问题，请提交issue！！
```


## 示例
![img](img/togif2.gif)

## 相关仓库

- [yjc-BST-M51-learning](https://github.com/yujiecong/yjc-BST-M51-learning)
- [yjc-PrechinA2-learning](https://github.com/yujiecong/yjc-PrechinA2-learning)

## 维护者

[@yujiecong](https://github.com/yujiecong)。

## 如何贡献

非常欢迎你的加入！[提一个 Issue](https://github.com/ZHKU-Robot/yjc-stm32f407-learning/issues/new) 或者提交一个 Pull Request。


本 Readme 遵循 [Contributor Covenant](http://contributor-covenant.org/version/1/3/0/) 行为规范。

### 贡献者

感谢以下参与项目的人：  
<a href="graphs/contributors"><img src="https://avatars2.githubusercontent.com/u/44287052?s=60&amp;v=4" /></a>


## 使用许可
[MIT License](./LICENSE)