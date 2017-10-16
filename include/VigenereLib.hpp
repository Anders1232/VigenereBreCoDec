#ifndef VIGENERE_LIB
#define VIGENERE_LIB

namespace VigenereLib
{
	void Code(char* fileToCode, char* fileWithKey);
	void Decode(char* fileToDecode, char* fileWithKey);
	void Break(char* fileToBreak);
}

#endif
