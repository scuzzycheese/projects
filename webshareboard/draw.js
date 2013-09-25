var drawer = new draw();

if(window.addEventListener)
{
	window.addEventListener('load', drawer, false);
}
	

function draw()	
{
	var canvas;
	var eHandlers;
	
	var engine;
	var scale = 20;
	var dVT100;

	var that = {};


	function init ()
	{
		canvas = document.getElementById('drawCanvas');
		if(!canvas)
		{
			alert('Error: I cannot find the canvas element!');
			return;
		}


		engine = new drawEngine(canvas);

 		dVT100 = new VT100(80, 24, "chatWindow");
		$("#chatInputText").keyup(handleInputBoxMessages);
		$("#sendButton").click(handleSendButton);

		engine.registerChatMsgReceiver(handleIncomingChatMessage);
		engine.connect();


		//while(!engine.isConnected());

		engine.scale(scale * scale, new Point(canvas.width/2, canvas.height/2), "me", true);
		engine.reDraw("me");

		eHandlers = new eventHandlers(engine, scale);

		canvas.addEventListener('mousedown', ev_canvas, false);
		canvas.addEventListener('mousemove', ev_canvas, false);
		canvas.addEventListener('mouseup',   ev_canvas, false);
		canvas.addEventListener('mouseout',   ev_canvas, false);
		canvas.addEventListener('DOMMouseScroll',   ev_canvas, false);
		canvas.addEventListener('mousewheel',   ev_canvas, false);
		canvas.addEventListener('contextmenu',   ev_canvas, false);

		that.engine = engine;

		return that;
	}

	function ev_canvas(ev)
	{
		if(ev.layerX || ev.layerX == 0) // Firefox
		{
			ev._x = ev.layerX;
			ev._y = ev.layerY;
		}
		else if(ev.offsetX || ev.offsetX == 0) // Opera
		{
			ev._x = ev.offsetX;
			ev._y = ev.offsetY;
		}
		ev.wheel = (ev.wheelDelta) ? ev.wheelDelta / 120 : -(ev.detail || 0) / 3;

		if(typeof eHandlers[ev.type] === 'function') 
		{
			eHandlers[ev.type](ev);
		}
	}

	function handleIncomingChatMessage(msg, from)
	{
		dVT100.write(from + ": " + msg + "\r\n");
	}

	function handleInputBoxMessages(event)
	{
		if(event.keyCode == 13)
		{
			handleSendButton();
		}
	}

	function handleSendButton()
	{
		var inputBoxValue = $("#chatInputText").val();
		$("#chatInputText").val("");
		dVT100.write("Me: " + inputBoxValue + "\r\n");
		engine.sendChatMsg(inputBoxValue + "\r\n");
	}
	return init();
}



function eventHandlers(eng, startScale)
{
	var that = {};

	var scribbling = false;
	var moving = false;
	var lastPos = new Point(0, 0);
	var engine = eng;
	var scale = startScale;
	var penColor = "#000000";

	function mousedown(ev)
	{
		//ev.target.style.cursor = 'crosshair';
		switch(ev.which)
		{
			case 1:
			{
				engine.startNewLine(new Point(ev._x, ev._y), penColor, 0.05, "me", true);
				scribbling = true;
				break;
			}
			case 3:
			{
				contextmenu(ev);
				break;
			}
		}
		ev.stopPropagation();
		ev.preventDefault();
	}

	function contextmenu(ev)
	{
		lastPos = new Point(ev._x, ev._y);
		moving = true;
		ev.stopPropagation();
		ev.preventDefault();
	}

	function mousemove(ev)
	{
		if(scribbling)
		{
			engine.addToLine(new Point(ev._x, ev._y), "me", true);
		}
		if(moving)
		{
			var tempPoint = new Point(-(lastPos.x - ev._x), -(lastPos.y - ev._y));
			engine.translate(tempPoint, "me", true);
			lastPos = new Point(ev._x, ev._y);
		}
	}

	function mouseup(ev)
	{
		if(scribbling)
		{
			scribbling = false;
			engine.finishLine("me", true);
			engine.reDraw("me");
		}
		if(moving)
		{
			moving = false;
			engine.reDraw("me");
		}
	}

	function mouseout(ev)
	{
		if(scribbling)
		{
			scribbling = false;
			engine.finishLine("me", true);
		}
	}

	function DOMMouseScroll(ev)
	{
		//Maybe I have to stop propogation of this event
		if(ev.wheel > 0)
		{
			scale ++;
			engine.scale(scale * scale, new Point(ev._x, ev._y), "me", true);
		}
		if(ev.wheel < 0)
		{
			if(scale > 0)
			{
				scale --;
				engine.scale(scale * scale, new Point(ev._x, ev._y), "me", true);
			}
		}
	}

	function init()
	{
		that.scribbling = scribbling;
		that.moving = moving;
		that.lastPos = lastPos;
		that.engine = engine;
		that.scale = scale;

		that.mousedown = mousedown;
		that.contextmenu = contextmenu;
		that.mousemove = mousemove;
		that.mouseup = mouseup;
		that.mouseout = mouseout;
		that.DOMMouseScroll = DOMMouseScroll;
		that.mousewheel = DOMMouseScroll;

		setupColourHandlers();

		return that;
	}

	function setupColourHandlers()
	{
		$("#penColor").change(function(event)
		{
			penColor = $("#penColor").val();
		});

		$("#colorButtonRed").click(function(event)
		{
			penColor = "#FF0000";
		});
		$("#colorButtonGreen").click(function(event)
		{
			penColor = "#00FF00";
		});
		$("#colorButtonBlue").click(function(event)
		{
			penColor = "#0000FF";
		});
		$("#colorButtonYellow").click(function(event)
		{
			penColor = "#FFFF00";
		});
		$("#colorButtonOrange").click(function(event)
		{
			penColor = "#FFA500";
		});
		$("#colorButtonBlack").click(function(event)
		{
			penColor = "#000000";
		});
	}

	return init();
}

