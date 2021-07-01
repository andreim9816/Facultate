
/*
window.onkeydown=function(e){
	var dvs=document.getElementsByClassName("d1");
	if (e.key=='q') pas=1;
	if (e.key=='w') pas=-1;
	for(dv of dvs){
		inalt=parseInt(getComputedStyle(dv).height);
		inalt=Math.max(inalt+pas,0);
		dv.style.height=inalt+"px";
	}
}
*/
window.onkeydown = function(e)
{
	var divs = document.getElementsByClassName("d1");
	let inaltime ;
	let pas = 0;
	
	console.log(e.key);
	if(e.key == 'q')
	 pas = 1;
	else if(e.key == 'e')
	 pas = -1;

	for(let i = 0 ; i < divs.length ; i++)
	 {
		inaltime = parseInt(getComputedStyle(divs[i]).height);
		inaltime += parseInt(pas);
		inaltime = Math.max(inaltime,0);
		divs[i].setAttribute('style' , "height:" + inaltime +"px");
	 }
		
}