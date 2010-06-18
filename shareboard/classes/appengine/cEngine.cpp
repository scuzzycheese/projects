/* 
 * File:   engine.cpp
 * Author: scuzzy
 * 
 * Created on 21 May 2010, 21:52
 */

#include "cEngine.h"

cEngine::cEngine() : newLine(NULL), dOperationTranslation(1, 0, 0, 1, 319, 164)
{
	dScale = 1.0f;
	matrixChanged = false;
	dServer = NULL;
	dClient = new cClient();
}


bool cEngine::mStartNewLine(const QPoint &start, const QColor &colour, const int &diameter)
{
	dInvertedWorldMatrix = dWorldMatrix.inverted();

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
		newLine->mAddVector(dInvertedWorldMatrix.map(vec));
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

void cEngine::mResetMatrices()
{
	dWorldMatrix.reset();
	dInvertedWorldMatrix.reset();
	dRotationMatrix.reset();
	dTranslationMatrix.reset();
	dScaleMatrix.reset();
	dOperationTranslation.setMatrix(1, 0, 0, 1, 319, 164);
	dScale = 1.0f;
	matrixChanged = true;
}

bool cEngine::mMatrixChanged()
{
	if(matrixChanged)
	{
		matrixChanged = false;
		return true;
	}
	return false;
}

void cEngine::mScale(const int &scale)
{
	dScale = 1 + ((double)scale / 10.0f);
	dScaleMatrix = dOperationTranslation.inverted() * QMatrix(dScale, 0, 0, dScale, 0, 0) * dOperationTranslation;
	dWorldMatrix = dScaleMatrix * dTranslationMatrix;
	matrixChanged = true;
}



void cEngine::mTranslate(const QPoint &transBy)
{
	//I think this needs to be here, because scaling performs quite complex
	//operations on the matrix, the scale matrix has to be updated with
	//every translation operation
	dScaleMatrix = dOperationTranslation.inverted() * QMatrix(dScale, 0, 0, dScale, 0, 0) * dOperationTranslation;


	QMatrix tempMatrix = dScaleMatrix;
	tempMatrix.setMatrix(tempMatrix.m11(), tempMatrix.m12(), tempMatrix.m21(), tempMatrix.m22(), 0, 0);
	QPointF tempPoint = tempMatrix.inverted().map(QPointF(transBy));


	dOperationTranslation.translate(-tempPoint.x(), -tempPoint.y());
	dTranslationMatrix.translate(tempPoint.x(), tempPoint.y());

	dWorldMatrix = dScaleMatrix * dTranslationMatrix;
	matrixChanged = true;
}




/*
void cVectorDrawWidget::rotateSlot(const int &angle)
{
	double pi = 3.14159;

	double a = pi/180 * (double)angle;
	double sina = sin(a);
	double cosa = cos(a);





	dRotationMatrix = QMatrix(cosa, sina, -sina, cosa, 0, 0);
	QMatrix newTrans = dOperationTranslation.inverted() * dTranslationMatrix * dRotationMatrix * dOperationTranslation;
	QPoint transVector(newTrans.dx() - dTranslationMatrix.dx(), newTrans.dy() - dTranslationMatrix.dy());
	translate(transVector);





	dRotationMatrix = QMatrix(cosa, sina, -sina, cosa, 0, 0);
	mDumpMatrix("dOperationTranslation", dOperationTranslation);
	mDumpMatrix("dTranslationMatrix", dTranslationMatrix);
	mDumpMatrix("dRotationMatrix", dRotationMatrix);
	dTranslationMatrix = dOperationTranslation.inverted() * dTranslationMatrix * dRotationMatrix * dOperationTranslation;
	mSetRotationToIdentity(dTranslationMatrix);
	dWorldMatrix = dScaleMatrix * dRotationMatrix * dTranslationMatrix;
	emit mMatrixChanged();

}
*/



bool cEngine::mStartServer(QString serverName)
{
	if(dServer == NULL)
	{
		dServer = new cServer(serverName);
		return true;
	}
	else
	{
		return false;
	}
}
void cEngine::mConnectToHost(const QString &host, quint16 port)
{
	dClient->mConnectToHost(host, port);
}

