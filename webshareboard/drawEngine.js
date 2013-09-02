function drawEngine(canvas, context)
{
	var that = {};

	var dCanvas = canvas;
	var dContext = context;
	var dLines = new Array();
	var dCurrentLine = null;
	var dMatrixChanged = false;
	var socket = null;

	var dScaleMatrix;
	var dTranslationMatrix;
	var dWorldMatrix;
	var dInvertedWorldMatrix;
	var dScale;
	var dComm;

	function resetMatrices()
	{
		dScaleMatrix = new Matrix.I(3);
		dTranslationMatrix = new Matrix.I(3);
		dWorldMatrix = new Matrix.I(3);
		dInvertedWorldMatrix = new Matrix.I(3);
	}
	resetMatrices();

	function scale(scaleValue, aroundPoint)
	{
       var tempPoint = map(inverse(dWorldMatrix), aroundPoint);

       dScale = 1 + (scaleValue / 10);
       dScaleMatrix = new Matrix.create([[dScale, 0, 0], [0, dScale, 0], [0, 0, 1]]);
       dWorldMatrix = dScaleMatrix.x(dTranslationMatrix);

       var aroundPointAfter = map(dWorldMatrix, tempPoint);

       translateMatrix(dTranslationMatrix, (new Point(aroundPoint.x - aroundPointAfter.x, aroundPoint.y - aroundPointAfter.y)));
       dWorldMatrix = dScaleMatrix.x(dTranslationMatrix);

       dMatrixChanged = true;

       reDraw();
	}

	function translate(transBy)
	{
		translateMatrix(dTranslationMatrix, transBy);
		dWorldMatrix = dScaleMatrix.x(dTranslationMatrix);

		dMatrixChanged = true;
		dComm.sendMsg(JSON.stringify(dWorldMatrix));
		reDraw();
	}
	function inverse(matrix)
	{
		var invertedMatrix = matrix.inverse();
		if(invertedMatrix === null)
		{
			invertedMatrix = new Matrix.create([[matrix.e(1, 1), matrix.e(1, 2), -matrix.e(1, 3)], [matrix.e(2, 1), matrix.e(2, 2), -matrix.e(2, 3)], [matrix.e(3, 1), matrix.e(3, 2), matrix.e(3, 3)]]);
		}
		return invertedMatrix;
	}

	function map(matrix, inPoint)
	{
		var xPrime = matrix.e(1, 1) * inPoint.x + matrix.e(2, 1) * inPoint.y + matrix.e(3, 1);
		var yPrime = matrix.e(2, 2) * inPoint.y + matrix.e(1, 2) * inPoint.x + matrix.e(3, 2);
		return new Point(xPrime, yPrime);
	}

	function translateMatrix(matrix, transBy)
	{
	   var elements = matrix.elements;
		elements[2][0] += transBy.x;
		elements[2][1] += transBy.y;
		matrix.setElements(elements);
	}


	function reDraw()
	{
		var context = dContext;
		dContext.clearRect(0, 0, dCanvas.width, dCanvas.height);
		for(j = 0; j < dLines.length; j ++)
		{
		   var line = dLines[j];
			context.beginPath();
			var tempAlteredPoint = map(dWorldMatrix, line.vectors[0]);
			context.moveTo(tempAlteredPoint.x, tempAlteredPoint.y);
			for(i = 1; i < line.vectors.length; i ++)
			{	
				var point = line.vectors[i];
				var alteredPoint = map(dWorldMatrix, line.vectors[i])
				context.lineTo(alteredPoint.x, alteredPoint.y);
				context.stroke();
			}
		}
	}

	function startNewLine(point, currentPenColor, currentPenWidth)
	{
		dInvertedWorldMatrix = inverse(dWorldMatrix);

		var transedPoint = map(dInvertedWorldMatrix, point);

		dContext.beginPath();
		dContext.moveTo(point.x, point.y);
		dCurrentLine = new drawLine(transedPoint, currentPenColor, currentPenWidth);
		dLines.push(dCurrentLine);
	}

	function addToLine(point)
	{
		var transedPoint = map(dInvertedWorldMatrix, point);
		dContext.lineTo(point.x, point.y);
		dContext.stroke();
		dCurrentLine.addVectorToLine(transedPoint);
	}

	function finishLine()
	{
		dCurrentLine.finishLine();
	}

	function connect()
	{
		dComm = new commHandler("test");
		dComm.registerRecvFunc(recvFunc);
	}
	function recvFunc(msg)
	{
		dComm.sendMsg("YO YO YO");
	}

	function init()
	{
		that.dCanvas = dCanvas;
		that.dContext = dContext;
		that.dLines = dLines;
		that.dCurrentLine = dCurrentLine;
		that.dMatrixChanged = dMatrixChanged;
		that.dScaleMatrix = dScaleMatrix;
		that.dTranslationMatrix = dTranslationMatrix;
		that.dWorldMatrix = dWorldMatrix;
		that.dInvertedWorldMatrix = dInvertedWorldMatrix;
		that.dScale = dScale;

		that.scale = scale;
		that.translate = translate;
		that.reDraw = reDraw;
		that.startNewLine = startNewLine;
		that.addToLine = addToLine;
		that.finishLine = finishLine;
		that.connect = connect;

		return that;
	}

	return init();

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


function commHandler(channel)
{
	var that = {};

	var dNick = "shareboard";
	var dHost = "localhost";
	var dPort = 8000;
	var dSocket = null;
	var recvFunc = null;
	var dChannel = channel;


	function connectToServer(host, port)
	{
		dSocket = new Websock();
		dSocket.on("message", getMessage);
		dSocket.on("open", sockOpened);
		dSocket.open("ws://" + host + ":" + port);  
	}

	function getMessage()
	{
		var msg = dSocket.rQshiftStr(dSocket.rQlen());
		console.log(msg);

		if(msg.startsWith("PING"))
		{
			handlePing(msg);
			return;
		}
		
		if(msg.indexOf("PRIVMSG #") != -1)
		{
			var msgIndicatorIndex = msg.indexOf("PRIVMSG #") + 9;
			var channel = msg.substring(msgIndicatorIndex, msg.indexOf(" :", msgIndicatorIndex));
			console.log("Channel: " + channel);
			if(channel === dChannel)
			{
				var msgData = msg.substring(msg.indexOf(" :", msgIndicatorIndex) + 2);
				handleMsg(msgData.trim());
			}
		}
	}

	function sockOpened()
	{
		dSocket.send_string("NICK shareboard\r\n");
		dSocket.send_string("USER shareboard 2 * : shareboard\r\n");
		dSocket.send_string("JOIN #" + dChannel + "\r\n");
	}

	function handleMsg(msg)
	{
		console.log("Message Handler: " + msg);
		if(recvFunc !== null)
		{
			recvFunc(msg);
		}
	}

	function handlePing(msg)
	{
		console.log("PONG " + msg.substr(5));
		dSocket.send_string("PONG " + msg.substr(5) + "\r\n");
	}

	function sendMsg(msg)
	{
		dSocket.send_string("PRIVMSG #" + dChannel + " :" + msg + "\r\n");
	}

	function registerRecvFunc(func)
	{
		recvFunc = func;
	}

	function init()
	{
		that.sendMsg = sendMsg;
		that.registerRecvFunc = registerRecvFunc;
		
		connectToServer(dHost, dPort);

		return that;
	}

	return init();

}

if (!String.prototype.startsWith) {
  Object.defineProperty(String.prototype, 'startsWith', {
    enumerable: false,
    configurable: false,
    writable: false,
    value: function (searchString, position) {
      position = position || 0;
      return this.indexOf(searchString, position) === position;
    }
  });
}
