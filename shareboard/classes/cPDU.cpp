#include "cPDU.h"



void cPDU::build()
{
	/**
	 * Formula:
	 * 	PDULength(m_int32)
	 * 		nameLength(m_short16)
	 * 			name(char *)
	 * 		dataLength(m_int32)
	 * 			data(char *)
	 */

	//PDULength includes ittself in the length	
	PDULength = sizeof(PDULength) + sizeof(nameLength) + nameLength + sizeof(dataLength) + dataLength;

	if(PDULength > 0 && PDULength <= MAX_PDU_LENGTH)
	{
		PDUd = new char[PDULength];
		PDUInc = PDUd;

		//now we construct the PDU in a single block of memory
		memcpy(PDUInc, &PDULength, sizeof(PDULength));
		PDUInc += sizeof(PDULength);
	
		memcpy(PDUInc, &nameLength, sizeof(nameLength));
		PDUInc += sizeof(nameLength);

		memcpy(PDUInc, name.c_str(), nameLength);
		PDUInc += nameLength;

		memcpy(PDUInc, &dataLength, sizeof(dataLength));
		PDUInc += sizeof(dataLength);

		memcpy(PDUInc, data, dataLength);
		//no need to increment again as we are not going to add more data
	}
	else
	{
		//invalid PDU
		PDULength = 0;
	}
}


std::string cPDU::mGetName()
{
	if(!PDUd) build();
	return name;
}

m_short16 cPDU::mGetNameLength()
{
	if(!PDUd) build();
	return nameLength;
}

char *cPDU::mGetData()
{
	if(!PDUd) build();
	return data;
}

m_int32 cPDU::mGetDataLength()
{
	if(!PDUd) build();
	return dataLength;
}

char *cPDU::mGetPDU()
{
	if(!PDUd) build();
	return PDUd;
}

m_int32 cPDU::mGetPDULength()
{
	if(!PDUd) build();
	return PDULength;
}


cPDU::cPDU() : PDUd(NULL), PDUInc(NULL), data(NULL), PDULength(0), dataLength(0), nameLength(0)
{
}

cPDU::cPDU(cPDU &pdu)
{
		//Damnit Silex, you got me again!
		//NOTE: KEEP THIS UP TO DATE

		//non allocation members
		PDULength = pdu.PDULength;
		dataLength = pdu.dataLength;
		nameLength = pdu.nameLength;

		//pointers;
		PDUd = new char[PDULength];
		memcpy(PDUd, pdu.PDUd, PDULength);
		PDUInc = (char *)PDUd;

		data = new char[dataLength];
		memcpy(data, pdu.data, dataLength);

		//I think strings take care of themselves
		name = pdu.name;
}


cPDU::cPDU(char *in) : PDUd(NULL), PDUInc(NULL), data(NULL), PDULength(0), dataLength(0), nameLength(0)
{
	char *inData = (char *)in;
	char *beginInData = inData;
	//Parse the PDU
	memcpy(&PDULength, inData, sizeof(PDULength)); 
	inData += sizeof(PDULength);

	memcpy(&nameLength, inData, sizeof(nameLength));
	inData += sizeof(nameLength);
	
	char *inName = new char[nameLength + 1];
	//we null terminate just incase it's not already null terminated
	//as it won't be if it's created with this library
	inName[nameLength] = 0x00;
	memcpy(inName, inData, nameLength);
	name = std::string(inName);
	inData += nameLength;

	memcpy(&dataLength, inData, sizeof(dataLength));
	inData += sizeof(dataLength);

	data = new char[dataLength];
	memcpy(data, inData, dataLength);

	delete[](inName);
	//This should be freed automagically
	delete[](beginInData);
}


void cPDU::mAddFieldName(std::string fn)
{
	name = fn;
	nameLength = name.length();
}

void cPDU::mAddData(char *d, m_int32 length)
{
	data = new char[length];
	memcpy(data, d, length);
	dataLength = length;
}



cPDU::~cPDU()
{
	//only free if there is actually memory allocated
	if(data)
	{
		delete[](data);
		data = NULL;
	}
	if(PDUd)
	{
		delete[](PDUd);
		PDUd = NULL;
	}
}
