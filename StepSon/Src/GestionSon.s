	PRESERVE8
	THUMB   
		
	include Driver\DriverJeuLaser.inc	
	EXPORT  CallbackSon  
	EXPORT StartSon
		
	EXTERN GPIOB_Clear
	EXTERN GPIOB_Set
		
	IMPORT Son
	IMPORT LongueurSon

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		
FlagSon dcd 0 
	EXPORT  FlagSon
SortieSon dcd 0
	EXPORT SortieSon
index dcd 0
	EXPORT index
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		


StartSon PROC
	ldr r0,=index
	mov r1, #0
	str r1,[r0]
	bx lr
	endp

CallbackSon  PROC
	ldr r0,=index
	ldr r0, [r0]
	
	ldr r2, =LongueurSon
	ldr r2, [r2]
	
	cmp r0, r2 ;r0 index
	bne Lecture
	
	bx lr
Lecture

	ldr r3,=Son
	ldrsh r3, [r3,r0,lsl #1] ; LSL logical shift left #1 car multiplié par 2
	
	add r3, #32768 ;Partie calcul fenetrage
	mov r1, #720
	mul r3, r1
	lsr r3, #16


	ldr r0,=index ; increment de index 
	ldr r1, [r0]
	add r1,#1 
	str r1, [r0] 
	
	ldr r2,=SortieSon ; stockage sortieson
	str r3, [r2]
	mov r0,r3
	
	push {lr}
	bl PWM_Set_Value_TIM3_Ch3
	pop {lr}
	
	bx lr
	endp	
		
	END
END