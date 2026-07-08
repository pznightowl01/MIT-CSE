const button = document.getElementById('moveButton');
const container = document.getElementById('moveContainer');

button.addEventListener('click', function() {
    container.style.transform = "translateX(0px)";
});
