# myapp/views.py
import firebase_admin
from firebase_admin import credentials, db
from django.shortcuts import render

# Initialize Firebase
cred = credentials.Certificate('/home/TechAZsure/firebase.json')
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://narbid-agrithon-default-rtdb.asia-southeast1.firebasedatabase.app/'
})

def fetch_data(request):
    ref = db.reference('/')
    data = ref.get()
    return render(request, 'display/data.html', {'data': data})
    return render(request, 'display/data.html', {'data': data})
