var express = require("express"), app = express(); 
var MongoClient = require("mongodb").MongoClient, db = null;

app.listen(11010, function() { 
    console.log("L’application est lancée..."); 
});

// CHEMIN
app.use(express.urlencoded({extended: true})); 
app.use("/", express.static(__dirname + "/public"));
app.use("/distance/:city", function(req, res) {
    // Faire la requête à l’API de distance.org 
    require("https").request({ 
        host: "fr.distance24.org", 
        path: encodeURI("/route.json?stops=Bourget-du-lac|"+req.params.city), 
        port: 443, 
        method: "GET" 
    }, function(result) { 
        var response = "";
        var dist=null;
        result.setEncoding("utf8"); 
        result.on("data", (chunk) => { 
            console.log("getting chunk...")
            response+= chunk
        }); 
        result.on("end", () => { 
            response=JSON.parse(response);
            console.log("DISTANCE : "+response.distance)
            dist={distance:response.distance}
            res.send(dist);

        });
        
    }).end();
    // et envoyer au client la distance quand on aura la réponse 
}) ;
app.use("/json", function(req, res) {
    response="";
    result = db.collection("locomotion").find().toArray(function(err,arr){
        res.send(arr);
     });
});


app.use("/q1", function(req, res) {
    db.collection("locomotion").mapReduce( 
        function () { 
            emit(this["no-test"], 1)
            
        }, 
        function (key, values) { 
            return Array.sum(values);
            
        }, 
        { out: { inline: 1 } }, 
        function(err, data) { 
            if (err!=null) {
            //si il y a une erreur
                res.send(err);
            }else{
            // sinon je renvoie les données 
                res.send(data);
            }
        } 
    );
});

app.use("/q2", function(req, res) {
    db.collection("locomotion").mapReduce( 
        function () { 
            emit(this["first-name"], 1);
            
        }, 
        function (key, values) { 
            res = Array.sum(values);
            res.sort(function compare(a, b) {
                if (a._id < b._id)
                   return -1;
                if (a._id > b._id )
                   return 1;
                return 0;
              });

            return res; 
        }, 
        { out: { inline: 1 } }, 
        function(err, data) { 
            if (err!=null) {
            //si il y a une erreur
                res.send(err);
            }else{
            // sinon je renvoie les données 
                res.send(data);
            }
        } 
    );
});

app.use("/q3", function(req, res) {
    db.collection("locomotion").mapReduce( 
        function () { 
            emit(this["first-name"].charAt(0), 1)
            
        }, 
        function (key, values) { 
            return Array.sum(values);
            
        }, 
        { out: { inline: 1 } }, 
        function(err, data) { 
            if (err!=null) {
            //si il y a une erreur
                res.send(err);
            }else{
            // sinon je renvoie les données 
                res.send(data);
            }
        } 
    );
});


app.use("/q4", function(req, res) {
    db.collection("locomotion").mapReduce( 
        function () { 
            emit(this["field"], 1)
            
        }, 
        function (key, values) { 
            return Array.sum(values);
            
        }, 
        { out: { inline: 1 } }, 
        function(err, data) { 
            if (err!=null) {
            //si il y a une erreur
                res.send(err);
            }else{
            // sinon je renvoie les données 
                res.send(data);
            }
        } 
    );
});

app.use("/q5", function(req, res) {
    db.collection("locomotion").mapReduce( 
        function () { 
            if(this["bus-time"] != 'undefined' && this["foot-time"] != 'undefined'){
                emit("car", 1);
            }else if(this["bus-time"] != 'undefined' && this["car-time"] != 'undefined'){
                emit("foot",1);
            }else if(this["car-time"] != 'undefined' && this["foot-time"] != 'undefined'){
                emit("bus",1);
            }
            
        }, 
        function (key, values) { 
            return Array.sum(values);
            
        }, 
        { out: { inline: 1 } }, 
        function(err, data) { 
            if (err!=null) {
            //si il y a une erreur
                res.send(err);
            }else{
            // sinon je renvoie les données 
                res.send(data);
            }
        } 
    );
});

MongoClient.connect( 
    "mongodb://gr1_10:eic8I@localhost:27017/info508", 
    { useUnifiedTopology: true }, 
    function(err, client) { 
        // s’il y a une erreur je l’affiche 
        if(err!=null){
            console.log(err); 
        }else{
            // sinon je mets à jour la variable db 
            db = client.db("info508"); 
        }
        
    } 
);
