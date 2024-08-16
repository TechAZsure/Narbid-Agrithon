import RPi.GPIO as GPIO
from RF24 import *
import firebase_admin
from firebase_admin import credentials, db
from datetime import datetime

radio = RF24(17, 0)
address = b'00001'
radio.openReadingPipe(1, address)
radio.startListening()

cred = credentials.Certificate("firebase.json")
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://narbid-agrithon-default-rtdb.asia-southeast1.firebasedatabase.app/'
})

ref = db.reference('/')

while True:
    if radio.available():
        receivedMessage = []
        radio.read(receivedMessage, radio.getDynamicPayloadSize())

        now = datetime.now()
        date = now.strftime("Y-%m-%d")
        time str = now.strftime("%H:%M:%S")

        data = {
            'temperature': receivedMessage[0],
            'humidity': receivedMessage[1],
            'soil_moisture': receivedMessage[2],
            'npk_value': receivedMessage[3],
            'ph_value': receivedMessage[4],
            'water_level': receivedMessage[5]
        }
        ref.child(date).child(time_str).set(data)
