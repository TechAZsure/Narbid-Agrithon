from django.contrib import admin
from django.urls import path
from display.views import fetch_data

urlpatterns = [
    path('admin/', admin.site.urls),
    path('display/', fetch_data, name='fetch_data'),
]
