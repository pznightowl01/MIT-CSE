from django.urls import path
from . import views

urlpatterns = [
    path('', views.car, name='car'),
    path('car2/', views.car2, name='car2'),
]
