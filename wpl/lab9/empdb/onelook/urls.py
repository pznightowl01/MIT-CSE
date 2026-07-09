from django.urls import path
from . import views

urlpatterns = [
    path('', views.insert_works, name='home'),
    path('insert/', views.insert_works, name='insert'),
    path('search/', views.search_company, name='search'),
]
