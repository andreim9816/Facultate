window.onload = function()
{
    let rng = document.getElementById('rng');
    rng.onchange = function()
    {
        let divs = document.querySelectorAll('DIV');
        for(let i of divs)
        {
            if(i.innerHTML == rng.value)
            i.setAttribute('style','border:2px solid green');
        }
    }
}