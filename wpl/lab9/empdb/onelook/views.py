from django.shortcuts import render
from .models import Works, Lives
from .forms import WorksForm, CompanyForm

# Create your views here.

def insert_works(request):
    form = WorksForm()
    success = False

    if request.method == 'POST':
        form = WorksForm(request.POST)
        if form.is_valid():
            Works.objects.create(
                person_name=form.cleaned_data['person_name'],
                company_name=form.cleaned_data['company_name'],
                salary=form.cleaned_data['salary']
            )
            success = True
            form = WorksForm()

    return render(request, 'insert.html', {'form': form, 'success': success})

def search_company(request):
    form = CompanyForm()
    results = []
    if request.method == 'POST':
        form = CompanyForm(request.POST)
        if form.is_valid():
            cname = form.cleaned_data['company_name']
            works = Works.objects.filter(company_name=cname)
            for w in works:
                lives = Lives.objects.filter(person_name=w.person_name).first()
                if lives:
                    results.append((w.person_name, lives.city))
    return render(request, 'search.html', {'form': form, 'results': results})
