#include "sys.h"
#include "usart.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h" //ucos 使用
#endif
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口1初始化
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/8/18
//版本：V1.5
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
//V1.5修改说明
//1,增加了对UCOSII的支持
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if 1
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
    int handle;
};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
_sys_exit(int x)
{
    x = x;
}
//重定义fputc函数
int fputc(int ch, FILE *f)
{
    while ((USART1->SR & 0X40) == 0)
        ; //循环发送,直到发送完毕
    USART1->DR = (u8)ch;
    return ch;
}
#endif

/*使用microLib的方法*/
/* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
/**
 * @author 	xiaowine@cee0.com
 * @date		2015年6月9日8:56:05
 * @brief 	U1接收指针
 *********************/
void (*Proce_U1)(u8);

//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误
u8 USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.
u8 USART_TX_BUF[USART_TRA_LEN];
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA = 0; //接收状态标记

//初始化IO 串口1
//bound:波特率
/**********************USART1初始化*****************************************************************/
void uart1_init(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); //使能USART1，GPIOA时钟
    USART_DeInit(USART1);                                                         //复位串口1
                                                                                  //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                                     //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);          //初始化PA9

    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);                //初始化PA10

    //Usart1 NVIC 配置

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                           //根据指定的参数初始化VIC寄存器

    //USART 初始化设置

    USART_InitStructure.USART_BaudRate = bound;                                     //一般设置为9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //收发模式

    USART_Init(USART1, &USART_InitStructure);      //初始化串口
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //开启中断
    USART_Cmd(USART1, ENABLE);                     //使能串口
    USART_ClearFlag(USART1, USART_FLAG_TC);        /* 清发送外城标志，Transmission Complete flag */
    Proce_U1 = Prece_REC;
}
/***********************USART2初始化******************************************************************/
void uart2_init(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //使能USART2时钟

    USART_DeInit(USART2); //复位串口1
    //USART2_TX   PA.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽
    GPIO_Init(GPIOA, &GPIO_InitStructure);          //初始化PA2
    //USART2_RX	  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;             //PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, ENABLE);  //复位串口2
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, DISABLE); //停止复位

#ifdef EN_USART2_RX //如果使能了接收
    //USART 初始化设置
    USART_InitStructure.USART_BaudRate = bound;                                     //一般设置为9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //8位数据长度
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             ///奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //收发模式
    USART_Init(USART2, &USART_InitStructure);
    ; //初始化串口

    //Usart2 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;         //使能串口2中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //从优先级2级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);                           //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //开启中断

    USART_Cmd(USART2, ENABLE);              //使能串口
    USART_ClearFlag(USART2, USART_FLAG_TC); /* 清发送外城标志，Transmission Complete flag */

#endif
}
/***********************USART3初始化******************************************************************/
void uart3_init(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIOA时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //使能USART2时钟

    USART_DeInit(USART3);                      //复位串口1
                                               //USART3_TX   PB.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽
    GPIO_Init(GPIOB, &GPIO_InitStructure);          //初始化PA10
    //USART3_RX	  PB.11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;            //PB11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, ENABLE);  //复位串口3
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, DISABLE); //停止复位

#ifdef EN_USART3_RX //如果使能了接收
    //USART 初始化设置
    USART_InitStructure.USART_BaudRate = bound;                                     //一般设置为9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //8位数据长度
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             ///奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //收发模式
    USART_Init(USART3, &USART_InitStructure);
    ; //初始化串口

    //Usart2 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;         //使能串口2中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //从优先级2级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);                           //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); //开启中断

    USART_Cmd(USART3, ENABLE);              //使能串口
    USART_ClearFlag(USART3, USART_FLAG_TC); /* 清发送外城标志，Transmission Complete flag */
#endif
}

/***********************USART1中断******************************************************************/

#if EN_USART1_RX             //如果使能了接收
void USART1_IRQHandler(void) //串口1中断服务程序
{
    u8 Res;
#ifdef OS_TICKS_PER_SEC //如果时钟节拍数定义了,说明要使用ucosII了.
    OSIntEnter();
#endif
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //接收中断(接收到的数据必须是0x0d 0x0a结尾)
    {
        Res = USART_ReceiveData(USART1); //(USART1->DR);	//读取接收到的数据
        (*Proce_U1)(Res);
    }
#ifdef OS_TICKS_PER_SEC //如果时钟节拍数定义了,说明要使用ucosII了.
    OSIntExit();
#endif
}
#endif
/***********************USART2中断******************************************************************/

#ifdef EN_USART2_RX //如果使能了接收
//接收缓存区
void USART2_IRQHandler(void)
{
    u8 Res;

    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //接收到数据
    {
        Res = USART_ReceiveData(USART2); //读取接收到的数据
        Res = Res;
        //		process_USART2(Res);
        //		USART2->DR = Res;
        //		while((USART2->SR&0X40)==0);//循环发送,直到发送完毕
        //		USART2->SR&=(0XFFDF);  //清除接收标志位
    }
}
#endif
/***********************USART3中断******************************************************************/

#ifdef EN_USART3_RX //如果使能了接收
//接收缓存区
void USART3_IRQHandler(void)
{
    u8 Res;
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //接收到数据
    {
        Res = USART_ReceiveData(USART3); //读取接收到的数据
        Res = Res;
    }
}
#endif

void USARTx_Send_buff(USART_TypeDef *USARTx, u32 len, u8 *buf)
{
    u8 *p = buf;
    u32 i;
    /*	由软件序列清除该位(先读USART_SR，然后写入USART_DR)。
	则能够保证首个数据发送时，不出现覆盖的情况
	http://www.openedv.com/posts/list/14573.htm
	下面执行其中一个就行
	*/
    USART_ClearFlag(USART1, USART_FLAG_TC);
    //	USART_GetFlagStatus(USART1, USART_FLAG_TC);
    for (i = 0; i < len; i++)
    {
        USART_SendData(USARTx, *p++); //向串口1发送数据
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) != SET)
            ; //等待发送结束
    }
    delay_ms(2);
}

/*
***********************************************************************************************************
**函数原型		:  	void FM0DataToUART(uUINT16ARR add,u8 cmd,u8 temp,u8 *p_uartsendbuf)
**参数说明		:  
**返回值		:	无	
**说	明		;	本函数用于对接收的数据命令进行相应的操作；
************************************************************************************************************
*/
void FM0DataToUART(uUINT16ARR add, u8 cmd, u8 temp, u8 *p_uartsendbuf)
{
    u8 i;
    *p_uartsendbuf = cmd;
    *(p_uartsendbuf + 1) = add.Byte[0];
    *(p_uartsendbuf + 2) = add.Byte[1];
    *(p_uartsendbuf + 3) = temp;
    *(p_uartsendbuf + 4) = cmd;
    for (i = 1; i < 4; i++)
    {
        *(p_uartsendbuf + 4) ^= *(p_uartsendbuf + i);
    }
}
/**
************************************************************************************************************************
 * @Function 	:		void Prece_REC(u8 temp)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	接收处理函数
 * @param 		: 	u8 temp 接收到的字节
 * @Return  	:		None
 * @说	明  	:		
************************************************************************************************************************
*/
void Prece_REC(u8 temp)
{
    temp = temp;
}
