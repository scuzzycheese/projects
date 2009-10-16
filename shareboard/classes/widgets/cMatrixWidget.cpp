#include "cMatrixWidget.h"


cMatrixWidget::cMatrixWidget(QWidget *parent) : QGroupBox(parent), dMat(NULL)
{
	dLayout = new QGridLayout();
	dLayout->setContentsMargins(0, 10, 0, 0);

	m11.setRange(-1000000.0f, 1000000.0f);
	m12.setRange(-1000000.0f, 1000000.0f);
	m21.setRange(-1000000.0f, 1000000.0f);
	m22.setRange(-1000000.0f, 1000000.0f);
	dx.setRange(-1000000.0f, 1000000.0f);
	dy.setRange(-1000000.0f, 1000000.0f);

	m11.setDecimals(4);
	m12.setDecimals(4);
	m21.setDecimals(4);
	m22.setDecimals(4);
	dx.setDecimals(4);
	dy.setDecimals(4);



	null3.setValue(1.0f);

	dLayout->addWidget(&m11, 0, 0); dLayout->addWidget(&m12, 0, 1); dLayout->addWidget(&null1, 0, 2);
	dLayout->addWidget(&m21, 1, 0); dLayout->addWidget(&m22, 1, 1); dLayout->addWidget(&null2, 1, 2);
	dLayout->addWidget(&dx, 2, 0); dLayout->addWidget(&dy, 2, 1); dLayout->addWidget(&null3, 2, 2);
	setLayout(dLayout);
}

void cMatrixWidget::mSetMatrix(QMatrix *matIn)
{
	dMat = matIn;
}

void cMatrixWidget::mUpdate()
{
	if(dMat)
	{
		m11.setValue(dMat->m11());
		m12.setValue(dMat->m12());
		m21.setValue(dMat->m21());
		m22.setValue(dMat->m22());
		dx.setValue(dMat->dx());
		dy.setValue(dMat->dy());
		null3.setValue(1);
	}
}

void cMatrixWidget::mCommit()
{
	if(dMat) dMat->setMatrix(m11.value(), m12.value(), m21.value(), m22.value(), dx.value(), dy.value());
}

cMatrixWidget::~cMatrixWidget()
{
	delete(dLayout);
}


