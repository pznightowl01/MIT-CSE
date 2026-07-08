from django.urls import path
from . import views
urlpatterns = [
path('', views.home),
path('bookdata/', views.bookdata),
path('reviews/', views.reviews),
path('publisher/', views.publisher),
]
