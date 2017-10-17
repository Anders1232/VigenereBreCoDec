#include "VigenereLib.hpp"
//#include "Error.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

namespace VigenereLib {
	struct VigenereSharedArea{
		int currentKey;
		int *occurencesCounter;
	} vigenereSharedArea;
	
	
	int CompareByOccurences(void const *p1, void const *p2)
	{
		int i1, i2;
		i1= *( (int*) p1);
		i2= *((int*)p2);
		int currentKey= vigenereSharedArea.currentKey;
		return ( vigenereSharedArea.occurencesCounter[currentKey*256+i2] - vigenereSharedArea.occurencesCounter[currentKey*256+i1] );
	}
	
	static void ImprimrCharMaisComum(int index)
	{
		switch(index):
		{
			case (0):
				printf(" ");
				break;
			case (1):
				printf("e");
				break;
			case (2):
				printf("a");
				break;
			case (3):
				printf("o");
				break;
			case (4):
				printf("r");
				break;
			case (5):
				printf("s");
				break;
			case (6):
				printf("d");
				break;
			case (7):
				printf("n");
				break;
			case (8):
				printf("t");
				break;
			case (9):
				printf("m");
				break;
			case (10):
				printf("i");
				break;
			case (11):
				printf("p");
				break;
			case (12):
				printf("c");
				break;
			case (13):
				printf("g");
				break;
			case (14):
				printf("l");
				break;
			case (15):
				printf("u");
				break;
			case (16):
				printf("ç");
				break;
			case (17):
				printf("v");
				break;
			case (18):
				printf("ã");
				break;
			case (19):
				printf("f");
				break;
			case (20):
				printf(",");
				break;
			case (21):
				printf("b");
				break;
			case (22):
				printf(".");
				break;
			case (23):
				printf("q");
				break;
			case (24):
				printf("é");
				break;
			case (25):
				printf("í");
				break;
			case (26):
				printf("-");
				break;
			case (27):
				printf("E");
				break;
			case (28):
				printf("U");
				break;
			case (29):
				printf("h");
				break;
			case (30):
				printf("j");
				break;
			case (31):
				printf("w");
				break;
			case (32):
				printf("x");
				break;
			case (33):
				printf("á");
				break;
			case (34):
				printf("ó");
				break;
			case (35):
				printf("ô");
				break;
			default:
				printf("?");
		}
	}
	
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
		unsigned char *chipheredText= (unsigned char*)malloc( (numOfLines+1)* sizeof(unsigned char) );
		chipheredText[numOfLines]= '\0';
		if(NULL == chipheredText)
		{
			fprintf(stderr, "[ERROR] %s | %s : %d \t Memory allocation fail.\n", __FILE__, __func__, __LINE__ );
			return;
		}
		for(int i=0; i< numOfLines; i++)
		{
			fscanf(f, " %hhu", &(chipheredText[i] ) );
		}
		fclose(f);
		//leitura concluída
//		printf("\nchiphered message: %s\n", v);
		int* repetitions= (int*) malloc (numOfLines/2 * sizeof(int));
		if(NULL == repetitions)
		{
			fprintf(stderr, "[ERROR] %s | %s : %d \t Memory allocation fail.\n", __FILE__, __func__, __LINE__ );
			return;
		}
		memset(repetitions, 0, numOfLines/2 * sizeof(int));
		for(int i= numOfLines/2; i >= 1; i--)
		{//para cada um dos tamanhos prováveis de chave
			int limiteContador= numOfLines/2-i;
			for(int count=0; count < limiteContador; count++)
			{
				if(chipheredText[count] == chipheredText[count+i])
				{
					(repetitions[i])++;
				}
			}
		}
		printf("Number of repetitions per gap:\n");
		float media=0;
		for(int count=0; count < numOfLines/2; count++)
		{
			printf("%d:\t%d\n", count, repetitions[count]);
			media+= (float)repetitions[count];
		}
		free(repetitions);
		media = media /(numOfLines/2);
		printf("media= %f\n", media);
		int keySize;
		printf("Please enter key size: ");
		scanf("%d", &keySize);
		
		int *occurencesCounter= (int*)malloc(keySize * 256 *sizeof(int));
		if(NULL == occurencesCounter)
		{
			fprintf(stderr, "[ERROR] %s | %s : %d \t Memory allocation fail.\n", __FILE__, __func__, __LINE__ );
			return;
		}
		memset(occurencesCounter, 0, keySize * 256 *sizeof(int));
		for(int i=0; i < numOfLines; i++)
		{
			(occurencesCounter[ (i%keySize)*256 + chipheredText[i] ])++;
		}
		
		printf("Distribution os characters:");
		int sortedIdexes[256];
		for(int i=0; i< 256; i++)
		{
			sortedIdexes[i]= i;
		}
		vigenereSharedArea.occurencesCounter= occurencesCounter;
		for(int i=0; i < keySize; i++)
		{
			printf("section %d of %d:\n", i, keySize);
			vigenereSharedArea.currentKey= i;
			qsort(sortedIdexes, 256, sizeof(int), CompareByOccurences);
			for(int j=0; j< 256; j++)
			{
				printf("%d\tis repeated \t%d\n", sortedIdexes[j], occurencesCounter[i*256+ sortedIdexes[j]] );
			}
		}
		
		
		
		
		free(occurencesCounter);
		free(chipheredText);
	}
}

