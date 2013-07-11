function drawEngine(canvas, context)
{
	this.canvas = canvas;
	this.context = context;
	this.lines = new Array();
	this.currentLine = null;


	this.startNewLine = function(point, currentPenColor, currentPenWidth)
	{
		context.beginPath();
		context.moveTo(point.x, point.y);
		this.currentLine = new drawLine(point, currentPenColor, currentPenWidth);
		this.lines.push(this.currentLine);
	}


	this.addToLine = function(point)
	{
		context.lineTo(point.x, point.y);
		context.stroke();
		this.currentLine.addVectorToLine(point);
	}

	this.finishLine = function()
	{
		this.currentLine.finishLine();
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
