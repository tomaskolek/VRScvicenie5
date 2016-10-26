#include <stddef.h>
#include "stm32l1xx.h"
#include "vrs_cv5.h"
#include <stdio.h>

//#include <string.h>


int main(void)
{
	nvic_init();
	gpio_init();
	adc_init();
	//usart_init();
/*
	while (1)
	{
		for(int i = 0; i <= 10000; i++){
		}
		if (pom == 1){
			sprintf(naPoslanie,"%f\r\n", (3.3/4095)*AD_value);
		}
		else{
			sprintf(naPoslanie,"%i\r\n", AD_value);
		}
		posli_znak(naPoslanie);
	}*/
	while (1){
		blikamLEDku(AD_value);
	}
	return 0;
}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}
