/* 
 * File:   engine.cpp
 * Author: scuzzy
 * 
 * Created on 21 May 2010, 21:52
 */

#include "cEngine.h"

cEngine::cEngine() : newLine(NULL)
{
}


bool cEngine::mStartNewLine(const QPoint &start, const QColor &colour, const int &diameter)
{
	if(!newLine)
	{
		newLine = new cVecLine(colour, diameter);
		return mAddVectToLine(start);
	}
	else return false;
}
bool cEngine::mAddVectToLine(const QPoint &vec)
{
	if(newLine)
	{
		newLine->mAddVector(vec);
		return true;
	}
	else return false;
}
bool cEngine::mEndNewLine()
{
	if(newLine)
	{
		//Copy the line into the lines array
		dLines.push_back(*newLine);
		delete newLine;
		newLine = NULL;
	}
	return true;
}

cVecLine *cEngine::mGetCurrentLine()
{
	if(newLine) return newLine;
	else return NULL;
}

deque<cVecLine> *cEngine::mGetLines()
{
	return &dLines;
}

void cEngine::mClear()
{
	dLines.clear();
}