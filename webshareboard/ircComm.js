function commHandler(name, channel)
{
	var that = {};

	var dNick = name;
	//var dHost = "192.168.0.60";
	var dHost = "daine.aka.amazon.com";
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
