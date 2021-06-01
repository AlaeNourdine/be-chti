

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

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();


	//régler la périodicité du timer : 5ms
Systick_Period_ff(360000);
	//génération d'interruption de débordement
Systick_Prio_IT(1,systick_callback);

SysTick_On;
SysTick_Enable_IT ;
	
	//Activation ADC1 : 72 ticks à 72kHz = 1 microsec
Init_TimingADC_ActiveADC_ff(ADC1,72);
	
//Choix du pin d'entrée (PA2)
Single_Channel_ADC(ADC1,2);

//Config timer 2 pour qu'il déclenche l'ADC1 à une fréquence de 320kHz
Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );

//configurer la DMA pour qu'elle remplisse la zone RAM voulue (0 = linéaire, 1= cyclique)
Init_ADC1_DMA1( 0, SignalCapture );


	

//============================================================================	


	
while	(1)
	{
	}	
}

