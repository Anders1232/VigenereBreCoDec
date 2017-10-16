#include "VigenereLib.hpp"
//#include "Error.h"
#include <stdlib.h>
#include <stdio.h>

namespace VigenereLib {
	
//	Code(char* fileToCode, char* fileWithKey);
//	Decode(char* fileToDecode, char* fileWithKey);
	void Break(char* fileToBreak){
		FILE* f= fopen(fileToBreak, "r");
		if(NULL == f){
			fprintf(stderr, "[ERROR] %s | %s : %d \t Could not open file %s, does it exists?\n", __FILE__, __func__, __LINE__, fileToBreak );
			return;
		}
		int numOfLines=0;
		int aux;
		while(1 == fscanf(f, " %d", &aux))
		{
			numOfLines++;
		}
		fseek(f, 0, SEEK_SET);
		unsigned char *v= (unsigned char*)malloc( (numOfLines+1)* sizeof(unsigned char) );
		v[numOfLines]= '\0';
		if(NULL == v){
			fprintf(stderr, "[ERROR] %s | %s : %d \t Memory allocation fail.\n", __FILE__, __func__, __LINE__ );
			return;
		}
		for(int i=0; i< numOfLines; i++){
			fscanf(f, " %hhu", &(v[i] ) );
		}
		//leitura concluída
//		printf("\nchiphered message: %s\n", v);
		for(int i= numOfLines/2; i >= 1; i--)
		{//para cada um dos tamanhos prováveis de chave
			
		}
	}
}

