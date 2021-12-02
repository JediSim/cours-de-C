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

/*


var dict = {
    "word_21": "Hello Java",
    "word_22": "Hello World",
    "word_11": "Hello Javascript"
}; // init (like your example)

var keys = Object.keys(dict); // or loop over the object to get the array
// keys will be in any order
keys.sort(); // maybe use custom sort, to change direction use .reverse()
// keys now will be in wanted order

for (var i=0; i<keys.length; i++) { // now lets iterate in sort order
    var key = keys[i];
    var value = dict[key];
    // do something with key & value here 
} 

*/


app.use("/q2", function(req, res) {
    db.collection("locomotion").mapReduce( 
        function () { 
            if (this["first-name"]!=null){
                emit(this["first-name"], 1);
            }else{
                emit("anonyme", 1);
            }
        }, 
        function (key, values) {             
            return Array.sum(values); 
        }, 
        {out: { inline: 1 }}, 
        function(err, data) { 
            if (err!=null) {
            //si il y a une erreur
                res.send(err);
            }else{
                data=data.sort(function(a,b){
                    if(a["_id"]<b["_id"]){
                        return -1;
                    }
                    if(a["_id"]>b["_id"]){
                        return 1;
                    }
                    return 0;})
                
                res.send(data);
            }
        }
    );
});

app.use("/q3", function(req, res) {
    db.collection("locomotion").mapReduce( 
        function () {
            if (this["first-name"]!=null){
                emit((this["first-name"].charAt(0).toUpperCase()), 1);
            }else{
                emit("anonyme", 1);
            }
            
        }, 
        function (key, values) { 
            return Array.sum(values);
            
        }, 
        { out: { inline: 1 }}, 
        function(err, data) { 
            if (err!=null) {
            //si il y a une erreur
                res.send(err);
            }else{
            // sinon je renvoie les données 
                data=data.sort(function(a,b){
                    if(a["_id"]<b["_id"]){
                        return -1;
                    }
                    if(a["_id"]>b["_id"]){
                        return 1;
                    }
                    return 0;})
                
                res.send(data);
            }
        } 
    );
});


app.use("/q4", function(req, res) {
    db.collection("locomotion").mapReduce( 
        function () {
            if (this["field"]!=null){
                emit(this["field"], 1)
            }else{
                emit("aucune", 1)
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

app.use("/q5", function(req, res) {
    db.collection("locomotion").mapReduce( 
        function () { 
            Object.keys(this).forEach(key=>{
                if(key.match(/^.*-feeling$/)){
                emit(key,parseInt(this[key]));}});
            
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

app.use("/q6", function(req, res) {
    db.collection("locomotion").mapReduce( 
        function () { 
            if(this["bus-time"] != null){
                emit(this["bus-affluence"],1);
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

app.use("/q7", function(req, res) {
    db.collection("locomotion").mapReduce( 
        function () { 
            if(this["car-pooling"] == "on"){
                emit(this["car-pooling"],1);
            }else{
                emit("off",1);
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

app.use("/q8", function(req, res) {
    db.collection("locomotion").mapReduce( 
        function () { 
            Object.keys(this).forEach(key=>{
                if(key.match(/^.*-time$/)){
                emit(key,parseInt(this[key]));}});
            
        }, 
        function (key, values) {
            res = Array.sum(values)/values.length;

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

app.use("/q9", function(req, res) {
    db.collection("locomotion").mapReduce( 
        function () { 
            Object.keys(this).forEach(key=>{
                if(key.match(/^.*-feeling$/)){
                emit(key,parseInt(this[key]));}});
            
        }, 
        function (key, values) {
            nbPersonnes = values.length;

            res = Array.sum(values)/nbPersonnes;

            return {"personnes": nbPersonnes, "feeling": res};
            
        }, 
        { out: { inline: 1 } }, 
        function(err, data) { 
            if (err!=null) {
            //si il y a une erreur
                res.send(err);
            }else{
            // sinon je renvoie les données 
                data=data.sort(function(a,b){
                    if(a["value"]["feeling"]<b["value"]["feeling"]){
                        return -1;
                    }
                    if(a["value"]["feeling"]>b["value"]["feeling"]){
                        return 1;
                    }
                    return 0;})

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
