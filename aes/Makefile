all: aesEnc
	gcc -I/usr/local/ssl/include -L/usr/local/ssl/lib -O0 -g -o aes aes.c aesEnc.o -lssl -lcrypto -ldl

aesEnc: aesEnc.c
	gcc -I/usr/local/ssl/include -L/usr/local/ssl/lib -O0 -g -c aesEnc.c -o aesEnc.o -lcrypto