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
#include <QMatrix>
#include "cServer.h"
#include "cClient.h"

class cEngine
{
private:
	deque<cVecLine> dLines;
	cVecLine *newLine;

	bool matrixChanged;

public:
	//This is the translation matrix that we rotate and scale around
	QMatrix dOperationTranslation;

	//Matrix related stuff
	QMatrix dWorldMatrix;
	QMatrix dInvertedWorldMatrix;

	QMatrix dTranslationMatrix;
	QMatrix dRotationMatrix;
	QMatrix dScaleMatrix;
	double dScale;

	cServer *dServer;
	cClient *dClient;

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

	//Matrix stuff
	void mResetMatrices();

	void mScale(const int &scale);
	void mTranslate(const QPoint &transBy);

	bool mMatrixChanged();

	bool mStartServer(QString serverName);
	void mConnectToHost(const QString &host, quint16 port);


};

#endif	/* _ENGINE_H */

