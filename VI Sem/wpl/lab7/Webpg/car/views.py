from django.shortcuts import render

# Create your views here.

def car(request):
    return render(request, 'car.html')

def car2(request):
    if request.method == 'POST':
        manufacturer = request.POST.get('manufacturer')
        model = request.POST.get('model')

        context = {
            'manufacturer': manufacturer,
            'model': model
        }
        return render(request, 'car2.html', context)

    return render(request, 'car.html')
