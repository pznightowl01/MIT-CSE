from django.urls import path
from . import views

urlpatterns = [
    path('', views.home),
    path('addc/', views.addc),
    path('addpg/', views.addpg),
]
