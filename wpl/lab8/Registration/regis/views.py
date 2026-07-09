from django.shortcuts import render, redirect

# Create your views here.

def register(request):
    if request.method == "POST":
        username = request.POST.get('username')
        password = request.POST.get('password')
        email = request.POST.get('email')
        contact = request.POST.get('contact')

        if not username:
            return render(request, 'pg1.html', {'error': 'Username is required'})

        request.session['username'] = username
        request.session['email'] = email
        request.session['contact'] = contact

        return redirect('success')

    return render(request, 'pg1.html')


def success(request):
    return render(request, 'pg2.html', {
        'username': request.session.get('username'),
        'email': request.session.get('email'),
        'contact': request.session.get('contact'),
    })
