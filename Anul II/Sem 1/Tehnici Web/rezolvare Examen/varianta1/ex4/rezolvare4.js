window.onkeypress = function(e)
{
    var days = ["duminca","luni","marti","miercuri","joi","vineri","sambata"];
    if(e.key == 'd')
    {
        let data = new Date();
        let zi = days[data.getDay()];
        let luna = parseInt(data.getMonth() +1);
        let an = (data.getFullYear()).toString();

        let input = document.getElementById("data");
        input.value="";
        input.value = input.value + zi + " "+luna + " "+an[2] + an[3];
    }
}
 