window.onload = function()
{
    let elem = document.querySelectorAll('*');

    for(let i of elem)
    {
        if(i.classList.length >= 3) // au peste 3 clase
        {
            i.classList.add("c3");
        }
    }

    document.getElementsByTagName('BODY')[0].onclick = function()
    {
        elem = document.querySelectorAll('*');
        let j,i,k;

        for( j of elem) // pentru fiecare element
        {
            for(i = 0 ; i < j.classList.length ; i++) // luam fiecare clasa a elementului
            {
                let clasa = j.classList.item(i); // stringul ce denumeste clasa 
                for( k = 0 ; k < clasa.length - 1 ; k++) // parcurgem si vedem daca contine 'z'
                {
                    if('z' == clasa[k])
                    {
                        j.classList.remove(j.classList.item(i));
                        i--;
                        break;
                    }
                }
            }
        }
    }
}