from django.urls import path
from . import views

urlpatterns = [
    path('', views.OrderFormView.as_view(), name='order_form'),
    path('bill/', views.bill_view, name='bill'),
]
