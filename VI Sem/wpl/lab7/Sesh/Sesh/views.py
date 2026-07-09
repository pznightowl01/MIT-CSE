from django.shortcuts import render, redirect

# Create your views here.

def pg1(request):
    if request.method == 'POST':
        name = request.POST.get('name')
        seat = request.POST.get('seat')
        destination = request.POST.get('destination')

        request.session['name'] = name
        request.session['seat'] = seat
        request.session['destination'] = destination

        return redirect('pg2')

    return render(request, 'pg1.html')


def pg2(request):
    name = request.session.get('name')
    seat = request.session.get('seat')
    destination = request.session.get('destination')

    context = {
        'name': name,
        'seat': seat,
        'destination': destination
    }

    return render(request, 'pg2.html', context)
