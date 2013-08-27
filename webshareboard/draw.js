if(window.addEventListener)
{
	window.addEventListener('load', new draw(), false);
}
	

function draw()	
{
	var canvas;
	var context;
	var eHandlers;
	
	var engine;
	var scale = 20;


	function init ()
	{
		canvas = document.getElementById('drawCanvas');
		if(!canvas)
		{
			alert('Error: I cannot find the canvas element!');
			return;
		}

		if(!canvas.getContext)
		{
			alert('Error: no canvas.getContext!');
			return;
		}

		context = canvas.getContext('2d');
		if(!context)
		{
			alert('Error: failed to getContext!');
			return;
		}

		engine = new drawEngine(canvas, context);
		engine.connectToServer("localhost", "6665");
		engine.scale(scale * scale, new Point(canvas.width/2, canvas.height/2));
		engine.reDraw();

		eHandlers = new eventHandlers(engine, scale);

		canvas.addEventListener('mousedown', ev_canvas, false);
		canvas.addEventListener('mousemove', ev_canvas, false);
		canvas.addEventListener('mouseup',   ev_canvas, false);
		canvas.addEventListener('mouseout',   ev_canvas, false);
		canvas.addEventListener('DOMMouseScroll',   ev_canvas, false);
		canvas.addEventListener('mousewheel',   ev_canvas, false);
		canvas.addEventListener('contextmenu',   ev_canvas, false);
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

	init();
}



function eventHandlers(eng, startScale)
{
	var that = {};

	var scribbling = false;
	var moving = false;
	var lastPos = new Point(0, 0);
	var engine = eng;
	var scale = startScale;

	function mousedown(ev)
	{
		switch(ev.which)
		{
			case 1:
			{
				engine.startNewLine(new Point(ev._x, ev._y), null, null);
				scribbling = true;
				break;
			}
			case 3:
			{
				contextmenu(ev);
				break;
			}
		}
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
			engine.addToLine(new Point(ev._x, ev._y));
		}
		if(moving)
		{
			var tempPoint = new Point(-(lastPos.x - ev._x), -(lastPos.y - ev._y));
			engine.translate(tempPoint);
			lastPos = new Point(ev._x, ev._y);
		}
	}

	function mouseup(ev)
	{
		if(scribbling)
		{
			scribbling = false;
			engine.finishLine();
			engine.reDraw();
		}
		if(moving)
		{
			moving = false;
			engine.reDraw();
		}
	}

	function mouseout(ev)
	{
		if(scribbling)
		{
			scribbling = false;
			engine.finishLine();
		}
	}

	function DOMMouseScroll(ev)
	{
		//Maybe I have to stop propogation of this event
		if(ev.wheel > 0)
		{
			scale ++;
			engine.scale(scale * scale, new Point(ev._x, ev._y));
		}
		if(ev.wheel < 0)
		{
			if(scale > 0)
			{
				scale --;
				engine.scale(scale * scale, new Point(ev._x, ev._y));
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

		return that;
	}

	return init();
}

