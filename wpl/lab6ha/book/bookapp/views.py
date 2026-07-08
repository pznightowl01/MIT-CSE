from django.shortcuts import render
def home(request):
return render(request, "home.html")
def bookdata(request):
return render(request, "bookdata.html")
def reviews(request):
return render(request, "reviews.html")
def publisher(request):
return render(request, "publisher.html")
