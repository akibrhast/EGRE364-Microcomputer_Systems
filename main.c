#include "stm32l476xx.h"
#include "SysTimer.h"
//volatile uint32_t msTicks;









void assign(uint32_t t){
GPIOE -> ODR &= ~(0xFC00); //clears 10-15
GPIOE -> ODR |= (t>>4)<<10;
GPIOA -> ODR &= ~(0x000F);// lear 0-3
GPIOA -> ODR |= (t&0x00F);
}

void blinkF(uint32_t t){
	int i;
	
	assign(t);
	for(i=0; i<3840 ; i++);
	
	 t= t>>3;
	 assign(t);	 
	
	for(i=0; i<15360  ; i++);
t= t<<1;
	 assign(t);	 
	 

	for(i=0; i<11520  ; i++);

t= t<<1;
			 assign(t);	 

	for(i=0; i< 7680 ; i++);


}

void blinkB(uint32_t t){
	int i;

	assign(t);
	for(i=0; i<15360; i++);
	
	 t= t>>1;
	 assign(t);	 
	
	for(i=0; i<11520; i++);
t= t>>1;
	 assign(t);	 
	 

	for(i=0; i<7680; i++);

t= t>>1;
			 assign(t);	 

	for(i=0; i<3840 ; i++);

}



void initialize(){
	// Enable High Speed Internal Clock (HSI = 16 MHz)
	RCC->CR |= ((uint32_t)RCC_CR_HSION);
	
  // wait until HSI is ready
  while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 ) {;}
	
  // Select HSI as system clock source 
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;  //01: HSI16 oscillator used as system clock

  // Wait till HSI is used as system clock source 
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 ) {;}
  
  // Enable the clock to GPIO Port B	
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOEEN | RCC_AHB2ENR_GPIOBEN;   

	// MODE: 00: Input mode, 01: General purpose output mode
  //       10: Alternate function mode, 11: Analog mode (reset state)
		//Turn on pin PA0 - PA3 and PE10 - PE15
  
	/* Turn on RED led on PB2*/
	GPIOB->MODER &= ~(0x03<<(2*2)); 
  GPIOB->MODER |= (1<<4);
	GPIOB->ODR |= GPIO_ODR_ODR_2;
		
		
		

		
		

		
		
	/*Sets PE pin to output mode*/
	GPIOE->MODER &= (0x000FFFFF); 
	GPIOE->MODER |= (0x55500000);
	
	/*Configure  Output Type as Push Pull */
	GPIOE-> OTYPER &= (0x03FF);
	GPIOE-> OTYPER |= (0x0000);
	
	/*Configure output type as no pullup no pulldow */
	GPIOE -> PUPDR &= (0x000FFFFF);
	GPIOE -> PUPDR |= (0x00000000);
	
	
	/*Set PA pin to output mode*/
	GPIOA->MODER &= (0xFFFFFF00); 
	GPIOA->MODER |=  (0x00000055);
	
	/*Configure  Output Type as Push Pull */
	GPIOA-> OTYPER &= (0xFFF0);
	GPIOA-> OTYPER |= (0x0000);
	
	/*Configure output type as no pullup no pulldow */
	GPIOA -> PUPDR &= (0xFFFFFF00);
	GPIOA -> PUPDR |= (0x00000000);
	
//set PH0 AND PH1 as output mode and always on

	

}




int main(void){
	int i;
	uint32_t d = 1;
	uint32_t t = (0x200);
	//SysTick_Config(SystemCoreClock / 1000);
SysTick_Init();

	
	initialize();
	
	
	
	
	

		//GPIOA->ODR |= GPIO_ODR_ODR_3 | GPIO_ODR_ODR_0 | GPIO_ODR_ODR_1 | GPIO_ODR_ODR_2;
	
		//GPIOE->ODR |= GPIO_ODR_ODR_10 | GPIO_ODR_ODR_11 |GPIO_ODR_ODR_12 | GPIO_ODR_ODR_13 |GPIO_ODR_ODR_14 | GPIO_ODR_ODR_15;
		
	
//while(1){
//	GPIOE->ODR &= (0xFBFF) ; //CLEAR BIT 10 ONLY
//	GPIOE->ODR |= (0x400); //SET BIT 10 TO 1
//	{delay(25);
//	GPIOE->ODR &= (0xFBFF) ; //CLEAR BIT 10
//		delay(25);
//	}
//	//delay(25);
//	
//	GPIOE->ODR &= 0xFC00; //CLEAR 11
//	GPIOE->ODR |= 0x800; //S ET 11 TO 1
//	{delay(10);
//	GPIOE->ODR &= 0xFC00;
//		delay(10);
//	}
//		//delay(10);
//	
//	GPIOE->ODR |= GPIO_ODR_ODR_12;
//	
	//GPIO 10 ON
	
	//GPIO 11 ON GPIO 10 DELAY(20)
	
	//GPIO 12 ON GPIO 11 DELAY(20) GPIO 10(40)
	
	//GPIO 13 ON GPIO 12 DELAY(20) GPIO 11(40) GPIO 10(60)
	
	//GPIO 14 ON GPIO 13 DELAY(20) GPIO 12(40) GPIO 11(60) GPIO 10(80)
	
	//GPIO 15 ON GPIO 14 DELAY(20) GPIO 13(40) GPIO 12(60) GPIO 11(80)	GPIO 10 OFF
	
	//GPIO 0  ON GPIO 15 DELAY(20) GPIO 14(40) GPIO 13(60) GPIO 12(80)	GPIO 11 OFF GPIO 10 OFF
	
	//GPIO 1  ON GPIO 0  DELAY(20) GPIO 15(40) GPIO 14(60) GPIO 13(80)	GPIO 12 OFF GPIO 11 OFF GPIO 10 OFF
	
	//GPIO 2  ON GPIO 1  DELAY(20) GPIO 0 (40) GPIO 15(60) GPIO 14(80)	GPIO 13 OFF GPIO 12 OFF GPIO 11 OFF GPIO 10 OFF
	
	//GPIO 3  ON GPIO 2  DELAY(20) GPIO 1 (40) GPIO 0 (60) GPIO 15(80)	GPIO 14 OFF GPIO 13 OFF GPIO 12 OFF GPIO 11 GPIO 10 OFF 

//}
	
	
	while(1){
	
		if(d) {
			for(i=0; i<25; i++) {
					blinkF(t);}
			
					t>>=1;
				}
			else {
				for(i=0; i<25; i++) {
					blinkB(t);}
			
					t<<=1;
				}
			
		if(t==0x1) d = 0; // change to backward
		else if(t== 0x200) d = 1; //change to forward
	}
}






