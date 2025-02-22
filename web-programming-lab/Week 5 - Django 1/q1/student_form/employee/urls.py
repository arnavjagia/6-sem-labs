from django.conf.urls import url
from . import views

urlpatterns = [
    url(r'^$', views.check_eligibility, name='check_eligibility'),
]
