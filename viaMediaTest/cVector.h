/* 
 * File:   cVector.h
 * Author: scuzzy
 *
 * Created on 26 January 2012, 4:44 PM
 */

#ifndef _CVECTOR_H
#define	_CVECTOR_H

class cVector
{
public:
	cVector();
	cVector(int xIn, int yIn);
	virtual ~ cVector();
	int getX();
	int getY();
	void setX(int xIn);
	void setY(int yIn);
private:
	union
	{
		int vec[2];
		struct
		{
			int x;
			int y;
		};
	};
};

#endif	/* _CVECTOR_H */

