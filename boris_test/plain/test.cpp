#include "cBuffer.h"
#include "cBufferBase.h"
#include <stdio.h>

#include <stdlib.h>


int main()
{


	cBuffer *buff = (cBuffer *)new(malloc(sizeof(cBuffer))) cBufferBase<cBuffer>();

	buff->copy("hello there my", 15);


	printf("BUFFER: %s\n", buff->currentBuffer());

}
