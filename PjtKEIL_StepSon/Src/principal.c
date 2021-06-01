

#include "DriverJeuLaser.h"
extern int PeriodeSonMicroSec;
extern void CallbackSon(void);

int main(void)
{
	
	// configuration du Timer 4 en débordement 100ms
Timer_1234_Init_ff( TIM1, 72000*PeriodeSonMicroSec);	
	
	
// Activation des interruptions issues du Timer 4
// Association de la fonction à exécuter lors de l'interruption : timer_callback
// cette fonction (si écrite en ASM) doit être conforme à l'AAPCS
Active_IT_Debordement_Timer( TIM1, 2, CallbackSon );
	
	
// configuration de PortB.1 (PB1) en sortie push-pull
GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();


	
	

//============================================================================	
	
	
while	(1)
	{
	}
}

