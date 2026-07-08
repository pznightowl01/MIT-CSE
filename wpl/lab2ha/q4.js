function produceBill() {
    var brandPrice = document.getElementById("brand").value;
    var qty = document.getElementById("qty").value;
    var total = 0;

    if (document.getElementById("mobile").checked) {
        total += 5000;
    }

    if (document.getElementById("laptop").checked) {
        total += 20000;
    }

    total = (parseInt(brandPrice) + total) * parseInt(qty);

    alert("Total Amount = ₹" + total);
}

