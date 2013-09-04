function drawEngine(canvas)
{
	var that = {};

	var dCanvas = canvas;
	var dContext = {};
	var dLines = new Array();
	var dCurrentLine = {};
	var socket = null;

	var dScaleMatrix = {};
	var dTranslationMatrix = {};
	var dWorldMatrix = {};
	var dInvertedWorldMatrix = {};
	var dState = {};
	var dScale;
	var dComm;

	function resetMatrices(owner)
	{
		dScaleMatrix[owner] = new Matrix.I(3);
		dTranslationMatrix = new Matrix.I(3);
		dWorldMatrix[owner] = new Matrix.I(3);
		dInvertedWorldMatrix[owner] = new Matrix.I(3);
	}
	//This is a hack, need to do something here
	resetMatrices("me");

	function scale(scaleValue, aroundPoint, owner)
	{
      var tempPoint = map(inverse(dWorldMatrix[owner]), aroundPoint);

      dScale = 1 + (scaleValue / 10);
      dScaleMatrix[owner] = new Matrix.create([[dScale, 0, 0], [0, dScale, 0], [0, 0, 1]]);
      dWorldMatrix[owner] = dScaleMatrix[owner].x(dTranslationMatrix);

      var aroundPointAfter = map(dWorldMatrix[owner], tempPoint);

      translateMatrix(dTranslationMatrix, (new Point(aroundPoint.x - aroundPointAfter.x, aroundPoint.y - aroundPointAfter.y)));
      dWorldMatrix[owner] = dScaleMatrix[owner].x(dTranslationMatrix);

		dComm.sendMsg(buildSendString(dWorldMatrix[owner]));

      reDraw(owner);
	}

	function translate(transBy, owner)
	{
		translateMatrix(dTranslationMatrix, transBy);
		dWorldMatrix[owner] = dScaleMatrix[owner].x(dTranslationMatrix);

		dComm.sendMsg(buildSendString(dWorldMatrix[owner]));
		reDraw(owner);
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

	function getContext(owner)
	{
		if(!dContext[owner])
		{
		/*
			if(!dCanvas.getContext)
			{
				alert('Error: no canvas.getContext!');
				return;
			}
		*/

			dContext[owner] = canvas.getContext('2d');
			if(!dContext[owner])
			{
				alert('Error: failed to getContext!');
				return;
			}
		}
		return dContext[owner];
	}

	function reDraw(owner)
	{
		var context = getContext(owner);
		context.clearRect(0, 0, dCanvas.width, dCanvas.height);
		for(j = 0; j < dLines.length; j ++)
		{
		   var line = dLines[j];
			context.beginPath();
			var tempAlteredPoint = map(dWorldMatrix[owner], line.vectors[0]);
			context.moveTo(tempAlteredPoint.x, tempAlteredPoint.y);
			for(i = 1; i < line.vectors.length; i ++)
			{	
				var point = line.vectors[i];
				var alteredPoint = map(dWorldMatrix[owner], line.vectors[i])
				context.lineTo(alteredPoint.x, alteredPoint.y);
				context.stroke();
			}
		}
	}

	function startNewLine(point, currentPenColor, currentPenWidth, owner)
	{
		var context = getContext(owner);
		dInvertedWorldMatrix[owner] = inverse(dWorldMatrix[owner]);

		var transedPoint = map(dInvertedWorldMatrix[owner], point);

		context.beginPath();
		context.moveTo(point.x, point.y);
		dCurrentLine[owner] = new drawLine(transedPoint, currentPenColor, currentPenWidth);
		dLines.push(dCurrentLine[owner]);

		dComm.sendMsg(buildSendString(new State("scribbling")));
		dComm.sendMsg(buildSendString(transedPoint));
	}

	function addToLine(point, owner)
	{
		var context = getContext(owner);
		var transedPoint = map(dInvertedWorldMatrix[owner], point);
		context.lineTo(point.x, point.y);
		context.stroke();
		dCurrentLine[owner].addVectorToLine(transedPoint);

		dComm.sendMsg(buildSendString(transedPoint));
	}

	function finishLine(owner)
	{
		dCurrentLine[owner].finishLine();
		dComm.sendMsg(buildSendString(new State("finished_scribbling")));
	}

	function connect()
	{
		dComm = new commHandler("test");
		dComm.registerRecvFunc(recvFunc);
	}
	function recvFunc(msg, from)
	{
		if(msg.startsWith("{")) 
		{
			obj = JSON.parse(msg);
			if(obj.objType === "matrix")
			{
				dInvertedWorldMatrix[from] = obj;
			}
			if(obj.objType === "state")
			{
				dState[from] = obj;
			}
			

			console.log("Object is of type: " + obj.objType);
		}
		else
		{
			dComm.sendMsg(from + ": YO YO YO");
		}
	}

	function isConnected()
	{
		return dComm.connected;
	}


	function buildSendString(obj)
	{
		if(obj instanceof Matrix) 
		{
			obj.objType = "matrix";
		}
		return JSON.stringify(obj);
	}

	function init()
	{
		that.dCanvas = dCanvas;
		that.dLines = dLines;
		that.dScale = dScale;

		that.scale = scale;
		that.translate = translate;
		that.reDraw = reDraw;
		that.startNewLine = startNewLine;
		that.addToLine = addToLine;
		that.finishLine = finishLine;
		that.connect = connect;
		that.isConnected = isConnected;

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
	this.objType = "point";
	this.x = x;
	this.y = y;
}

function State(state)
{
	this.objType = "state";
	this.state = state;
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
	var connected = false;


	function connectToServer(host, port)
	{
		dSocket = new Websock();
		dSocket.on("message", getMessage);
		dSocket.on("open", sockOpened);
		dSocket.on("close", sockClosed);
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
				var from = msg.substring(1, msg.indexOf("!"));
				handleMsg(msgData.trim(), from);
			}
		}
	}

	function sockOpened()
	{
		dSocket.send_string("NICK shareboard\r\n");
		dSocket.send_string("USER shareboard 2 * : shareboard\r\n");
		dSocket.send_string("JOIN #" + dChannel + "\r\n");
		connected = true;
	}

	function sockClosed()
	{
		connected = false;
	}

	function handleMsg(msg, from)
	{
		console.log("Message Handler: " + msg);
		if(recvFunc !== null)
		{
			recvFunc(msg, from);
		}
	}

	function handlePing(msg)
	{
		console.log("PONG " + msg.substr(5));
		dSocket.send_string("PONG " + msg.substr(5) + "\r\n");
	}

	function sendMsg(msg)
	{
		if(connected)
		{
			dSocket.send_string("PRIVMSG #" + dChannel + " :" + msg + "\r\n");
		}
	}

	function registerRecvFunc(func)
	{
		recvFunc = func;
	}

	function init()
	{
		that.sendMsg = sendMsg;
		that.registerRecvFunc = registerRecvFunc;
		that.connected = connected;
		
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
