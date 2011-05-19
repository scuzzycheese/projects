all: aesEnc
	gcc -O0 -g -o aes aes.c aesEnc.o -lssl -lcrypto

aesEnc: aesEnc.c
	gcc -O0 -g -c aesEnc.c -o aesEnc.o -lcrypto