from django.shortcuts import render, redirect
from .models import Category, Page
from .forms import CategoryForm, PageForm
# Create your views here.

def home(request):
    categories = Category.objects.all()
    pages = Page.objects.all()
    return render(request, 'direc/home.html', {'categories': categories, 'pages': pages})


def addc(request):
    form = CategoryForm()
    if request.method == 'POST':
        form = CategoryForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('/')
    return render(request, 'direc/addc.html', {'form': form})


def addpg(request):
    form = PageForm()
    if request.method == 'POST':
        form = PageForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('/')
    return render(request, 'direc/addpg.html', {'form': form})
