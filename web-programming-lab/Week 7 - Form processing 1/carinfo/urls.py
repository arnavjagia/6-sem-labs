from django.urls import path
from . import views

urlpatterns = [
    path('', views.car_form_view, name='car_form'),
    path('result/<str:manufacturer>/<str:model>/', views.car_result_view, name='car_result'),
]