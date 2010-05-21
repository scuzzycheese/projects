#ifndef CMATRIXWIDGET_H
#define CMATRIXWIDGET_H



#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDoubleSpinBox>

class cMatrixWidget : public QGroupBox
{

	Q_OBJECT

	public:
		QMatrix *dMat;
		QGridLayout *dLayout;

		QDoubleSpinBox m11;
		QDoubleSpinBox m12;
		QDoubleSpinBox m21;
		QDoubleSpinBox m22;
		QDoubleSpinBox dx;
		QDoubleSpinBox dy;
		QDoubleSpinBox null1;
		QDoubleSpinBox null2;
		QDoubleSpinBox null3;

		cMatrixWidget(QWidget *parent);
		~cMatrixWidget();


		void mSetMatrix(QMatrix *matIn);
	public slots:
		void mUpdate();
		void mCommit();

};


#endif

