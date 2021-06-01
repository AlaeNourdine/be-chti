	PRESERVE8
	THUMB   
		
	include Driver\DriverJeuLaser.inc	
	EXPORT  CallbackSon   
		
	EXTERN GPIOB_Clear
	EXTERN GPIOB_Set

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		
FlagCligno dcd 0 
	EXPORT  SortieSon
	
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		

index dcd 0

CallbackSon  PROC
				push {lr}
				mov r0,#1
				ldr r1,=FlagCligno
				LDR r3,[r1] 
				CMP	 r3,#1
				bne	 setTo1 		
				MOV r3,#0
				STR r3,[r1]
				bl GPIOB_Clear
				pop {lr}	
				bx lr
setTo1
				MOV r3,#1
				STR r3,[r1]
				bl GPIOB_Set
				pop {lr}
				bx lr	
				endp;

END
	
	END