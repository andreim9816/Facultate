window.addEventListener("load",function(){
	setInterval(
		function(){
			document.body.appendChild(document.createTextNode(Math.floor(Math.random()*1000)+" "));
			document.body.normalize();
		},500
	);
});

window.onload = function()
{
	// la onload, afiseaza ce e in localStorage
	let i;
	let vect = localStorage.getItem("numere");
	if(vect)
	{
		document.body.lastChild.nodeValue = vect;
	}
	else 
	{
		console.log("Niciun numar");
	}

	document.getElementById('salveaza').onclick = function()
	{
		localStorage.setItem("numere", document.body.lastChild.nodeValue );
	}

	document.getElementById('sterge').onclick = function()
	{
		document.body.lastChild.nodeValue ="";
		localStorage.setItem("numere","");
	}
}