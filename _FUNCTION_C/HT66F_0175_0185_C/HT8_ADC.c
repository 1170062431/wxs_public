/**
  ******************************************************************************
  * @file HT8_ADC.c
  * @brief This file provides all the ADC firmware functions.
  * @author Holtek Semiconductor Inc
  * @version V1.0.0
  * @date 2018-12-20
  ******************************************************************************
  * @attention
  *
  * Firmware Disclaimer Information
  *
  * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
  *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
  *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
  *    other intellectual property laws.
  *
  * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
  *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
  *    other than HOLTEK and the customer.
  *
  * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
  *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
  *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
  *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
  *
  * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
  ************************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "HT8_ADC.h"

/**
  * @brief Initializes the ADC peripheral according to the specified parameters
  * @retval None
  */
void ADC_Init(void)
{
/***************** ADC clock select *****************/
	#ifdef	ADC_CLOCK_FSYS
		{
			/* select ADC clock fsys */
			_sacks2 = 0; _sacks1 = 0; _sacks0 = 0;
		}		
	#elif	ADC_CLOCK_FSYS_DIV2
		{
			/* select ADC clock fsys/2 */
			_sacks2 = 0; _sacks1 = 0; _sacks0 = 1;
		}
	#elif	ADC_CLOCK_FSYS_DIV4
		{
			/* select ADC clock fsys/4 */
			_sacks2 = 0; _sacks1 = 1; _sacks0 = 0;
		}
	#elif	ADC_CLOCK_FSYS_DIV8
		{
			/* select ADC clock fsys/8 */
			_sacks2 = 0; _sacks1 = 1; _sacks0 = 1;
		}
	#elif	ADC_CLOCK_FSYS_DIV16
		{
			/* select ADC clock fsys16 */
			_sacks2 = 1; _sacks1 = 0; _sacks0 = 0;
		}
	#elif	ADC_CLOCK_FSYS_DIV32
		{
			/* select ADC clock fsys/32 */
			_sacks2 = 1; _sacks1 = 0; _sacks0 = 1;
		}
	#elif	ADC_CLOCK_FSYS_DIV64
		{
			/* select ADC clock fsys/64 */
			_sacks2 = 1; _sacks1 = 1; _sacks0 = 0;
		}
	#elif	ADC_CLOCK_FSYS_DIV128
		{
			/* select ADC clock fsys/128 */
			_sacks2 = 1; _sacks1 = 1; _sacks0 = 1;
		}
	#endif	
/*************** end of ADC clock select ******************/	

						
/******** setting AD convert data alignment type **********/
	#ifdef	ADC_VALUE_ALIGN_RIGHT		
		{
			/* select AD convert data alignment right	*/
			_adrfs = 1;
		}	
	#else		
		{
			/* select 	AD convert data alignment left */	
			_adrfs = 0;
		}	
	#endif
/***** end of setting AD convert data alignment type ******/


/********** setting AD convert reference voltage *********/		
	#ifdef	ADC_REF_VOLTAGE_VDD
		{
			_savrs3 = 0; _savrs2 = 0; _savrs1 = 0; _savrs0 = 0;
			ADC_VREFI_DISABLE();//disable Vrefi
		}	
	#elif	ADC_REF_VOLTAGE_VREFI
		{
			_savrs3 = 0; _savrs2 = 0; _savrs1 = 0; _savrs0 = 1;
			ADC_VREFI_ENABLE();	//enable Vrefi
			ADC_PGA_ENABLE();	//enable PGA
		}	
	#elif	ADC_REF_VOLTAGE_VREFIx2
		{
			_savrs3 = 0; _savrs2 = 0; _savrs1 = 1; _savrs0 = 0;
			ADC_VREFI_ENABLE();	//enable Vrefi
			ADC_PGA_ENABLE();	//enable PGA
		}	
	#elif	ADC_REF_VOLTAGE_VREFIx3
		{
			_savrs3 = 0; _savrs2 = 0; _savrs1 = 1; _savrs0 = 1;
			ADC_VREFI_ENABLE();	//enable Vrefi
			ADC_PGA_ENABLE();	//enable PGA
		}	
	#elif	ADC_REF_VOLTAGE_VREFIx4
		{
			_savrs3 = 0; _savrs2 = 1; _savrs1 = 0; _savrs0 = 0;
			ADC_VREFI_ENABLE();	//enable Vrefi
			ADC_PGA_ENABLE();	//enable PGA
		}	
	#elif	ADC_REF_VOLTAGE_VBGx2
		{
			_savrs3 = 1; _savrs2 = 0; _savrs1 = 1; _savrs0 = 0;
			ADC_VBG_ENABLE();	//enable Vbg
			ADC_PGA_ENABLE();	//enable PGA
		}	
	#elif	ADC_REF_VOLTAGE_VBGx3
		{
			_savrs3 = 1; _savrs2 = 0; _savrs1 = 1; _savrs0 = 1;
			ADC_VBG_ENABLE();	//enable Vbg
			ADC_PGA_ENABLE();	//enable PGA
		}	
	#elif	ADC_REF_VOLTAGE_VBGx4
		{
			_savrs3 = 1; _savrs2 = 1; _savrs1 = 0; _savrs0 = 0;
			ADC_VBG_ENABLE();	//enable Vbg
			ADC_PGA_ENABLE();	//enable PGA
		}	
	#endif 
/********* end of setting AD convert reference voltage *********/
}



/**
  * @brief select ADC channel.
  * @param[in] ADC_Channel: specifies the ADC channel.
  * can have one of the values of @ref ADC_Channel_TypeDef.
  * @retval  none.
  */
void ADC_SelectChannel(u8 ADC_Channel)
{
	_sadc1 &= 0b00011111;
	if((ADC_Channel >= 0)&&(ADC_Channel < 8))
	{
		/* clear ADC channel */
		_sadc0 &= 0b11111000;
		
		/* selection external ADC channel */
		_sadc0 |= ADC_Channel;
		
		/* select IO in AD input */
		_acerl = 0x01;
		_acerl <<= 	ADC_Channel;
	}
	else
	{
		/* selection internal ADC channel */
		//当选择内部模拟信号时，外部通道输入信号会自动关闭。
		_sadc1 |= ADC_Channel;		
	}	
}/* end of ADC_SelectChannel(u8 ADC_Channel) */


/**
  * @brief Get one sample of measured signal.
  * @param[in] None.
  * @retval ConversionValue:  value of the measured signal.
  */
u16 ADC_GetValue(void)
{
	u16 Value;
	
	/* start AD converter */
	ADC_START();
	
	/* waitting AD conversion finish */
	while(1 == _adbz);	
	
/* AD conversion data alignment right */
	#ifdef	ADC_VALUE_ALIGN_RIGHT		
		{
			/* get the AD conversion value */
			Value = (_sadoh <<8) | _sadol;
		}	
	
/* AD conversion data alignment left */
	#else	
		{
			/* get the AD conversion value */
			Value = (_sadoh <<4) | (_sadol >>4);
		}	
	#endif
	return Value;
}



/**
  * @brief Get one sample of measured signal.
  * @param[in] ADC_Channel: specifies the ADC channel.
  * can have one of the values of @ref ADC_Channel_TypeDef.
  * @retval ConversionValue:  value of the measured signal.
  * @par Required preconditions:
  * ADC conversion finished.
  */
u16 ADC_GetChannelValue(u8 ADC_Channel)
{
	u16 AD_ConverterValue;
	
	_sadc1 &= 0b00011111;
	if((ADC_Channel >= 0)&&(ADC_Channel < 8))
	{
		/* clear ADC channel */
		_sadc0 &= 0b11111000;
		/* selection external ADC channel */
		_sadc0 |= ADC_Channel;	

        /* select IO in AD input */
		_acerl = 0x01;
		_acerl <<= 	ADC_Channel;		
	}
	else
	{
		/* selection internal ADC channel */
		_sadc1 |= ADC_Channel;		
	}
	
	/* start AD convert */
	ADC_START();
		
	/* waitting AD conversion finish */	
	while(1 == _adbz);	
	
	/* AD conversion data alignment right */
	#ifdef	ADC_VALUE_ALIGN_RIGHT		
		{
			/* get the AD conversion value */
			AD_ConverterValue = (_sadoh <<8) | _sadol;
		}	
			
	/* AD conversion data alignment left */
	#else	
		{
			/* get the AD conversion value */
			AD_ConverterValue = (_sadoh <<4) | (_sadol >>4);
		}	
	#endif
	
		return AD_ConverterValue;
}

 
/******************* (C) COPYRIGHT 2018 Holtek Semiconductor Inc *****END OF FILE****/