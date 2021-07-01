 

window.onload = function()
{
    let i, elem,elem1;
    elem1 = document.querySelectorAll('.a.b');

    for(let p of elem1)
    {
        if( p.classList.contains('c') == 0 && p.classList.contains('d') == 0)
         p.classList.add('zzz');
    }

     let but = document.getElementById('clase_multe');
     but.onclick = function()
     {
         for(let i = 0 ; i < but.classList.length ; i++)
         {
             let cls = but.classList.item(i);

             if(parseInt(cls[cls.length -1]) %2 ==0)
              {
                  but.classList.remove(cls);
                  i--;
              }
         }
     }
}