from django.shortcuts import render
# Create your views here.
import random
import string
def captcha_view(request):
if 'attempts' not in request.session:
request.session['attempts'] = 0
if 'captcha' not in request.session:
request.session['captcha'] = ''.join(
random.choices(string.ascii_uppercase + string.digits, k=5)
)
message = ""
disabled = False
if request.method == "POST":
user_input = request.POST.get("usercaptcha")
actual_captcha = request.session['captcha']
if user_input == actual_captcha:
message = "Captcha Matched Successfully"
request.session['attempts'] = 0
request.session['captcha'] = ''.join(
random.choices(string.ascii_uppercase + string.digits, k=5)
)
else:
request.session['attempts'] += 1
message = "Captcha Mismatch"
if request.session['attempts'] >= 3:
message = "Too many attempts. TextBox Disabled."
disabled = True
return render(request, "captcha.html", {
"captcha": request.session['captcha'],
"message": message,
"disabled": disabled
})
