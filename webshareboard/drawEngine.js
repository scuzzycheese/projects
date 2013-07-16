function drawEngine(canvas, context)
{
	this.dCanvas = canvas;
	this.dContext = context;
	this.dLines = new Array();
	this.dCurrentLine = null;
	this.dMatrixChanged = false;

	this.resetMatrices = function()
	{
		this.dOperationTranslationMatrix = new Matrix.create
		([
			[1,0,0],
			[0,1,0],
			[this.dCanvas.width/2, this.dCanvas.height/2, 0]
		]);
		this.dScaleMatrix = new Matrix.I(3);
		this.dTranslationMatrix = new Matrix.I(3);
		this.dWorldMatrix = new Matrix.I(3);
		this.dInvertedWorldMatrix = new Matrix.I(3);

		this.dScale = 1;
	}
	this.resetMatrices();

	this.scale = function(scaleValue)
	{
		this.dScale = 1 + (scaleValue / 10);
		this.dScaleMatrix = this.dOperationTranslationMatrix.inverse().x(new Matrix.create([[this.dScale, 0, 0],[0, this.dScale, 0],[0, 0, 0]])).x(this.dOperationTranslationMatrix);
		this.dWorldMatrix = this.dScaleMatrix.x(this.dTranslationMatrix);
		this.dMatrixChanged = true;
	}

	this.translate = function(transBy)
	{
		this.dScaleMatrix = this.dOperationTranslationMatrix.inverse().x(new Matrix.create([[this.dScale, 0, 0],[0, this.dScale, 0],[0, 0, 0]])).x(this.dOperationTranslationMatrix);
		var tempMatrix = this.dScaleMatrix;
	}
/*
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
*/

	this.startNewLine = function(point, currentPenColor, currentPenWidth)
	{
		context.beginPath();
		context.moveTo(point.x, point.y);
		this.dCurrentLine = new drawLine(point, currentPenColor, currentPenWidth);
		this.dLines.push(this.dCurrentLine);
	}

	this.addToLine = function(point)
	{
		context.lineTo(point.x, point.y);
		context.stroke();
		this.dCurrentLine.addVectorToLine(point);
	}

	this.finishLine = function()
	{
		this.dCurrentLine.finishLine();
	}


}


function drawLine(startPoint, color, width)
{
	this.color = color;
	this.width = width;
	this.vectors = [startPoint];

	this.addVectorToLine = function(point)
	{
		this.vectors.push(point);
	}
	
	this.finishLine = function()
	{
	}
}

function point(x, y)
{
	this.x = x;
	this.y = y;
}
