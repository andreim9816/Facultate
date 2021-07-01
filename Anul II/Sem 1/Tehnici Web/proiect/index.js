var http = require('http');
var url = require ('url');
var fs = require('fs');

const express = require('express')
const app = express()
const port = 3000

var spectacole = require('./spectacole.json')

app.use(express.json())

app.use(function(req, res, next) {
    res.header("Access-Control-Allow-Origin", "*"); // update to match the domain you will make the request from
    res.header("Access-Control-Allow-Headers", "Access-Control-Allow-Headers, Origin,Accept, X-Requested-With, Content-Type, Access-Control-Request-Method, Access-Control-Request-Headers, access-control-allow-origin")
    next();
  });

app.get('/spectacole', (req, res) =>
{
 res.send(spectacole);
 console.log("A ajuns la GET");
})

app.post('/abonare', function(req, res)
{
    console.log("A ajuns la POST", req.body);
    var date = fs.readFileSync('./abonati.json');
    var ob = JSON.parse(date);
    ob.push(req.body);
    fs.writeFileSync('./abonati.json', JSON.stringify(ob));
    res.send({state:"OK"});
})

app.post('/cumpara' , (req , res) =>
{
    let date = fs.readFileSync('./spectacole.json');
  //  let ob = JSON.parse(date);
   
    console.log(req);
    console.log("BODY",req.body); 

    res.send({state : "OK"});
})

app.listen(port, () => console.log(`Serverul merge la portul ${port}!`))
