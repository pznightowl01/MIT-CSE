from django.shortcuts import render
from .models import Institutes


def display_institutes(request):
    institutes = Institutes.objects.all()
    return render(request, 'courses/display.html', {'institutes': institutes})
