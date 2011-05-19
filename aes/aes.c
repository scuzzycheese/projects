#include <string.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/err.h>

#include "aesEnc.h"

enum cipherDirection
{
	CIPHER_DECRYPT = 0,
	CIPHER_ENCRYPT = 1
};

char *encode(const unsigned char *input, int length);
char *decode(unsigned char *input, int length);
char *encodeMultiBlocks(const unsigned char *input, int length);

int main()
{
	unsigned char *encoded = encode("abc00005d41402abc4b2a76b9719d911017c592", sizeof("abc00005d41402abc4b2a76b9719d911017c592"));
	printf("ENCODED: %s\n", encoded);
	printf("LENGTH: %u\n\n", strlen(encoded));

	unsigned char *decoded = decode(encoded, strlen(encoded));
	printf("DECODED: %s\n", decoded);
	free(encoded);
	free(decoded);
}

//Finish this tomorrow
char *encodeMultiBlock(const unsigned char *input, int length)
{
	unsigned char *blkPtr;
	for(int i = 0, blkPtr = input; i < length; i += 32, blkPtr += 32)
	{
		unsigned char *block = NULL;
		if(length <= 32)
		{
			block = encode(blkPtr, length);
		}
		else
		{
			block = encode(blkPtr, 32);
		}
	}
}

void setCipher(BIO *bioCipher, unsigned char *keyData, int keyDataLen, enum cipherDirection direction)
{
	unsigned char key[32];
	unsigned char iv[32];

	int i = EVP_BytesToKey(EVP_aes_256_ecb(), EVP_sha1(), NULL, keyData, keyDataLen, 1, key, iv);
	if(i != 32)
	{
		printf("Key size is %d bits - should be 256 bits\n", i);
	}
	printf("KEY LEN: %u\n", i);

	//The documentation doesnt tell whether the key or iv need to be permanent, ie: allocated somewhere in memory
	//as they are destroyed after this function
	//Also, the last param: 1 = encrypt, 0 = decrypt
	BIO_set_cipher(bioCipher, EVP_aes_256_ecb(), key, iv, direction);
}

char *encode(const unsigned char *input, int length)
{
	BIO *bioMem;
	BIO *bioB64;
	BIO *bioCipher;
	BUF_MEM *bioBuff;

	bioB64 = BIO_new(BIO_f_base64());
	BIO_set_flags(bioB64, BIO_FLAGS_BASE64_NO_NL);
	bioMem = BIO_new(BIO_s_mem());

	bioCipher = BIO_new(BIO_f_cipher());
	setCipher(bioCipher, "myAesKey12345678", 16, CIPHER_ENCRYPT);

	//build the stack:
	//bioCipher -> bioB64 -> bioMem
	//bioB64 = BIO_push(bioB64, bioMem);
	bioCipher = BIO_push(bioCipher, bioMem);

	BIO_write(bioCipher, input, length);
	BIO_flush(bioCipher);
	BIO_get_mem_ptr(bioCipher, &bioBuff);

	char *encData = (char *) malloc(bioBuff->length + 1);

	memcpy(encData, bioBuff->data, bioBuff->length);
	encData[bioBuff->length - 1] = '\0';

	BIO_free_all(bioCipher);
	return encData;
}

char *decode(unsigned char *input, int length)
{
	printf("Input string: %s\n", input);
	BIO *bioMem;
	BIO *bioB64;
	BIO *bioCipher;

	bioB64 = BIO_new(BIO_f_base64());
	BIO_set_flags(bioB64, BIO_FLAGS_BASE64_NO_NL);
	bioMem = BIO_new_mem_buf(input, length);

	bioCipher = BIO_new(BIO_f_cipher());
	setCipher(bioCipher, "myAesKey12345678", 16, CIPHER_DECRYPT);

	//bioB64 = BIO_push(bioB64, bioMem);
	bioCipher = BIO_push(bioCipher, bioMem);

	char *outBuff = (char *)malloc(length);
	memset(outBuff, 0x00, length);
	int readBytes = BIO_read(bioCipher, outBuff, length);
	printf("Number of bytes read: %d\n", readBytes);
	readBytes = BIO_read(bioCipher, outBuff, length);
	printf("Number of bytes read: %d\n", readBytes);
	outBuff[readBytes] = '\0';


	//BIO_free_all(bioCipher);
	return outBuff;
}


