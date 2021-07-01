window.onload = function()
{
    // memoram in localStorage numarul elem
    // memoram in localStorage suma

    let elem = parseInt(localStorage.getItem('elem'));
    let body = document.getElementsByTagName('BODY')[0];

    if(!elem) // daca numarul nu exista in localStorage, deci e prima data cand intru in pagina
    {
        let random = Math.floor(Math.random() * 500);
        let primulText = document.createTextNode("text");
        console.log(random);
        primulText.nodeValue = random;        

        let alDoileaText = document.createTextNode("text");
        alDoileaText.nodeValue = " 0";

        body.appendChild(primulText);
        body.appendChild(alDoileaText);

        localStorage.setItem('elem',random.toString());
        localStorage.setItem('suma','0');

      //  console.log("NU AR TREUBI");
    }

    else 
    {
        // exista deja stocat
        let random = Math.floor(Math.random() * 500);
        let buton = document.getElementById('res');
        let suma = parseInt(localStorage.getItem('suma')); // suma de pana acum

        // aceseaza textele
        let primulText = buton.nextSibling; 
        let alDoileaText = buton.nextSibling.nextSibling;

        console.log(primulText);
        console.log(alDoileaText);
        
        primulText.nodeValue = random; // punem pe prima pozitie elementul random
        alDoileaText.nodeValue = suma + elem;
        
        localStorage.setItem('elem',random.toString());
        localStorage.setItem('suma',alDoileaText.nodeValue.toString());

         // care va fi suma 
    }

    let buton = document.getElementById('res');
    buton.onclick = function()
    {
        // la click se reseteaza
        localStorage.setItem('suma','0');

    }
}