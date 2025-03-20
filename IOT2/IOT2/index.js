const express = require('express');
const app = express();
const PORT = 3000;

app.get('/', function (req, res) {
    res.sendFile(__dirname + "/views/index.html");
});

const server = app.listen(PORT, function () {
    console.log("Server is running at port " + PORT);
});

const SocketServer = require('ws').Server;
const wss = new SocketServer({ server });

let currentRangeValue = 0;

wss.on('connection', function (ws) {
    console.log('Client connected');

    ws.send(currentRangeValue);

    ws.on('message', function (msg) {
        currentRangeValue = msg;
        broadcast(currentRangeValue);
    });

    ws.on('close', function () {
        console.log('Client disconnected');
    });
});

function broadcast(value) {
    wss.clients.forEach(function (client) {
        if (client.readyState === client.OPEN) {
            client.send(value);
        } else {
            console.log("Client off");
        }
    });
}
