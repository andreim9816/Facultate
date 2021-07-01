window.onload = function()
{
    let p = document.querySelectorAll('div+p b');
    let i;
    
    for(i of p)
    {
        let string = (i.textContent).toString();
        let stringRev = "";
        
        let j = string.length - 1;

        while(j>=0)
        {
            
            stringRev += string[j];
            j--;
        }
        i.textContent = stringRev;
    }
    
}