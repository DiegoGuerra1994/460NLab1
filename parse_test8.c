	#include <stdio.h>	/* standard input/output library */
	#include <stdlib.h>	/* Standard C Library */
	#include <string.h>	/* String operations library */
	#include <ctype.h>	/* Library for useful character operations */
	#include <limits.h>	/* Library for definitions of common variable type characteristics */
	
	/*char* lPtr;*/

	#define MAX_LINE_LENGTH 255
	#define symbolTableLength 500
	enum{
	   DONE, OK, EMPTY_LINE, LABEL
	};

	enum opcode{
		BR, ADD, LDB, STB, JSR, AND, LDW, STW, RTI, XOR, JMP, SHF, LEA, TRAP
	};

	typedef struct table{
		int addr;
		char* name;
	} sym_table;

	sym_table symbol_table[symbolTableLength]; /*make symbol table array*/

	int label = 0; /*true if parser found label*/

	int readAndParse( FILE * pInfile, char * pLine, char ** pLabel, char ** pOpcode, char ** pArg1, char ** pArg2, char ** pArg3, char ** pArg4)
	{
	   char * lRet ,*lPtr;
	   int i;
	   if( !fgets( pLine, MAX_LINE_LENGTH, pInfile ) )
		return( DONE );
	   for( i = 0; i < strlen( pLine ); i++ )
		pLine[i] = tolower( pLine[i] );
	   
           /* convert entire line to lowercase */
	   *pLabel = *pOpcode = *pArg1 = *pArg2 = *pArg3 = *pArg4 = pLine + strlen(pLine);

	   /* ignore the comments */
	   lPtr = pLine; 

	   while( *lPtr != ';' && *lPtr != '\0' && *lPtr != '\n' )
		lPtr++;

	    *lPtr = '\0';
	   if( !(lPtr = strtok( pLine, "\t\n ," ) ) ) 
		return( EMPTY_LINE );

	   if( isOpcode( lPtr ) == -1 && lPtr[0] != '.' ){ /* found a label */
		*pLabel = lPtr;
		label = 1;
		/*printf("Found a label\n");*/
		if( !( lPtr = strtok( NULL, "\t\n ," )))  return( OK );
		/*return (LABEL);*/
	   } /*null pointer may be specified, in which case the function continues scanning 
	     where a previous successful call to the function ended.*/
	   
           *pOpcode = lPtr;

	   if( !( lPtr = strtok( NULL, "\t\n ," ))) return(OK ); 
	   
           *pArg1 = lPtr;
	   
           if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

	   *pArg2 = lPtr;
	   if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

	   *pArg3 = lPtr;

	   if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

	   *pArg4 = lPtr;

	   return( OK );
	}
	 /*returns -1 if invalid opcode*/
	int isOpcode(char* inStr){
		if (strcmp(inStr,"add") == 0){
			return 0;
		}
		else if (strcmp(inStr,"and") == 0){
			return 0;
		}
		else if (strcmp(inStr,"br") == 0){
			return 0;
		}
		else if (strcmp(inStr,"brn") == 0){
			return 0;
		}
		else if (strcmp(inStr,"brp") == 0){
			return 0;
		}
		else if (strcmp(inStr,"brnp") == 0){
			return 0;
		}
		else if (strcmp(inStr,"brz") == 0){
			return 0;
		}
		else if (strcmp(inStr,"brnz") == 0){
			return 0;
		}
		else if (strcmp(inStr,"brzp") == 0){
			return 0;
		}
		else if (strcmp(inStr,"brnzp") == 0){
			return 0;
		}
		else if (strcmp(inStr,"halt") == 0){
			return 0;
		}
		else if (strcmp(inStr,"jmp") == 0){
			return 0;
		}
		else if (strcmp(inStr,"jsr") == 0){
			return 0;
		}
		else if (strcmp(inStr,"jsrr") == 0){
			return 0;
		}
		else if (strcmp(inStr,"ldb") == 0){
			return 0;
		}
		else if (strcmp(inStr,"ldw") == 0){
			return 0;
		}
		else if (strcmp(inStr,"lea") == 0){
			return 0;
		}
		else if (strcmp(inStr,"nop") == 0){
			return 0;
		}
		else if (strcmp(inStr,"not") == 0){
			return 0;
		}
		else if (strcmp(inStr,"ret") == 0){
			return 0;
		}
		else if (strcmp(inStr,"lshf") == 0){
			return 0;
		}
		else if (strcmp(inStr,"rshfl") == 0){
			return 0;
		}
		else if (strcmp(inStr,"rshfa") == 0){
			return 0;
		}
		else if (strcmp(inStr,"rti") == 0){
			return 0;
		}
		else if (strcmp(inStr,"stb") == 0){
			return 0;
		}
		else if (strcmp(inStr,"stw") == 0){
			return 0;
		}
		else if (strcmp(inStr,"trap") == 0){
			return 0;
		}
		else if (strcmp(inStr,"xor") == 0){
			return 0;
		}
		else{
			return -1;
		}

	}


int returnOffset(char* symbol, int pointer){
	int x;
	for(x=0; x < symbolTableLength; x++){
			if(strcmp(symbol_table[x].name, symbol) == 0){
				return pointer - symbol_table[x].addr-1;
			}
	}

	return -1;

}

int toNum( char * pStr ){
   char * t_ptr;
   char * orig_pStr;
   int t_length,k;
   int lNum, lNeg = 0;
   long int lNumLong;

   orig_pStr = pStr;
   if( *pStr == '#' )			/* decimal */
   { 
     pStr++;
     if( *pStr == '-' )			/* dec is negative */
     {
       lNeg = 1;
       pStr++;
     }
     t_ptr = pStr;
     t_length = strlen(t_ptr);
     for(k=0;k < t_length;k++)
     {
       if (!isdigit(*t_ptr))
       {
	 printf("Error: invalid decimal operand, %s\n",orig_pStr);
	 exit(4);
       }
       t_ptr++;
     }
     lNum = atoi(pStr);
     if (lNeg)
       lNum = -lNum;
 
     return lNum;
   }
   else if( *pStr == 'x' )	/* hex */
   {
     pStr++;
     if( *pStr == '-' )			/* hex is negative */
     {
       lNeg = 1;
       pStr++;
     }
     t_ptr = pStr;
     t_length = strlen(t_ptr);
     for(k=0;k < t_length;k++)
     {
       if (!isxdigit(*t_ptr))
       {
	 printf("Error: invalid hex operand, %s\n",orig_pStr);
	 exit(4);
       }
       t_ptr++;
     }
     lNumLong = strtol(pStr, NULL, 16);    /* convert hex string into integer */
     lNum = (lNumLong > INT_MAX)? INT_MAX : lNumLong;
     if( lNeg )
       lNum = -lNum;
     return lNum;
   }
   else
   {
	printf( "Error: invalid operand, %s\n", orig_pStr);
	exit(4); 
	/*This has been changed from error code 3 to error code 4, see clarification 12 */
   }
}

	/* Note: MAX_LINE_LENGTH, OK, EMPTY_LINE, and DONE are defined values */
int main (){

	   char lLine[MAX_LINE_LENGTH + 1], *lLabel, *lOpcode, *lArg1, *lArg2, *lArg3, *lArg4;
	   int lRet;
	   int i = 0;
	   int ctr = 0;
	   int addrCtr; /*used in 2nd pass of program*/
	   int mach_code = 0;
	   int arg1_num = 0;
	   int orig; /*start addr of program*/
	   int offs; /*offset from current addr to label*/
	  
	   FILE * pOutfile;
	   pOutfile = fopen( "data.out", "w" );

	   int endDefined = 0;
	   FILE * lInfile;
	   lInfile = fopen("data.in", "r");	/* open the input file */
	  
	    /*find start address of program*/
	   do{
	   	lRet = readAndParse( lInfile, lLine, &lLabel, &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
		if (strcmp(lOpcode, ".orig") == 0){
                 	orig = toNum(lArg1);
			printf("%i\n",orig);
                }

        else if (strcmp(lOpcode, ".end") == 0){
                 	endDefined = 1;
                }

	   } while (lRet != DONE);


	   /*If there is no .END, then throw an error*/
	   	if(endDefined == 0){
	   		error(4);
	   	}


        /*1st pass: generate symbol table*/
	   /* lInfile = fopen("data.in", "r");*/     /* open the input file */
	   rewind(lInfile);	
	   do{	
	 	lRet = readAndParse( lInfile, lLine, &lLabel, &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
		printf("1st pass");
		printf("	lRet: %i\n", lRet);
		if (label){
			symbol_table[i].addr = orig + ctr;
			printf("address: %i\n", symbol_table[i].addr);	
			symbol_table[i].name = lLabel;
			printf("label: %s\n", symbol_table[i].name);
			label = 0;
			i++; 
		}
 		ctr++;
	   } while( lRet != DONE );

	    /*writeText(mach_code);2nd pass: generate machine code*/
	   /*lInfile = fopen("data.in", "r");*/     /* open the input file */
	   rewind(lInfile);
	   do
	   {	
	   	addrCtr = orig;
	   	lRet = readAndParse( lInfile, lLine, &lLabel, &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
		printf("label:%s", lLabel);
		printf(" opcode:%s", lOpcode);
		printf(" arg1:%s", lArg1);
		printf(" arg2:%s ", lArg2);
		printf(" arg3:%s\n", lArg3);
		if( lRet != DONE && lRet != EMPTY_LINE ){
			/*generate machine code (hex) given the parsed opcodes*/
				if (strcmp(lOpcode, ".orig") == 0){
					fprintf( pOutfile, "0x%.4X\n", orig);
				}

				if (strcmp(lOpcode, "br") || strcmp(lOpcode, "brnzp") == 0){
					/*need condition for n, z, p,*/ 
					offs = returnOffset(lArg1, addrCtr);
					/*check if offset is too big!!!*/
					mach_code = offs;
				}

				else if (strcmp(lOpcode, "add") == 0){
					mach_code = (ADD << 12) + ((lArg1[1] - 0x30)<<9) + ((lArg2[1] - 0x30)<<6);
					mach_code &= 0xFFC0; /*clearing the last 6 bits*/
					/*see if the number being added is a constant number*/
					if( (lArg3[0] == 'x') || (lArg3[0] == '#')){
						mach_code |= 0x10; /*Changing the 5th bit to 1 since we are adding a constant*/
						mach_code += toNum(lArg3);
					}
					/*Argument 3 is a register*/
					else{
						mach_code += (lArg3[1] - 0x30);
					}
					fprintf( pOutfile, "0x%.4X\n", mach_code);
				}


				else if (strcmp(lOpcode, "ldb") == 0){
					 /*extract reg number from arguments, then shift to correct place*/
					mach_code = (LDB << 12) + ((lArg1[1] - 0x30)<<9) + ((lArg2[1] - 0x30)<<6); 

					 /* put constant in bits[5:0]*/
					mach_code &= 0xFFC0;
					mach_code += toNum(lArg3);
					printf("mach_code: %i\n", mach_code);
					fprintf( pOutfile, "0x%.4X\n", mach_code);
			
				}				
				else if (strcmp(lOpcode, "stb") == 0){
					  /*extract reg number from arguments, then shift to correct place*/
                                        mach_code = (STB << 12) + ((lArg1[1] - 0x30)<<9) + ((lArg2[1] - 0x30)<<6);

                                         /* put constant in bits[5:0]*/
                                        mach_code &= 0xFFC0;
                                        mach_code += toNum(lArg3);
                                        printf("mach_code: %i\n", mach_code);
					fprintf( pOutfile, "0x%.4X\n", mach_code);

				}

				else if (strcmp(lOpcode, "jsr") == 0 || strcmp(lOpcode, "jsrr") == 0){
						
						if (strcmp(lOpcode, "jsr") == 0)
						{
							mach_code = (JSR << 12) + 1<<11;
						}
						else 
						{
							mach_code = (JSR << 12) + ((lArg1[1] - 0x30) << 5);
						}
						 
				}
				/*fprintf( pOutfile, "0x%.4X\n", mach_code);*/
				printf("MACH_CODE!:  %i\n", mach_code);


				addrCtr++;

		}
	   } while( lRet != DONE );
	   fclose(pOutfile);

	}


