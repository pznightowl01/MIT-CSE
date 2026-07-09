 function validateForm() {
            var model = document.getElementById("model").value;
            if (model === "") {
                alert("Please enter model name");
                return false;
            }
            return true;
        }
