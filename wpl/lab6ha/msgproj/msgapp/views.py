from django.shortcuts import render
from django.http import HttpResponse
def message_view(request):
output = ""
style = ""
if request.method == "POST":
action = request.POST.get("action")
if action == "Exit":
return HttpResponse("Application Closed")
if action == "Clear":
return render(request, "message.html")
name = request.POST.get("name", "")
message = request.POST.get("message", "")
output = name + " " + message
color = request.POST.get("color")
if color:
style += "color:" + color + ";"
if request.POST.get("bold"):
style += "font-weight:bold;"
if request.POST.get("italic"):
style += "font-style:italic;"
if request.POST.get("underline"):
style += "text-decoration:underline;"
return render(request, "message.html", {
"output": output,
"style": style
})
