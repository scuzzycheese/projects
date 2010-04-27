#ifndef PDUH
#define PDUH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

//maco to tell us if things are the correct size or not
#define ASSERT_SIZEOF(t, n) typedef char assert_sizeof_##t[(sizeof(t) == (n)) ? 1 : -1]

//define an integer type that has 32 bits
#ifdef INT32
#define PDUINTTYPE
typedef int m_int32;
#endif

//if we can't tell the architechture, fall back on the default
#ifndef PDUINTTYPE
typedef int m_int32;
#endif

//if the architechture does not support 32bit integer types, fail
ASSERT_SIZEOF(m_int32, 4);

//define a short type that has 16 bits
#ifdef SHORT16
#define PDUSHORTTYPE
typedef short m_short16;
#endif

//if we can't tell the architechture, fall back on the default
#ifndef PDUSHORTTYPE
typedef short m_short16;
#endif

//if the architechture does not support 32bit integer types, fail
ASSERT_SIZEOF(m_short16, 2);

//the maximum length a PDU can be
#define MAX_PDU_LENGTH 2000000



#define MSG_WAITALL 0x8

class cPDU
{

	private:
		char *PDUd;
		//Fake pointer for doing 1byte arithmatic
		char *PDUInc;
		char *data;
		std::string name;

		m_int32 PDULength;
		m_int32 dataLength;
		m_short16 nameLength;

		void build();

	public:

		//Accessors
		std::string getName();
		m_short16 getNameLength();
		void *getData();
		m_int32 getDataLength();
		void *getPDU();
		m_int32 getPDULength();
		cPDU();
		cPDU(void *in);
		cPDU(cPDU &pdu);
		void addFieldName(std::string fn);
		void addData(void *d, m_int32 length);
		~cPDU();
};

#endif
