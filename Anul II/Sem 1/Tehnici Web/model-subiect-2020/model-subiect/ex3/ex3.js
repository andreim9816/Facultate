 

window.addEventListener("load", function(){
	var rng = document.getElementById("rng");
	rng.max = Math.floor(20+Math.random()*20);
	rng.parentNode.insertBefore(document.createTextNode(rng.min), rng);
	rng.parentNode.appendChild(document.createTextNode(rng.max));
	rng.value=rng.min;
});

window.onload = function()
{
	let range = document.getElementById('rng');
	range.onchange = function()
	{
		let val = range.value;
		document.body.style.fontSize = val + "px";

		if(val >= (parseInt(range.min) + parseInt(range.max))/2)
		 document.body.style.color = "red";
		 else document.body.style.color ="blue";

	}

	let buttons = document.getElementsByTagName("input");
	let i;
	for(i = 1 ; i < buttons.length ; i++)
	 {
		 buttons[i].setAttribute('name' , 'grup');
	 }

	 let buton = document.getElementById('btn');
	 buton.onclick = function()
	 {
		let j;
		let selectedValue;
		let radioButtons = document.querySelectorAll("input[type=radio]");
		
		for(let ra of radioButtons)
		{
			if(ra.checked == true)
			 selectedValue = ra.nextSibling.nodeValue;
		}
		console.log(selectedValue);
		buton.innerText = selectedValue;
	 }

}