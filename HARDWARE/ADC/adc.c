#include "sys.h"
#include "adc.h"

u16 value[N][M];
u16 aftervalue[M];
float avalue[M];

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//ADC ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/7 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved					   
//////////////////////////////////////////////////////////////////////////////////	 
 
		   
//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~3																	   

void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PC4 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//ѭ��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = M;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
 /* 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
  ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����	
  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����	
  ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 8, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 9, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 9, ADC_SampleTime_239Cycles5 );
  ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 10, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 11, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����	
  ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 12, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 13, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
  ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 14, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 15, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����		
	*/
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0 , 1, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1 , 2, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2 , 3, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3 , 4, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4 , 5, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5 , 6, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6 , 7, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7 , 8, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 9, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15,10, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8 ,11, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9 ,12, ADC_SampleTime_239Cycles5 );	//���ò���ʱ��Ϊ239.5����

	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	ADC_DMACmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	ADC_StartCalibration(ADC1);	 //����ADУ׼ 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
}
//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
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



















