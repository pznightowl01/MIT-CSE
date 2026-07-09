from django.shortcuts import render
# Create your views here.
def grocery_view(request):
selected_items = []
if request.method == "POST":
items = request.POST.getlist("items")
for i in items:
name, price = i.split("-")
selected_items.append((name, price))
return render(request, "grocery.html", {
"selected_items": selected_items
})
