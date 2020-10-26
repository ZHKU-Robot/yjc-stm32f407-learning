# yjc-stm32学习

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](.)

***
本仓库包含以下内容：

1. 一个傻逼的自我修养

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
- 俄罗斯方块
- 贪吃蛇必须要安排(已完成)


## 更新
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
- 2020年10月23日20:51:08 update cha-[TFTLCD显示屏](./contents/cha-TFTLCD) 
    - 这一章很难,推荐选读，我们只需要去知道怎么调函数就好hhh
- 2020年10月22日22:19:14 update ch4-[串口通信实验](./contents/ch4-serialport) 和 ch01-[快速组织代码](./contents/ch01-quickexample)
    - 串口设置的一般步骤可以总结为如下几个步骤：
        1. 串口时钟使能，GPIO 时钟使能。 
        2. 设置引脚复用器映射：调用 GPIO_PinAFConfig 函数。 
        3. GPIO 初始化设置：要设置模式为复用功能。 
        4. 串口参数初始化：设置波特率，字长，奇偶校验等参数。 
        5. 开启中断并且初始化 NVIC，使能中断（如果需要开启中断才需要这个步骤）。 
        6. 使能串口。 
        7. 编写中断处理函数：函数名格式为 USARTxIRQHandler(x 对应串口号)。 
- 2020年10月22日19:02:19 update ch2-[蜂鸣器](./contents/ch2-beep)和ch3-[键盘输入](./contents/ch3-keyinput)
- 2020年10月21日23:25:30 update ch1-[跑马灯](./contents/ch1-ledwater)
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