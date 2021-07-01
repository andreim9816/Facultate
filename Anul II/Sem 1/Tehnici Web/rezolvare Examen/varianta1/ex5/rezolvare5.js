window.onload = function()
{
 

   
    document.onmousemove = function(e)
    {
        var x = e.clientX;
        var y = e.clientY;

        let divs = document.getElementsByClassName('d1');
        let i;

        for(i of divs)
            if(parseInt(i.style.left) > x)
            {
                i.style.backgroundColor = 'blue';
                
            }
        
    }
}