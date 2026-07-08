function updateCover() {
const bgColor = document.getElementById("bgColor").value;
const font = document.getElementById("font").value;
const fontSize = document.getElementById("fontSize").value;
const fontColor = document.getElementById("fontColor").value;
const titleText = document.getElementById("titleText").value;
const subtitleText = document.getElementById("subtitleText").value;
const imageInput = document.getElementById("imageInput");
const cover = document.getElementById("cover");
const title = document.getElementById("title");
const subtitle = document.getElementById("subtitle");
const coverImage = document.getElementById("coverImage");
cover.style.backgroundColor = bgColor;
title.textContent = titleText;
subtitle.innerHTML = subtitleText.replace(/\n/g, "<br>");
title.style.fontFamily = font;
subtitle.style.fontFamily = font;
title.style.color = fontColor;
subtitle.style.color = fontColor;
subtitle.style.fontSize = fontSize + "px";
if (imageInput.files && imageInput.files[0]) {
const reader = new FileReader();
reader.onload = function(e) {
coverImage.src = e.target.result;
}
reader.readAsDataURL(imageInput.files[0]);
}
}
