
var numarComanda = 0;
var existaMesaj = false;

window.onload = function()
{
    // pentru afisarea acelui mesaj cu aboneaza-te
   setInterval(afisMesajAbonare , 30000);
   setTimeout( () => 
   {
    stergeMesajAbonare();
   }, 6000)
    
   getNames(); // genereaza Numele pieselor pentru partea de rezervare

   // setarea in engleza sau Romana
   seteazaLimba();

   console.log(document.getElementsByClassName("Text+Imagine")[0].innerText);
}

var language = {
    eng:
    {
        Rezervari : "Phone booking",
        Program : "For tickets:",
        ProgramOre : "Monday - Sunday 11.30 - 19.00 with break frm 14.30 to 15.00",
        Adresa : "Adress",
        Suport : "Online Support (for tickets)",
        Facebook : "Like us on facebook",
        Twitter : "Follow us on Twitter",
        Youtube : "Subscribe!"
    },

    ro:
    {
        Rezervari : "Rezervari",
        Program: "Program casierie",
        ProgramOre : "luni – duminica, orele 11.30– 19.00 cu pauza intre 14.30 - 15.00",
        Adresa : "Adresa",
        Suport : "Suport bilete online",
        Facebook : "Apreciaza-ne pe Facebook",
        Twitter : "Urmateste-ne pe Twitter",
        Youtube : "Aboneaza-te pe Youtube"
    }
}

function seteazaLimba()
{
    let optSelect = document.getElementById('selectLang');
    optSelect.addEventListener("change" , languageChange);
 
    let languageStored = localStorage.getItem('languageStored');
   
    if(languageStored === undefined)
    {
        languageStored = 'Engleza';
        localStorage.setItem('languageStored' , 'Engleza');
        optSelect.getElementsByTagName('option')[0].setAttribute('selected' , 'selected');
    }
    else 
    {
        if(languageStored == 'Engleza')
         optSelect.getElementsByTagName('option')[1].setAttribute('selected','selected');
        else optSelect.getElementsByTagName('option')[0].setAttribute('selected', 'selected');
        
        
         this.languageChange();
    }
}

function languageChange()
{
    let optSelect = document.getElementById('selectLang');

    let languageStored = localStorage.getItem('languageStored');

    let option = optSelect.value;
    languageStored = option;
    localStorage.setItem('languageStored' , languageStored);

    if(languageStored == 'Engleza')
    {
        let arrayH2 = document.getElementsByTagName('H2');
        arrayH2[0].textContent = language.eng.Rezervari;
        arrayH2[1].textContent = language.eng.Program;
        arrayH2[2].textContent = language.eng.Adresa;
        arrayH2[3].textContent = language.eng.Suport;

        let arrayP = document.getElementsByTagName('P');
        arrayP[1].textContent = language.eng.ProgramOre;

        
        let arrayTextImagine = document.getElementsByClassName('Text+Imagine');
        arrayTextImagine[0].getElementsByTagName('P')[0].innerText = language.eng.Facebook;
        arrayTextImagine[1].getElementsByTagName('P')[0].innerText = language.eng.Youtube;
        arrayTextImagine[2].getElementsByTagName('P')[0].innerText = language.eng.Twitter;
        
    }
    else 
    {
        let arrayH2 = document.getElementsByTagName('H2');
        arrayH2[0].textContent = language.ro.Rezervari;
        arrayH2[1].textContent = language.ro.Program;
        arrayH2[2].textContent = language.ro.Adresa;
        arrayH2[3].textContent = language.ro.Suport;

        let arrayP = document.getElementsByTagName('P');
        arrayP[1].textContent = language.ro.ProgramOre;

       
        let arrayTextImagine = document.getElementsByClassName('Text+Imagine');
        arrayTextImagine[0].getElementsByTagName('P')[0].innerText = language.ro.Facebook;
        arrayTextImagine[1].getElementsByTagName('P')[0].innerText = language.ro.Youtube;
        arrayTextImagine[2].getElementsByTagName('P')[0].innerText = language.ro.Twitter;
        
    }
}

function afisMesajAbonare()
{   
    
    let myDiv = document.createElement('DIV');
    let myBr = document.createElement('BR');
    let myP1 = document.createElement('P');
    let myP2 = document.createElement('P');
    
    document.getElementsByTagName("BODY")[0].appendChild(myDiv);

    myP1.innerText = "Ai petrecut destul de mult timp pe site";
    myP2.innerText = "Nu ai vrea sa te abonezi?";
    myP1.style.margin = "1px";
    myP2.style.margin = "1px";

    myDiv.setAttribute('id','mesaj');
    myDiv.style.padding = "15px";
    myDiv.style.color = "white";
    myDiv.style.backgroundColor = "black";
    
    myDiv.appendChild(myP1);
    myDiv.appendChild(myBr);
    myDiv.appendChild(myP2);

    myDiv.style.zIndex = "500";
    myDiv.style.fontSize = "18px";
    myDiv.style.position = "absolute";
    myDiv.style.marginTop = "150px";

    let currWidth = window.innerWidth
    console.log(currWidth);

    myDiv.style.marginLeft = currWidth/2 - 160  +"px";
    document.getElementsByTagName('BODY')[0].appendChild(myDiv);

}

function stergeMesajAbonare()
{
    setInterval( () =>
    {
        let myDiv = document.getElementById('mesaj');
     
        let divSlideShow = document.getElementsByClassName("Slideshow")[0];
        document.getElementsByTagName('BODY')[0].removeChild(myDiv);
        
    },30000);
}

function getNames()
{
    fetch("http://localhost:3000/spectacole")
    .then((data) => { return data.json() })
    .then((json) => displayNames(json))
}


function displayNames(data)
{
    let mySelect = document.getElementsByClassName("selectNume")[0];
    if(mySelect)
    {
        for (let i = 0; i < data.length; i++)
        {
            let ok = 1;
        
            for(let j = 0 ; j < i ; j++) // trebuie sa am grija sa nu afisez un spectacol de 2 ori
                if(data[i]["nume"] == data[j]["nume"])
                {
                    ok = 0;
                    break;
                }

            if(ok == 1)
            {
                let myOption = document.createElement('OPTION');
                myOption.innerText = data[i]["nume"];
                mySelect.appendChild(myOption);
            }
        }   
    }
}

function displayDates()
{
    fetch("http://localhost:3000/spectacole")
    .then((data) => { return data.json() })
    .then((data) => 
    {
       
        let i;
        let selectName = document.getElementsByClassName("selectNume")[0];
        let selectDate = document.getElementsByClassName("selectData")[0];
        
        // sterge ce era inainte
        for(i = selectDate.options.length - 1 ; i >= 0 ; i--)
            selectDate.remove(i);
        
        let myOption = document.createElement('OPTION');
        myOption.innerText = "---";
        selectDate.appendChild(myOption);

        for(i = 0 ; i < data.length ; i++)
         if(data[i]["nume"] == selectName.value) // am gasit spectacolul respectiv in fisier
         {
             let myOption = document.createElement('OPTION');
             myOption.innerText = data[i].data;
             selectDate.appendChild(myOption);
         }
         resetPrice();
    })
}

function displaySeats()
{
    // functie care avand un spectacol setat si o data setata, afiseaza locurile ocupate si cele neocupate
  
    fetch("http://localhost:3000/spectacole")
    .then((data) => { return data.json() })
    .then((data) => 
    {
        let i, j, k = 0;
    
        let nrLinii = 5;
        let nrColoane = 10;
    
        let selectNume = document.getElementsByClassName("selectNume")[0];
        let selectData = document.getElementsByClassName("selectData")[0];

        // seteaza la loc, pentru ca mai apoi sa scrie peste 
        for(i = 0 ; i < nrLinii ; i++)
        for(j = 0 ; j < nrColoane ; j++)
            document.getElementById(i.toString() + j.toString()).style.backgroundColor = "brown";

        // parcurgem elementele din fisier. Cand gasim spectacolul selectat din data selectata, atunci afisam locurile(ocupate / neocupate)
        for(let index = 0 ; index < data.length ; index++)
            {  
                if(selectNume.value == data[index]["nume"] && selectData.value == data[index]["data"])
                { 
                    
                    for(i = 0 ; i < nrLinii ; i++ )
                    for(j = 0 ; j < nrColoane ; j++)
                    {   
                        if(data[index].locuri[k] == "1") // daca este ocupat
                        {   
                            
                            let myDiv = document.getElementById(i.toString() + j.toString());
                            myDiv.style.backgroundColor = "grey";
                        }
                        k++;
                    }
                    
                    // seteaza si preturile
                    let myTable = document.getElementsByTagName('TABLE')[1];
                    myTable.rows[1].cells[1].innerText = data[index].pret.adult;
                    myTable.rows[2].cells[1].innerText = data[index].pret.elev;
                    myTable.rows[3].cells[1].innerText = data[index].pret.pensionar;

                break;
                }
            }
    })
}

function rezerva(elem)
{   
    // verificam sa nu fie deja ocupat. Daca nu este ocupat, atunci il coloram, il adaugam in cos
    let currColor = window.getComputedStyle(elem,null).getPropertyValue("background-color");

    if(currColor != "rgb(128, 128, 128)" && currColor != 'grey' && document.getElementsByClassName('selectNume')[0].value != '---' && document.getElementsByClassName('selectData')[0].value != '---') 
    {
        if(currColor  == "rgb(91, 32, 16)" || currColor == "brown")
        {
            // punem rosu la loc, scoatem din cos
            // crestem pretul
            let totalCost = document.getElementById('pretTotal').value;
            let totalCostInt = parseInt(totalCost);
  
            let myTable = document.getElementsByClassName("tableCosCumparaturi")[0];
            let noOfRows = myTable.rows.length;
            let i;
            
            // cautam randul pe care se gaseste 
            for(i = 0 ; i < noOfRows ; i ++)
             {
                 let string1 = myTable.rows[i].cells[0].innerText;
                 let cifra1 = parseInt(string1[7]) - 1;
                 cifra1 = cifra1.toString();

                 let string2 = myTable.rows[i].cells[1].innerText;
                 let cifra2 = parseInt(string2[6]) - 1;
                 cifra2 = cifra2.toString();

                 if(elem.id == (cifra1 + cifra2))
                    {   
                        totalCostInt -= parseInt(myTable.rows[i].cells[3].innerText);
                        document.getElementById("pretTotal").value = totalCostInt;
                        myTable.deleteRow(i);
                        break;
                    }
            }
            elem.style.backgroundColor= "rgb(165, 42, 42)"
        }
        else 
        {
            // daca era rosu, rezervam si adaugam in cos
            numarComanda++;

            let totalCost = document.getElementById('pretTotal').value;

            let totalCostInt = parseInt(totalCost);

            let myTable = document.getElementsByClassName("tableCosCumparaturi")[0];
            let tablePret = document.getElementsByTagName("TABLE")[1]; // tabela cu preturi

            let noOfRows = myTable.rows.length;

            if(noOfRows == 0)
             totalCostInt = 0;
           
            totalCostInt = totalCostInt + parseInt(tablePret.rows[1].cells[1].innerText); // aduna pretul pt adulti
            document.getElementById('pretTotal').value = totalCostInt;

            let nr = parseInt(elem.id[0]);
            nr++;
            let rand = "randul " + nr;

            nr = parseInt(elem.id[1]);
            nr++;
            let col = "locul " + nr;
            elem.style.backgroundColor = "rgb(91, 32, 16)"


            let row = myTable.insertRow(noOfRows);
            
            let cell1 = row.insertCell(0);
            let cell2 = row.insertCell(1);
            let cell3 = row.insertCell(2);
            let cell4 = row.insertCell(3);
            let cell5 = row.insertCell(4);

           
            cell1.innerText = rand;
            cell2.innerText = col;
            
            // creaza un select cu optiunile adult, elev, pensionar
            let mySelect = document.createElement('SELECT');
            mySelect.setAttribute('id' , numarComanda);
            mySelect.onchange = function(event)
            {
                let id = event.target.id;
                let tipPersoana = event.target.value;
                let myTable = document.getElementsByClassName("tableCosCumparaturi")[0];

                let stop = 1;

                for(let i = 1 ; i < 4 && stop ; i++)
                 {
                     if(tablePret.rows[i].cells[0].innerText == tipPersoana && stop)
                    {
                        let pretCorect = parseInt(tablePret.rows[i].cells[1].innerText);
                        let fostPret;
                       
                       // cautam locul respectiv in cosul de cumparaturi, dupa id
                       for(let j = 0 ; j < myTable.rows.length && stop ; j++)
                        {
                            if(id == myTable.rows[j].cells[2].getElementsByTagName('SELECT')[0].id)
                            {
                                fostPret = parseInt(myTable.rows[j].cells[3].innerText);

                                totalCostInt = parseInt(document.getElementById('pretTotal').value);
                                
                                // updatez pretul in cosul de cumparaturi pentru locul respectiv
                                totalCostInt = totalCostInt + pretCorect - fostPret;
                                myTable.rows[j].cells[3].innerText = pretCorect;
                                
                                // updatez pretul total din cosul de cumparaturi
                                document.getElementById('pretTotal').value = totalCostInt;

                                stop = 0;
                                break;
                            }
                        }
                    }

                }
            }

            cell3.appendChild(mySelect);  
            
            let myOption = document.createElement("OPTION");
            myOption.innerText = "Adult";
            mySelect.appendChild(myOption);


            myOption = document.createElement("OPTION");
            myOption.innerText = "Elev/Student";
            mySelect.appendChild(myOption);

            myOption = document.createElement("OPTION");
            myOption.innerText ="Pensionar";
            mySelect.appendChild(myOption);

            
            // cati lei costa un bilet
            cell4.innerText = tablePret.rows[1].cells[1].innerText;
        }
    }
    
}

function resetPrice()
{
    let table = document.getElementsByTagName('TABLE')[0];
    let i;
    let noOfRows = table.rows.length;

    while(noOfRows > 0)
     table.deleteRow(0);
    
     document.getElementById('pretTotal').value = "0";
}

function Submit()
{
    let name = document.getElementsByName('Name')[0].value;
    let mail = document.getElementsByName('Mail')[0].value;

    fetch("http://localhost:3000/abonare", {
        method: 'POST',
        mode: 'cors', // no-cors, *cors, same-origin
        cache: 'no-cache', // *default, no-cache, reload, force-cache, only-if-cached
        credentials: 'same-origin', // include, *same-origin, omit
        headers: {
            'Content-Type': 'application/json'
        // 'Content-Type': 'application/x-www-form-urlencoded',
        },
        redirect: 'follow', // manual, *follow, error
        referrerPolicy: 'no-referrer', // no-referrer, *client
        body: JSON.stringify({name: name, mail: mail})
    }).then((data) => 
    {
        console.log(data);
        return data.json()
    })
    .then((json) =>
    {

    })
}

function cumpara()
{
    let obj = [], i ;
    let tabel = document.getElementsByTagName('TABLE')[0];
    
    let piesa = document.getElementsByClassName('selectNume')[0].value;
    let data = document.getElementsByClassName('selectData')[0].value;

    obj.push( JSON.stringify({piesa : piesa , data : data}) );

    for(i = 0 ; i < tabel.rows.length ; i++)
       {
           let row , col;

           row = tabel.rows[i].cells[0].innerText.length;
           row = tabel.rows[i].cells[0].innerText[row - 1];

           col = tabel.rows[i].cells[1].innerText.length;
           col = tabel.rows[i].cells[1].innerText[col - 1];

           obj.push( JSON.stringify({row : row , col : col}));
       }
    
    console.log(obj , typeof(obj));

    fetch("http://localhost:3000/cumpara", {
        method: 'POST',
        mode: 'no-cors', // no-cors, *cors, same-origin
        cache: 'no-cache', // *default, no-cache, reload, force-cache, only-if-cached
        credentials: 'same-origin', // include, *same-origin, omit
        headers: {
            'Content-Type': 'application/json'
        // 'Content-Type': 'application/x-www-form-urlencoded',
        },
        redirect: 'follow', // manual, *follow, error
        referrerPolicy: 'no-referrer', // no-referrer, *client
        body: obj
    }).then((data) =>  
    {
        console.log(data);
        return data.json()
    })
    .then((json) =>
    {

    })
}