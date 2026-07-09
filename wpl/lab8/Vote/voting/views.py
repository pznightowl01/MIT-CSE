from django.shortcuts import render

# Create your views here.

votes = {
    'good': 0,
    'satisfactory': 0,
    'bad': 0
}

def vote(request):
    return render(request, 'pg1.html')

def result(request):
    return render(request, 'pg2.html')
