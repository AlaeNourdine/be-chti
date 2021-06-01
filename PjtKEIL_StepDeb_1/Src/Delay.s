	PRESERVE8
	THUMB   
		

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		
VarTime	dcd 0

	
; ===============================================================================================
	
;constantes (équivalent du #define en C)
TimeValue	equ 800000


	EXPORT Delay_100ms ; la fonction Delay_100ms est rendue publique donc utilisable par d'autres modules.
	EXPORT VarTime ; Rendue publique temporairement 
		
;Section ROM code (read only) :		
	area    moncode,code,readonly
		


; REMARQUE IMPORTANTE 
; Cette manière de créer une temporisation n'est clairement pas la bonne manière de procéder :
; - elle est peu précise
; - la fonction prend tout le temps CPU pour... ne rien faire...
;
; Pour autant, la fonction montre :
; - les boucles en ASM
; - l'accés écr/lec de variable en RAM
; - le mécanisme d'appel / retour sous programme
;
; et donc possède un intérêt pour débuter en ASM pur

Delay_100ms proc ; Début def procedure
	
	    ldr r0,=VarTime ;   		  
						  
		ldr r1,=TimeValue
		str r1,[r0] ; *VarTime = TimeValue 
		
BoucleTempo	
		ldr r1,[r0] ; TimeValue = *VarTime    				
		
		subs r1,#1 ; TimeValue -= 1
		str  r1,[r0] ; *VarTime = TimeValue 
		bne	 BoucleTempo ; bne = branch if not equal
			
		bx lr ; bx = On jump à l'instruction suivant l'invocation de Delay_100ms (on continue l'exécution du fichier C ici)
		endp ; Fin def procedure
		
		
	END	