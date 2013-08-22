function drawEngine(canvas, context)
{
	this.dCanvas = canvas;
	this.dContext = context;
	this.dLines = new Array();
	this.dCurrentLine = null;
	this.dMatrixChanged = false;

	this.resetMatrices = function()
	{
		this.dScaleMatrix = new Matrix.I(3);
		this.dTranslationMatrix = new Matrix.I(3);
		this.dWorldMatrix = new Matrix.I(3);
		this.dInvertedWorldMatrix = new Matrix.I(3);

		this.dScale = 0;
	}
	this.resetMatrices();

	this.scale = function(scaleValue, aroundPoint)
	{
       var tempPoint = this.map(this.inverse(this.dWorldMatrix), aroundPoint);

       this.dScale = 1 + (scaleValue / 10);
       this.dScaleMatrix = new Matrix.create([[this.dScale, 0, 0], [0, this.dScale, 0], [0, 0, 1]]);
       this.dWorldMatrix = this.dScaleMatrix.x(this.dTranslationMatrix);

       var aroundPointAfter = this.map(this.dWorldMatrix, tempPoint);

       this.translateMatrix(this.dTranslationMatrix, (new Point(aroundPoint.x - aroundPointAfter.x, aroundPoint.y - aroundPointAfter.y)));
       this.dWorldMatrix = this.dScaleMatrix.x(this.dTranslationMatrix);

       this.dMatrixChanged = true;

       this.reDraw();
	}

	this.translate = function(transBy)
	{
		this.translateMatrix(this.dTranslationMatrix, transBy);
		this.dWorldMatrix = this.dScaleMatrix.x(this.dTranslationMatrix);

		this.dMatrixChanged = true;
		this.reDraw();
	}
	this.inverse = function(matrix)
	{
		var invertedMatrix = matrix.inverse();
		if(invertedMatrix === null)
		{
			invertedMatrix = new Matrix.create([[matrix.e(1, 1), matrix.e(1, 2), -matrix.e(1, 3)], [matrix.e(2, 1), matrix.e(2, 2), -matrix.e(2, 3)], [matrix.e(3, 1), matrix.e(3, 2), matrix.e(3, 3)]]);
		}
		return invertedMatrix;
	}

	this.map = function(matrix, inPoint)
	{
		var xPrime = matrix.e(1, 1) * inPoint.x + matrix.e(2, 1) * inPoint.y + matrix.e(3, 1);
		var yPrime = matrix.e(2, 2) * inPoint.y + matrix.e(1, 2) * inPoint.x + matrix.e(3, 2);
		return new Point(xPrime, yPrime);
	}

	this.translateMatrix = function(matrix, transBy)
	{
	   var elements = matrix.elements;
		elements[2][0] += transBy.x;
		elements[2][1] += transBy.y;
		matrix.setElements(elements);
	}

/*
				   x' = m11*x + m21*y + dx
					y' = m22*y + m12*x + dy
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

	this.reDraw = function()
	{
		var context = this.dContext;
		this.dContext.clearRect(0, 0, this.dCanvas.width, this.dCanvas.height);
		//this.dLines.forEach(function(line, index, array)
		for(j = 0; j < this.dLines.length; j ++)
		{
		   var line = this.dLines[j];
			context.beginPath();
			var tempAlteredPoint = this.map(this.dWorldMatrix, line.vectors[0]);
			context.moveTo(tempAlteredPoint.x, tempAlteredPoint.y);
			for(i = 1; i < line.vectors.length; i ++)
			{	
				var point = line.vectors[i];
				var alteredPoint = this.map(this.dWorldMatrix, line.vectors[i])
				//context.lineTo(point.x, point.y);
				context.lineTo(alteredPoint.x, alteredPoint.y);
				context.stroke();
			}
		}
		//});
	}

	this.startNewLine = function(point, currentPenColor, currentPenWidth)
	{
		this.dInvertedWorldMatrix = this.inverse(this.dWorldMatrix);

		var transedPoint = this.map(this.dInvertedWorldMatrix, point);

		this.dContext.beginPath();
		this.dContext.moveTo(point.x, point.y);
		this.dCurrentLine = new drawLine(transedPoint, currentPenColor, currentPenWidth);
		this.dLines.push(this.dCurrentLine);
	}

	this.addToLine = function(point)
	{
		var transedPoint = this.map(this.dInvertedWorldMatrix, point);
		this.dContext.lineTo(point.x, point.y);
		this.dContext.stroke();
		this.dCurrentLine.addVectorToLine(transedPoint);
	}

	this.finishLine = function()
	{
		this.dCurrentLine.finishLine();
	}

	this.connectToServer = function(host, port)
	{
		var socket = new WebSocket("ws://localhost:8000");  
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

function Point(x, y)
{
	this.x = x;
	this.y = y;
}
