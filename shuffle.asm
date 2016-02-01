			.ORIG x3000
			LEA R0, maskaddr
			LDW R0, R0, #0 ; 
			LDB R0, R0, #0 ; R0 = mask control
			LEA R1, startaddr
			LDW R1, R1, #0 ; R1 = x4000 (base addr)
			AND R2, R2, #0 ; 
			ADD R2, R2, #4 ; R2 = counter
			LEA R3, storeaddr 
			LDW R3, R3, #0 ; R3 = x4005 (store addr)

again		AND R4, R0, #3 ; get rightmost 2 bits
			ADD R5, R1, R4 ;
			LDB R6, R5, #0 ; get memory content specified by mask control			
			STB R6, R3, #0
			ADD R3, R3, #1 ; incr store address
			RSHFL R0, R0, #2
			ADD R2, R2, #-1 ;decr counter
			BRp again
			HALT
maskaddr	.FILL x4004
startaddr	.FILL x4000
storeaddr	.FILL x4005
			.END
