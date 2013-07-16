if(window.addEventListener)
{
	window.addEventListener('load', function()
	{
		var canvas;
		var context;
		var eHandlers;
		

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
	
			eHandlers = new eventHandlers();

			canvas.addEventListener('mousedown', ev_canvas, false);
			canvas.addEventListener('mousemove', ev_canvas, false);
			canvas.addEventListener('mouseup',   ev_canvas, false);
			canvas.addEventListener('mouseout',   ev_canvas, false);
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

			if(typeof eHandlers[ev.type] === 'function') 
			{
				eHandlers[ev.type](ev);
			}
		}

		function eventHandlers()
		{
			this.scribbling = false;
			this.engine = new drawEngine(canvas, context);

			this.mousedown = function(ev)
			{
				this.engine.startNewLine(new point(ev._x, ev._y), null, null);
				this.scribbling = true;
			};

			this.mousemove = function(ev)
			{
				if(this.scribbling)
				{
					this.engine.addToLine(new point(ev._x, ev._y));
				}
			};

			this.mouseup = function(ev)
			{
				if(this.scribbling)
				{
					this.scribbling = false;
					this.engine.finishLine();
				}
			};

			this.mouseout = function(ev)
			{
				if(this.scribbling)
				{
					this.scribbling = false;
					this.engine.finishLine();
				}
			};
		}


		init();
	}, false);
}
