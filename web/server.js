// server.js
// Package inclusion
var express     = require('express');
var mysql       = require('mysql');

var app         = express();
var port        = process.env.PORT || 8080;

// MySQL credentials
var connection  = mysql.createConnection({
    host:       'localhost',    // IP Host
    user:       'root',         // MySQL Username
    password:   '',             // MySQL Password
    database:   'cheschirecat'  // DB Name
});

// MySQL Connection
connection.connect(function (err) {
    if(err) throw err; // If connection fail, check console
    console.log('You are now connected')
});

// Redirect to route.js file
require('./app/routes')(app, connection);

// Server listening
app.listen(port);
console.log('Listening on port ' + port);