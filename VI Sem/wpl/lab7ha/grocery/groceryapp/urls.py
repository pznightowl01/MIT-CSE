from django.urls import path
from . import views
urlpatterns = [
path('', views.grocery_view),
]
