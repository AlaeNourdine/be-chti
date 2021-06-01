

#include "DriverJeuLaser.h"
extern short int LeSignal;


extern int DFT_ModuleAuCarre( short int * Signal64ech, char k);
int DFT_result[64];
short SignalCapture[64];
int x = 1;
int scores[6] ;
void systick_callback(){
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	for(int i = 1 ; i<64 ; i++){
			if( (DFT_result[i] = DFT_ModuleAuCarre(SignalCapture,i)) <= 3)
				DFT_result[i] = 0;
			else
				scores[0] = x++;
	}
}
	

int main(void)
{
	
	
// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
CLOCK_Configure();


	//r�gler la p�riodicit� du timer : 5ms
Systick_Period_ff(360000);
	//g�n�ration d'interruption de d�bordement
Systick_Prio_IT(1,systick_callback);

SysTick_On;
SysTick_Enable_IT ;
	
	//Activation ADC1 : 72 ticks � 72kHz = 1 microsec
Init_TimingADC_ActiveADC_ff(ADC1,72);
	
//Choix du pin d'entr�e (PA2)
Single_Channel_ADC(ADC1,2);

//Config timer 2 pour qu'il d�clenche l'ADC1 � une fr�quence de 320kHz
Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );

//configurer la DMA pour qu'elle remplisse la zone RAM voulue (0 = lin�aire, 1= cyclique)
Init_ADC1_DMA1( 0, SignalCapture );


	

//============================================================================	


	
while	(1)
	{
	}	
}

