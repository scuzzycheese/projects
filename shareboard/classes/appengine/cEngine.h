/* 
 * File:   engine.h
 * Author: scuzzy
 *
 * Created on 21 May 2010, 21:52
 */

#ifndef CENGINE_H
#define	CENGINE_H

#include "cVecLine.h"
#include <deque>

class cEngine
{
private:
	deque<cVecLine> dLines;
	cVecLine *newLine;



public:
	cEngine();
	cEngine(const cEngine& orig);
	virtual ~cEngine()
	{
	}


	//These methods need to exist, because each point needs to inverted against the world matrix.
	//NOTE: these methods are contextual
	bool mStartNewLine(const QPoint &start, const QColor &colour, const int &diameter);
	bool mAddVectToLine(const QPoint &vec);
	bool mEndNewLine();

	cVecLine *mGetCurrentLine();
	deque<cVecLine> *mGetLines();

	void mClear();


};

#endif	/* _ENGINE_H */

