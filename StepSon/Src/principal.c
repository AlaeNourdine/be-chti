

#include "DriverJeuLaser.h"
extern int PeriodeSonMicroSec;
extern void CallbackSon(void);
extern int LongueurSon;


extern void StartSon(void);
int main(void)
{
// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
CLOCK_Configure();
	// configuration du Timer 4 en d�bordement
//Timer_1234_Init_ff( TIM1, 720000*PeriodeSonMicroSec);	
Timer_1234_Init_ff( TIM1, 6552);	//On trouve a partir PeriodeSonMicroSec
	

	
	
// configuration de PortB.1 (PB1) en sortie push-pull
GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================



//============================================================================	
	
PWM_Init_ff( TIM3, 3, 720);
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);	

// Activation des interruptions issues du Timer 4
// Association de la fonction � ex�cuter lors de l'interruption : timer_callback
// cette fonction (si �crite en ASM) doit �tre conforme � l'AAPCS
Active_IT_Debordement_Timer( TIM1, 2, CallbackSon );
int i = 0;
while	(1)
	{
		i++ ;
		if(i > 3600000){
			StartSon();
			i = 0;
		}
	}
}

