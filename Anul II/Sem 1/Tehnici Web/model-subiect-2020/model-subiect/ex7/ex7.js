 

window.onload  = function()
{
    setTimeout(fct, 1500);
}

function fct()
{
    let i;

    for(i = 0 ; i < 10 ; i++)
    {
        let div = document.createElement('button');
        document.getElementsByTagName('body')[0].appendChild(div);
        div.innerHTML = 0;
        div.activ = 0;

        div.onclick = function()
        {
            if(this.activ == 0)
            {
                //era pauza si am dat click, incepe numaratoarea
               this.activ = setInterval(function(t)
               {
                   t.innerHTML = 1 + parseInt(t.innerHTML);
               },1000,this);
            }
            else 
            {
               
                clearInterval(this.activ);
                this.activ = 0;
            }
        }
    }
}
