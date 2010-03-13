#include "cBuffer.h"
#include <stdio.h>

#include <stdlib.h>


int main()
{


	cBuffer buff;

	buff.copy("hello there my", 15);


	printf("BUFFER: %s\n", buff.currentBuffer());

}
