var numarSecret = Math.floor(Math.random() * 20) + 1;
alert(numarSecret);
var mesaj = document.querySelector(".afisare");
var nume = document.getElementById("nume");
var input = document.getElementById("ghiceste");
var buton = document.getElementById("verifica");
var r = 2;
var i = 0;
var nr = document.querySelector(".incercare");
var rest = document.querySelector(".ramas");
var myVar = setInterval(setColor, 400);
function setColor() {
    var x = document.body;
    if (x.style.backgroundColor == "lightskyblue")
        x.style.backgroundColor = "royalblue";
    else x.style.backgroundColor = "lightskyblue";
}
function stopColor() {
    clearInterval(myVar);
}
buton.onclick = function () {
    if (r > 1) {
        i = i + 1;
        if (input.value == numarSecret) {
            stopColor()
            document.body.style.backgroundColor = "dodgerblue";
            mesaj.innerHTML = "Felicitari, " + nume.value + "!Ati castigat un voucher de " + input.value + "%! Asteptam un mail din partea dumneavoastra pentru a va revendica premiul!"
            document.querySelector(".numar").innerHTML = input.value;
            nr.innerHTML = i;
            rest.innerHTML = r;
            var paragraf = document.createElement("p");
            paragraf.innerHTML = "Felicitari, " + nume.value + "! Ai castigat un voucher cu reducerea de  " + input.value + "%. Trimite-ne un mail pentru ati revendica premiul!";
            document.getElementById("rezultat").appendChild(paragraf);
            paragraf.className = "rez";
        }
        else {
            r--;
            rest.innerHTML=r;
            nr.innerHTML=i;
        }
        }
    else {
        rest.innerHTML=0;
        nr.innerHTML=2;
        mesaj.innerHTML = "Ne pare rau, " + nume.value + " ,dar nu ai reusit! ";
        buton.disabled = true;
    }
}


