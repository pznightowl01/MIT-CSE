var ball = document.getElementById("ball");

ball.animate(
    [
        { transform: "translateY(0px)" },
        { transform: "translateY(260px)" },
        { transform: "translateY(0px)" }
    ],
    {
        duration: 1000,
        iterations: Infinity,
        easing: "ease-in-out"
    }
);

