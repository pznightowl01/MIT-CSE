from django.shortcuts import render
def student_form(request):
data = ""
percentage = None
if request.method == "POST":
name = request.POST.get("name")
dob = request.POST.get("dob")
address = request.POST.get("address")
contact = request.POST.get("contact")
email = request.POST.get("email")
eng = int(request.POST.get("english"))
phy = int(request.POST.get("physics"))
chem = int(request.POST.get("chemistry"))
total = eng + phy + chem
percentage = total / 3
data = (
f"Name: {name}\n"
f"DOB: {dob}\n"
f"Address: {address}\n"
f"Contact: {contact}\n"
f"Email: {email}\n"
f"English: {eng}\n"
f"Physics: {phy}\n"
f"Chemistry: {chem}\n"
)
return render(request, "student_form.html", {
"data": data,
"percentage": percentage
})
