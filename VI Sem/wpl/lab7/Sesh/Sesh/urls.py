from django.urls import path
from . import views

urlpatterns = [
    path('', views.pg1, name='pg1'),
    path('pg2/', views.pg2, name='pg2'),
]
