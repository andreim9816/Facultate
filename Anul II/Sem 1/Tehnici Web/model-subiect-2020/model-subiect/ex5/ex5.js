window.onclick = function(e)
{
    let x = e.clientX;
    let y = e.clientY;

    console.log(x,y);

    let div = document.createElement('DIV');
    div.setAttribute('class','animat');
    div.style.position = "absolute";
    document.getElementsByTagName('body')[0].appendChild(div);
    let h = parseInt(getComputedStyle(div).height);
    let w = parseInt(getComputedStyle(div).width);

    let marginTop = y - h/2;
    let marginLeft = x - w/2;

    div.style.left = marginLeft + 'px';
    div.style.top= marginTop + "px";

    div.onclick = function(e)
    {
        e.stopImmediatePropagation();
    }
}