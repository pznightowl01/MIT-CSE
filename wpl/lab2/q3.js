function updateCard() {
    var card = document.getElementById("card");
    var message = document.getElementById("message");

    card.style.backgroundColor = document.getElementById("bgColor").value;
    message.style.fontFamily = document.getElementById("font").value;
    message.style.fontSize = document.getElementById("fontSize").value + "px";
    message.innerText = document.getElementById("text").value;

    var borders = document.getElementsByName("border");
    for (var i = 0; i < borders.length; i++) {
        if (borders[i].checked) {
            card.style.borderStyle = borders[i].value;
        }
    }
}
