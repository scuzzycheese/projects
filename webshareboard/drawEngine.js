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
		dTranslationMatrix[owner] = new Matrix.I(3);
		dWorldMatrix[owner] = new Matrix.I(3);
		dInvertedWorldMatrix[owner] = new Matrix.I(3);
	}
	//This is a hack, need to do something here
	resetMatrices("me");

	function scale(scaleValue, aroundPoint, owner, sendUpdate)
	{
		if(typeof(dWorldMatrix[owner]) === "undefined")
		{
			resetMatrices(owner);
		}
      var tempPoint = map(inverse(dWorldMatrix[owner]), aroundPoint);

      dScale = 1 + (scaleValue / 10);
      dScaleMatrix[owner] = new Matrix.create([[dScale, 0, 0], [0, dScale, 0], [0, 0, 1]]);
      dWorldMatrix[owner] = dScaleMatrix[owner].x(dTranslationMatrix[owner]);

      var aroundPointAfter = map(dWorldMatrix[owner], tempPoint);

      translateMatrix(dTranslationMatrix[owner], (new Point(aroundPoint.x - aroundPointAfter.x, aroundPoint.y - aroundPointAfter.y)));
      dWorldMatrix[owner] = dScaleMatrix[owner].x(dTranslationMatrix[owner]);

		if(sendUpdate)
		{
			dComm.sendMsg(buildSendString(dWorldMatrix[owner]));
		}

      reDraw(owner);
	}

	function translate(transBy, owner, sendUpdate)
	{
		if(typeof(dWorldMatrix[owner]) === "undefined")
		{
			resetMatrices(owner);
		}
		translateMatrix(dTranslationMatrix[owner], transBy);
		dWorldMatrix[owner] = dScaleMatrix[owner].x(dTranslationMatrix[owner]);

		if(sendUpdate)
		{
			dComm.sendMsg(buildSendString(dWorldMatrix[owner]));
		}
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
		if(typeof(dContext[owner]) === "undefined")
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
		if(typeof(dWorldMatrix[owner]) === "undefined")
		{
			resetMatrices(owner);
		}
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
				var alteredPoint = map(dWorldMatrix[owner], line.vectors[i])
				context.lineTo(alteredPoint.x, alteredPoint.y);
				context.stroke();
			}
		}
	}

	function startNewLine(point, currentPenColor, currentPenWidth, owner, sendUpdate)
	{
		if(typeof(dWorldMatrix[owner]) === "undefined")
		{
			resetMatrices(owner);
		}
		var context = getContext(owner);
		dInvertedWorldMatrix[owner] = inverse(dWorldMatrix[owner]);

		var transedPoint = map(dInvertedWorldMatrix[owner], point);

		if(sendUpdate)
		{
			context.moveTo(point.x, point.y);
		}
		else
		{
			var newPoint = map(dWorldMatrix["me"], transedPoint);
			context.moveTo(newPoint.x, newPoint.y);
		}

		dCurrentLine[owner] = new drawLine(transedPoint, currentPenColor, currentPenWidth);
		dLines.push(dCurrentLine[owner]);

		if(sendUpdate)
		{
			dComm.sendMsg(buildSendString(dWorldMatrix[owner]));
			dComm.sendMsg(buildSendString(new State("start_scribbling")));
			dComm.sendMsg(buildSendString(point));
		}
	}

	function addToLine(point, owner, sendUpdate)
	{
		if(typeof(dWorldMatrix[owner]) === "undefined")
		{
			resetMatrices(owner);
		}
		var context = getContext(owner);
		var transedPoint = map(dInvertedWorldMatrix[owner], point);

		if(sendUpdate)
		{
			context.lineTo(point.x, point.y);
		}
		else
		{
			var newPoint = map(dWorldMatrix["me"], transedPoint);
			context.lineTo(newPoint.x, newPoint.y);
		}
		context.stroke();

		dCurrentLine[owner].addVectorToLine(transedPoint);

		if(sendUpdate)
		{
			dComm.sendMsg(buildSendString(point));
		}
	}

	function finishLine(owner, sendUpdate)
	{
		if(typeof(dWorldMatrix[owner]) === "undefined")
		{
			resetMatrices(owner);
		}
		dCurrentLine[owner].finishLine();
		if(sendUpdate)
		{
			dComm.sendMsg(buildSendString(new State("finished_scribbling")));
		}
	}

	function connect()
	{
		var gParams = getParams();
		var name = "temp";
		if(typeof(gParams["name"]) !== "undefined")
		{
			name = gParams["name"];
		}
		dComm = new commHandler(name, "test");
		dComm.registerRecvFunc(recvFunc);
	}
	function recvFunc(msg, from)
	{
		if(msg.startsWith("{")) 
		{
			obj = JSON.parse(msg);
			if(obj.objType === "matrix")
			{
				dWorldMatrix[from] = new Matrix.create(obj.elements);
			}
			if(obj.objType === "state")
			{
				dState[from] = obj;
				if(dState[from].state === "finished_scribbling")
				{
					finishLine(from, false);
				}
			}
			if(obj.objType === "point")
			{
				if(dState[from].state === "start_scribbling")
				{
					startNewLine(obj, null, null, from, false);
					dState[from].state = "scribbling";
				}
				if(dState[from].state === "scribbling")
				{
					addToLine(obj, from, false);
				}
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


function commHandler(name, channel)
{
	var that = {};

	var dNick = name;
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
			var messages = msg.split("\r\n");
			for(var i = 0; i < messages.length; i ++)
			{
				var message = messages[i];
				var msgIndicatorIndex = message.indexOf("PRIVMSG #") + 9;
				var channel = message.substring(msgIndicatorIndex, message.indexOf(" :", msgIndicatorIndex));
				console.log("Channel: " + channel);
				if(channel === dChannel)
				{
					var msgData = message.substring(message.indexOf(" :", msgIndicatorIndex) + 2);
					var from = message.substring(1, message.indexOf("!"));
					handleMsg(msgData.trim(), from);
				}
			}
		}
	}

	function sockOpened()
	{
		dSocket.send_string("NICK " + dNick + "\r\n");
		dSocket.send_string("USER " + dNick + " 2 * : " + dNick + "\r\n");
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

function getParams()
{
	var prmstr = window.location.search.substr(1);
	var prmarr = prmstr.split ("&");
	var params = {};

	for(var i = 0; i < prmarr.length; i++)
	{
		var tmparr = prmarr[i].split("=");
		params[tmparr[0]] = tmparr[1];
	}
	return params;
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
