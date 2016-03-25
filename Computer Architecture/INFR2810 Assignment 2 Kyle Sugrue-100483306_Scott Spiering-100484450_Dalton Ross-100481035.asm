######################################################################################
##################[INFR 2810 : Computer Architecture - Assignment 2]##################
####[Kyle Sugrue - 100483306][Scott Spiering - 100484450][Dalton Ross - 100481035]####
######################################################################################

#Values are being hard coded, X was set to 128 during testing, and so it has been left to initialize X as a word
.data 
	N:			.word 10
	X: 			.word 128
	A: 			.word 128,10,23,12,128,9,220,46,128,5
	CLEAR:		.word 0

#String that are to be printed are set
	Req_Input: 	.asciiz "Please enter a number to search the array for:"
	Result:		.asciiz "Number matches found:"
 
#.text allows us to print stings 
.text 						  				 

#our main function
main: 

								#Prints Req_Input string to the console
	la $a0, Req_Input			#loads the address of Req_Input in a0
	li $v0, 4					#loads the the service code (integer value) for the system
	syscall
								#Gets X value (provided by the user)
	la $a0, X					#loads the address of X into a0
	la $a1, X					#loads the size of x in a1 (out of bounds prevention)
	li $v0, 5					#loads the integer value 5 (service code for read in an integer)
	syscall

	sw $v0, X					#stores the received value, which was stored in v0, into X
	
								#call the COUNT function (the following set-up the arguments for the function)
	la $a0, A					#loads the address of A into a0
	lw $a1, N					#loads the address of N into a1
	lw $a2, X					#loads the address of X into a2
	jal COUNT					#calls the function and sets ra to the following line

	move $t1, $v0				#moves the returned variable into t1 (how many of X was found within the string)
	
								#prints the result string to the console
	la $a0, Result				#loads the address of Result into a0
	li $v0, 4					#loads the appropriate service code (4 for print string)
	syscall
								#prints the results
	move $a0, $t1				#moves the results from t1 to a0
	li $v0, 1					#loads the service code (1 to print integers)
	syscall

li $v0, 10						#loads service code 10 to signal the end of the program, IE exit
syscall 					


#our count function, translated from:
######################################
##int count(int a[], int n, int x){	##
##	int res = 0; 					##
##	int i = 0; 						##
##	for(i = 0; i != n; i++)			##
##		if(a[i] == x)				##
##			res = res + 1;			##
##	return res; 					##
##}									##
######################################

COUNT:
	lw $v0, CLEAR				#Clears v0, sets it to 0
	
	LOOP:  						
		beq $t0, $a1, DONE		#compares t0 to a1, to see if we have searched the entire array, once completed jump to "done"
			lw $t2, 0($a0)		#loads a new value from the array to compare
			beq $a2, $t2, THEN	#compares the newly loaded value from the array to the value we are searching for (t2 = array value, a2 = value we are searching for), if there is a match jump to "then"
				j NEXT			#jumps to the next section if the values did not  match
			
			THEN: 				#if the values did match continue here
			addi $v0, $v0, 1	#increment the returned value by 1
			
			NEXT:				#if the values did not match continue here, values that matched continue also
			addi $a0, $a0, 4	#increment the address stored in a0 to obtain the next value in the array during the next iteration of the loop 
			addi $t0, $t0, 1	#increment the tracking value (I of our for loop) to keep track of our progress in the array
		j LOOP					#return to the start of the loop (jump to "loop")
		
	DONE: 						
jr $ra							#once done, return and execute the line following the function call