#include "cBuffer.h"
#include <stdio.h>

#include <stdlib.h>


int main()
{


	cBuffer buff;

	buff.copy("hello there my good good friend,", strlen("hello there my good good friend,")); 
	buff.copy(" how are you doing today?", strlen(" how are you doing today?"));

	buff.dumpBuffers();

}
