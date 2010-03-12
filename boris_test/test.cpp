#include "cBuffer.h"
#include "cBufferBase.h"
#include <stdio.h>


int main()
{


	cBuffer buff;

	buff.copy("hello there my", 15);


	printf("BUFFER: %s\n", buff.currentBuffer());

}
