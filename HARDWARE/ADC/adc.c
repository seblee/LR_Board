#include "sys.h"
#include "adc.h"

u16 value[N][M];
u16 aftervalue[M];
float avalue[M];

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//ADC 驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/6/7 
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved					   
//////////////////////////////////////////////////////////////////////////////////	 
 
		   
//初始化ADC
//这里我们仅以规则通道为例
//我们默认将开启通道0~3																	   

void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1, ENABLE );	  //使能ADC1通道时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PC4 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//循环模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = M;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
 /* 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
  ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期	
  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期	
  ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 8, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 9, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 9, ADC_SampleTime_239Cycles5 );
  ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 10, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 11, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期	
  ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 12, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 13, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
  ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 14, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 15, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期		
	*/
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0 , 1, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1 , 2, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2 , 3, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3 , 4, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4 , 5, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5 , 6, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6 , 7, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7 , 8, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 9, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15,10, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8 ,11, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9 ,12, ADC_SampleTime_239Cycles5 );	//配置采样时间为239.5周期

	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	ADC_DMACmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	ADC_StartCalibration(ADC1);	 //开启AD校准 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
}
//获得ADC值
//ch:通道值 0~3
u16 Get_Adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 	 







void filter(void)
{
	int sum = 0;
	u8 count,i;
	for(i=0;i<M;i++)
	{
		for(count=0;count<N;count++)
		{
			 sum+=value[count][i];
    }
    aftervalue[i]=sum/N;
    sum=0;
  }
}



















