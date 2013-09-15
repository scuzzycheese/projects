var STATE_NEW_LINE = "newLine";
var STATE_END_LINE = "endLine";
var STATE_DRAWING_LINE = "drawingLine"

function drawEngine(canvas)
{
	var that = {};

	var dCanvas = canvas;
	var dContext;
	var dLines = new Array();
	var dCurrentLine = {};

	var dScaleMatrix = {};
	var dTranslationMatrix = {};
	var dWorldMatrix = {};
	var dInvertedWorldMatrix = {};
	var dState = {};
	var dLastPoint = {};

	var dScale;
	var dComm;

	var dChatReceiver = null;

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

      reDraw();
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

	function getContext()
	{
		if(typeof(dContext) === "undefined")
		{
		/*
			if(!dCanvas.getContext)
			{
				alert('Error: no canvas.getContext!');
				return;
			}
		*/

			dContext = canvas.getContext('2d');
			if(!dContext)
			{
				alert('Error: failed to getContext!');
				return;
			}
		}
		return dContext;
	}

	function reDraw()
	{
		owner = "me";
		if(typeof(dWorldMatrix[owner]) === "undefined")
		{
			resetMatrices(owner);
		}
		var context = getContext();
		context.clearRect(0, 0, dCanvas.width, dCanvas.height);
		for(j = 0; j < dLines.length; j ++)
		{
		   var line = dLines[j];
			context.beginPath();
			var tempAlteredPoint = map(dWorldMatrix[owner], line.vectors[0]);
			context.moveTo(tempAlteredPoint.x, tempAlteredPoint.y);
			context.strokeStyle = line.lineBase.color;
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
		var context = getContext();
		dInvertedWorldMatrix[owner] = inverse(dWorldMatrix[owner]);

		var transedPoint = map(dInvertedWorldMatrix[owner], point);

		if(sendUpdate)
		{
			dLastPoint[owner] = point;
		}
		else
		{
			var newPoint = map(dWorldMatrix["me"], transedPoint);
			dLastPoint["me"] = newPoint;
		}

		dCurrentLine[owner] = new Line(transedPoint, currentPenColor, currentPenWidth);
		dLines.push(dCurrentLine[owner]);

		if(sendUpdate)
		{
			dComm.sendMsg(buildSendString(dWorldMatrix[owner]));
			dComm.sendMsg(buildSendString(new State(STATE_NEW_LINE, dCurrentLine[owner].lineBase)));
			dComm.sendMsg(buildSendString(point));
		}
		reDraw();
	}

	function addToLine(point, owner, sendUpdate)
	{
		if(typeof(dWorldMatrix[owner]) === "undefined")
		{
			resetMatrices(owner);
		}
		var context = getContext();
		var transedPoint = map(dInvertedWorldMatrix[owner], point);

		//TODO: maybe this shoulkd be if(owner !== "me") ?
		if(sendUpdate)
		{
			context.moveTo(dLastPoint[owner].x, dLastPoint[owner].y);
			context.strokeStyle = dCurrentLine[owner].lineBase.color;
			context.lineTo(point.x, point.y);
			dLastPoint[owner] = point;
		}
		else
		{
			context.moveTo(dLastPoint["me"].x, dLastPoint["me"].y);
			var newPoint = map(dWorldMatrix["me"], transedPoint);
			context.strokeStyle = dCurrentLine[owner].lineBase.color;
			context.lineTo(newPoint.x, newPoint.y);
			dLastPoint["me"] = newPoint;
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
			dComm.sendMsg(buildSendString(new State(STATE_END_LINE)));
		}
		reDraw();
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
				if(dState[from].state === STATE_END_LINE)
				{
					finishLine(from, false);
				}
			}
			if(obj.objType === "point")
			{
				if(dState[from].state === STATE_DRAWING_LINE)
				{
					addToLine(obj, from, false);
				}
				if(dState[from].state === STATE_NEW_LINE)
				{
					var lineBase = dState[from].payLoad;
					startNewLine(obj, lineBase.color, lineBase.width, from, false);
					dState[from].state = STATE_DRAWING_LINE;
				}
			}
			console.log("Object is of type: " + obj.objType);
		}
		else
		{
			if(dChatReceiver != null)
			{
				dChatReceiver(msg, from);
			}
		}
	}

	function registerChatMsgReceiver(receiver)
	{
		dChatReceiver = receiver;
	}

	function sendChatMsg(msg)
	{
		dComm.sendMsg(msg);
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
		that.sendChatMsg = sendChatMsg;
		that.registerChatMsgReceiver = registerChatMsgReceiver;

		return that;
	}

	return init();

}


function LineBase(color, width)
{
	this.objType = "linebase";
	this.color = color;
	this.width = width;
}

function Line(startPoint, color, width)
{
	this.lineBase = new LineBase(color, width);
	this.vectors = [startPoint];
	this.lineLimit = 
	{
		bottomRight: new Point
		(
			startPoint.x, 
			startPoint.y	
 		), 
		topLeft: new Point
		(
			startPoint.x, 
			startPoint.y
 		)
	};
	
	this.addToLimits = function(point)
	{
		if(point.x > this.lineLimit.bottomRight.x)
		{	
			this.lineLimit.bottomRight.x = point.x;
		}
		if(point.y > this.lineLimit.bottomRight.y)
		{
			this.lineLimit.bottomRight.y = point.y;
		}

		if(point.x < this.lineLimit.topLeft.x)
		{
			this.lineLimit.topLeft.x = point.x;
		}
		if(point.y < this.lineLimit.topLeft.y)
		{
			this.lineLimit.topLeft.y = point.y;
		}
	}

	this.addVectorToLine = function(point)
	{
		this.vectors.push(point);
		this.addToLimits(point);
	}
	
	this.finishLine = function()
	{
	}

	this.addToLimits(startPoint);

}

function Point(x, y)
{
	this.objType = "point";
	this.x = x;
	this.y = y;
}

function State(state, payLoad)
{
	this.objType = "state";
	this.state = state;
	this.payLoad = payLoad;
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
