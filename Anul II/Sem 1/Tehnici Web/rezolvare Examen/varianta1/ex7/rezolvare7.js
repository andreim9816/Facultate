 
 
 var vt;
 window.onload = function()
 {
    setTimeout(stop,10000);
     vt = setInterval(genereaza,500); // genereaza la fiecare jum de secunda 
 }

function stop()
{
    clearInterval(vt);
}

 function genereaza()
 {
    let i;
    let but = document.createElement('BUTTON');
    but.value = "ok";
    but.innerText = "ok";
    but.onclick = function()
    {
        if(this.previousElementSibling.innerText == "ok" && this.nextElementSibling.innerText == "ok")
        {
            setTimeout(puneApasat,1000,this);
        }
    } 
    
    let body = document.getElementsByTagName('BODY')[0];
    body.appendChild(but);
 }

 function puneApasat(t)
 {
     t.innerText = "apasat";
 }