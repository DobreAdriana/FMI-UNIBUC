function thankyou(){

    var question1 = document.quiz.question1.value;
    var question2 = document.quiz.question2.value;
    var question3 = document.quiz.question3.value;
    var question4 = document.quiz.question4.value;
    var question5 = document.quiz.question5.value;
    var happy = 1;


    if (question3 == "*") {
        happy=0;
    }
    if (question3 == "**") {
        happy=0;
    }
    if (question4 == "Nu") {
        happy=0;
    }


    var pictures = ["happy.jpg", "sad.jpg"];
    var messages = ["Multumim pentru feedback!" , "Ne cerem scuze! Contacteaza-ne pentru a remedia orice situatie"];
    var score;

    if (happy == 1) {
        score = 0;
    }

    if (happy == 0) {
        score = 1;
    }

    document.getElementById("after_submit").style.visibility = "visible";

    document.getElementById("message").innerHTML = messages[score];
    document.getElementById("picture").src = pictures[score];
    picture.onclick = function () {
        after_submit.removeChild(picture);
    }
}