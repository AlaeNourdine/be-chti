

#include "DriverJeuLaser.h"
extern int PeriodeSonMicroSec;
extern void CallbackSon(void);
extern int LongueurSon;


extern void StartSon(void);
int main(void)
{
// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();
	// configuration du Timer 4 en débordement
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
// Association de la fonction à exécuter lors de l'interruption : timer_callback
// cette fonction (si écrite en ASM) doit être conforme à l'AAPCS
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

