
var connection = new WebSocket('ws://opencat.local:81/', ['arduino']);
connection.onopen = function () {
  // connection.send('Connect ' + new Date());
};
connection.onerror = function (error) {
  console.log('WebSocket Error ', error);
};
connection.onmessage = function (e) {
  console.log('Server: ', e.data);
};
connection.onclose = function () {
  console.log('WebSocket connection closed');
};

function sendX(val) {
  send(0, val)
}

function sendY(val) {
  send(1, val)
}

function sendZ(val) {
  send(2, val)
}

function send(id, val) {
  // var data = leg << 12 | joint << 10 | value;
  console.log(id, val)
  val = parseInt(val) + 128
  var data = (id << 16) | val;
  var datastr = data.toString(16);
  console.log('DATA: ' + datastr + ' (' + data + ')');

  parse(datastr)

  connection.send(datastr);
}

function parse(payload) {
  var commandData = parseInt(payload, 16)
  var id = (commandData >> 16) & 3
  var val = (commandData & 255) - 128

  console.log("PARSE", id, val)
}
