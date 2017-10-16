#include "string.h"
#include "VigenereLib.hpp"

int main(int argc, char **argv)
{
	bool validArguents= false;
	if(4 == argc)
	{
		if(!strcmp(argv[1], "cod") )
		{
			validArguents=true;
//			VigenereLib::Code(argv[2], argv[3]);
		}
		else if(!strcmp(argv[1], "dec") )
		{
			validArguents=true;
//			VigenereLib::Decode(argv[2], argv[3]);
			
		}
	}
	else if(3 == argc){
		if(!strcmp(argv[1], "bre")){
			validArguents=true;
			VigenereLib::Break(argv[2]);
		}
	}
	if(!validArguents){
//		ShowHelpMessage();
	}
}
