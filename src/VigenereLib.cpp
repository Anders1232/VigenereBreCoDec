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
	
	static void PrintByteInISO_IEC_8859_1(unsigned char index)
	{
		if(index < 0x7f)
		{
			printf("%c", index);
		}
		else if(0xe7 == index)
		{
			printf("ç");
		}
		else if(0xe3 == index)
		{
			printf("ã");
		}
		else if(0xe9 == index)
		{
			printf("é");
		}
		else if(0xed == index)
		{
			printf("í");
		}
		else if(0xe1 == index)
		{
			printf("á");
		}
		else if(0xf3 == index)
		{
			printf("ó");
		}
		else if(0xf5 == index)
		{
			printf("õ");
		}
		else
		{
			printf("[whot?]");
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
		
		char sp= ' ';
		printf("Chave mais provável: ");
		unsigned char *key= (unsigned char*)malloc(keySize* sizeof (unsigned int));
		if(NULL == key)
		{
			fprintf(stderr, "[ERROR] %s | %s : %d \t Memory allocation fail.\n", __FILE__, __func__, __LINE__ );
			return;
		}
		for(int i=0; i< keySize; i++)
		{
			key[i]= sp ^ (unsigned char)sortedIdexes[i];
			printf("%c", key[i]);
		}
		printf("\n");
		
		printf("provável resposta: \n");
		for(int i=0; i < numOfLines; i++)
		{
			PrintByteInISO_IEC_8859_1(key[i% keySize] ^ chipheredText[i]);
		}
		
		free(key);
		free(occurencesCounter);
		free(chipheredText);
	}
}

