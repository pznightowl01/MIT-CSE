let currentInput = "0";
let firstNum = null;
let operator = null;
let shouldResetScreen = false;

const display = document.getElementById('display');

function appendNumber(num) {
    if (currentInput === "0" || shouldResetScreen) {
        currentInput = num;
        shouldResetScreen = false;
    } else {
        currentInput += num;
    }
    updateDisplay();
}

function setOperator(op) {
    firstNum = Number(currentInput);
    operator = op;
    shouldResetScreen = true;
}

function clearDisplay() {
    currentInput = "0";
    firstNum = null;
    operator = null;
    updateDisplay();
}

function updateDisplay() {
    display.value = currentInput;
}

function calculate() {
    if (operator === null || shouldResetScreen) return;

    let secondNum = Number(currentInput);
    let result = 0;

    if (operator === '+') result = firstNum + secondNum;
    if (operator === '-') result = firstNum - secondNum;
    if (operator === '*') result = firstNum * secondNum;
    if (operator === '/') {
        result = secondNum === 0 ? "Error" : firstNum / secondNum;
    }

    currentInput = result.toString();
    operator = null;
    updateDisplay();
    shouldResetScreen = true;
}
