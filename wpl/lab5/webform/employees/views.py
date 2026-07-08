from django.shortcuts import render
# Create your views here.
from datetime import date
def employee_form(request):
result = None
if request.method == "POST":
doj = request.POST.get("doj")
if doj:
year, month, day = map(int, doj.split('-'))
joining_date = date(year, month, day)
today = date.today()
experience = (today - joining_date).days / 365
if experience > 5:
result = "YES"
else:
result = "NO"
return render(request, "employee_form.html", {"result": result})
