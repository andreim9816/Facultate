const express=require('express');
app=express();
app.use('/ex10.html',express.urlencoded({extended:false}));

obiecte=[
	{
		nume:"a",
		culoare:"rosu",
		dimensiune:3,
	},
	{
		nume:"b",
		culoare:"verde",
		dimensiune:1,
	},
	{
		nume:"c",
		culoare:"albastru",
		dimensiune:4,
	},
	{
		nume:"d",
		culoare:"verde",
		dimensiune:1,
	},
	{
		nume:"e",
		culoare:"rosu",
		dimensiune:5,
	},
	{
		nume:"f",
		culoare:"albastru",
		dimensiune:2,
	},
	{
		nume:"g",
		culoare:"rosu",
		dimensiune:1,
	}
]
app.get("/ex10.html", function(req,res){

	res.sendFile(__dirname+"/ex10.html");
});

//Completati 

app.post('/ex10.html', function(req,res)
{
	let i;
	var ob = [];

	for(i of obiecte)
	{
		if(i.culoare == req.body.culoare && i.dimensiune < req.body.dimensiune)
			ob.push(i);
	}

	res.send(ob);
});

app.listen(8010);
console.log("Serverul a pornit");