from django.urls import path

from . import views

app_name = "captcha"

urlpatterns = [
    path("", views.captcha_view, name="captcha"),
]
