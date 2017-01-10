// Load .env config (silently fail if no .env present)
require('dotenv').config({ silent: true });

// Require necessary libraries
var async = require('async');
var ioLib = require('socket.io');
var http = require('http');
var path = require('path');
var express = require('express');
var MbedConnectorApi = require('mbed-connector-api');

// CONFIG (change these)

//V5nz2XpPdiZlmmqh3KtXIlwjS8dmQG67NXgLZFpdVyA2DqqPDyaED1mf3dtJz2vOypkBxbIV8AhpFgNUGCNETXnEt7DXkSd80GUv
var accessKey = process.env.ACCESS_KEY || "39WxX2aOAIHdZKUVNwSXYXQ91SyC3tA0AKB03m6m8w2RUVBuMEG3WQ68oZBdJ0k13GlRx76L1d78b2JidJ6rbFdlJzds64mXBkL8";
var port = process.env.PORT || 8080;

// Paths to resources on the endpoints
var Temperature = '/Monitor/0/D';
var PressureHp = '/Monitor/0/Hp';
var Humidity = '/Monitor/0/Hum';
var GPIO = '/GPIO/0/STATE'
var Zigbee = '/GPIO/1/Zigbee'

// Instantiate an mbed Device Connector object
var mbedConnectorApi = new MbedConnectorApi({
  accessKey: accessKey
});

// Create the express app
var app = express();
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'hbs');
app.use(express.static(path.join(__dirname, 'public')));

app.get('/', function (req, res) {
  // Get all of the endpoints and necessary info to render the page
  mbedConnectorApi.getEndpoints(function(error, endpoints) {
    if (error) {
      throw error;
    } else {
      // Setup the function array
      var functionArray = endpoints.map(function(endpoint) {
        return function(mapCallback) {
			 console.log("endpoints name>"+endpoint.name);
			  console.log("endpoints type>"+endpoint.type);
           mbedConnectorApi.getResourceValue(endpoint.name, GPIO, function(error, value) {
           // endpoint.blinkPattern = value;  //never use
		   console.log("debug:>"+value);
            mapCallback(error);
         });
        };
      });

      // Fetch all blink patterns in parallel, finish when all HTTP
      // requests are complete (uses Async.js library)
      async.parallel(functionArray, function(error) {
        if (error) {
          res.send(String(error));
        } else {
			res.render('index', {
            endpoints: endpoints
          });
        }
      });
    }
  });
});

// Handle unexpected server errors
app.use(function(err, req, res, next) {
  console.log(err.stack);
  res.status(err.status || 500);
  res.render('error', {
    message: err.message,
    error: err
  });
});

var sockets = [];
var server = http.Server(app);
var io = ioLib(server);

// Setup sockets for updating web UI
io.on('connection', function (socket) {
  // Add new client to array of client upon connection
  sockets.push(socket);

  socket.on('subscribe-to-Humidity', function (data) {
    // Subscribe to all changes of resource /3200/0/5501 (button presses)
    mbedConnectorApi.putResourceSubscription(data.endpointName, Humidity, function(error) {
      if (error) throw error;
      socket.emit('subscribed-to-Humidity', {
        endpointName: data.endpointName
      });
    });
  });
  
    socket.on('subscribe-to-Pressure', function (data) {
    // Subscribe to all changes of resource /3200/0/5501 (button presses)
    mbedConnectorApi.putResourceSubscription(data.endpointName, PressureHp, function(error) {
      if (error) throw error;
      socket.emit('subscribed-to-Pressure', {
        endpointName: data.endpointName
      });
    });
  });
  
    socket.on('subscribe-to-tmp', function (data) {
		 console.log("subscribe-to-tmp");
    // Subscribe to all changes of resource /3200/0/5501 (button presses)
    mbedConnectorApi.putResourceSubscription(data.endpointName, Temperature, function(error) {
		console.log("putResourceSubscription sub tmp in app.js");
      if (error) throw error;
      socket.emit('subscribed-to-tmp', {
        endpointName: data.endpointName
      });
    });
  });
  
    socket.on('subscribe-gpio-state', function (data) {
		
	    console.log("subscribe-gpio-state");
    // Subscribe to all changes of resource /3200/0/5501 (button presses)
    mbedConnectorApi.putResourceSubscription(data.endpointName, GPIO, function(error) {
		console.log("putResourceSubscription sub gpio in app.js");
      if (error) throw error;
      socket.emit('subscribed-gpio-state', {
        endpointName: data.endpointName
      });
    });
  });

  socket.on('unsubscribe-to-hum', function(data) {
    // Unsubscribe from the resource /3200/0/5501 (button presses)
    mbedConnectorApi.deleteResourceSubscription(data.endpointName, Humidity, function(error) {
      if (error) throw error;
      socket.emit('unsubscribed-to-hum', {
        endpointName: data.endpointName
      });
    });
  });

    socket.on('unsubscribe-to-pres', function(data) {
    // Unsubscribe from the resource /3200/0/5501 (button presses)
    mbedConnectorApi.deleteResourceSubscription(data.endpointName, PressureHp, function(error) {
      if (error) throw error;
      socket.emit('unsubscribed-to-pres', {
        endpointName: data.endpointName
      });
    });
  });
  
    socket.on('unsubscribe-to-tmp', function(data) {
    // Unsubscribe from the resource /3200/0/5501 (button presses)
    mbedConnectorApi.deleteResourceSubscription(data.endpointName, Temperature, function(error) {
      if (error) throw error;
      socket.emit('unsubscribed-to-tmp', {
        endpointName: data.endpointName
      });
    });
  });

   socket.on('unsubscribe-gpio-state', function(data) {
    // Unsubscribe from the resource /3200/0/5501 (button presses)
    mbedConnectorApi.deleteResourceSubscription(data.endpointName, GPIO, function(error) {
      if (error) throw error;
      socket.emit('unsubscribed-gpio-state', {
        endpointName: data.endpointName
      });
    });
  });    
  
  
  socket.on('get-humidity', function(data) {
    // Read data from GET resource /3200/0/5501 (num button presses)
    mbedConnectorApi.getResourceValue(data.endpointName, Humidity, function(error, value) {
      if (error) throw error;
      socket.emit('Hum', {
        endpointName: data.endpointName,
        value: value
      });
    });
  });
  
    socket.on('get-pressure', function(data) {
    // Read data from GET resource /3200/0/5501 (num button presses)
    mbedConnectorApi.getResourceValue(data.endpointName, PressureHp , function(error, value) {
		  
      if (error) throw error;
      socket.emit('Pressure', {
        endpointName: data.endpointName,
        value: value
      });
    });
  });
  
    socket.on('get-tmp', function(data) {
    // Read data from GET resource /3200/0/5501 (num button presses)
	 console.log("get-temp in app.js");
    mbedConnectorApi.getResourceValue(data.endpointName, Temperature, function(error, value) {
		
		 console.log("getResourceValue : Temperature called");
      if (error) throw error;
      socket.emit('Temp', {
        endpointName: data.endpointName,
        value: value
      });
    });
  });
  
    
   socket.on('get-gpio-state', function(data) {
	   console.log("get-gpio in app.js");
    // Read data from GET resource /3200/0/5501 (num button presses)
   mbedConnectorApi.getResourceValue(data.endpointName, GPIO , function(error, value) {
      if (error) throw error;
	   console.log("getResourceValue:get-gpio in app.js");
      socket.emit('GPIO-STATE', {
        endpointName: data.endpointName,
        value: value
      });
    });
  });
/*
  socket.on('update-blink-pattern', function(data) {
    // Set data on PUT resource /3201/0/5853 (pattern of LED blink)
    mbedConnectorApi.putResourceValue(data.endpointName, PressureHp, data.blinkPattern, function(error) {
      if (error) throw error;
    });
  });  
*/
  socket.on('post-gpio-state', function(data) {
    // POST to resource /3201/0/5850 (start blinking LED)
    mbedConnectorApi.postResource(data.endpointName, GPIO,data.myvalue, function(error) {
      if (error) throw error;
    });
  });
  
  
  socket.on('post-zigbee', function(data) {
    // POST to resource /3201/0/5850 (start blinking LED)
    mbedConnectorApi.postResource(data.endpointName, Zigbee,data.myvalue, function(error) {
      if (error) throw error;
    });
  });

  socket.on('disconnect', function() {
    // Remove this socket from the array when a user closes their browser
    var index = sockets.indexOf(socket);
    if (index >= 0) {
      sockets.splice(index, 1);
    }
  })
});

// When notifications are received through the notification channel, pass the
// button presses data to all connected browser windows
mbedConnectorApi.on('notification', function(notification) {
	
	console.log("notification.path:"+notification.path);
	
  if (notification.path === Humidity) {
    sockets.forEach(function(socket) {
      socket.emit('Hum', {
        endpointName: notification.ep,
        value: notification.payload
      });
    });
  }
  
  if (notification.path === PressureHp) {
    sockets.forEach(function(socket) {
      socket.emit('Pressure', {
        endpointName: notification.ep,
        value: notification.payload
      });
    });
  }
  
  if (notification.path === Temperature) {
	
    sockets.forEach(function(socket) {
      socket.emit('Temp', {
        endpointName: notification.ep,
        value: notification.payload
      });
    });
  }
 
  if (notification.path === GPIO) {
	    console.log("notification:GPIO");
   sockets.forEach(function(socket) {
      socket.emit('GPIO-STATE', {
        endpointName: notification.ep,
        value: notification.payload
      });
    });
  } 
  
});


// Start the app
server.listen(port, function() {
  // Set up the notification channel (pull notifications)
  mbedConnectorApi.startLongPolling(function(error) {
    if (error) throw error;
    console.log('mbed Device Connector Quickstart listening at http://localhost:%s', port);
  })
});
