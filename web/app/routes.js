// app/routes.js
// Route file exportation for server.js file
module.exports      = function (app, connection) {

    // ----------
    // Insertion Route
    app.get('/insert/:username/:computername/:password', function (req, res) {

        // Set all URL parameters in tab
        var param = {
            username: req.params.username,
            computername: req.params.computername,
            password: req.params.password,
            paid: "0"
        };

        // Request to DB in table 'users'
        connection.query('INSERT INTO users (user_name, machine_name, password, status) VALUES (?, ?, ?, ?)', [param.username, param.computername, param.password, param.paid], function (err, result) {

            // Request didn't work
            if(err)
                // Send back error code
                res.send("400");

            // Request worked
            console.log("Insert worked : " + param.username + " " + param.computername + " " + param.password);
        });

        // Send back success code
        res.send("200");

    })

};