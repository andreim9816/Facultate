window.onload = function()
{
    let elem;
    elem = document.querySelectorAll("div+p");
    
    for(let p of elem)
    {
        p.onclick = function()
        {
            this.innerHTML = this.previousElementSibling.querySelectorAll('li').length;
        }
    }
}