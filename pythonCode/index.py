# Install http requester(?)
# python -m pip install requests

import serial
import json
import requests

is_checking_metal = False
URL = "http://192.168.3.100:8080/"
users = []
current_user = {}

def loadUsers():
    response = requests.get(URL + "getUsers")
    return response.json()

users = loadUsers()

def checkUser(n):
    for x in users:
        print(x)
        if (x["number"] == n):
            print("Certo")
            return x
    else:
        return {}


def addVal():
    payload = {"index": current_user["index"], "password": "lixoinatorUser"}
    response = requests.post(URL + "addVal", data=payload)

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
ser.reset_input_buffer()

while True:
	if ser.in_waiting > 0:
		line = ser.readline().decode('utf-8').rstrip()
		print(line)
		current_user = checkUser(int(line))
		print(current_user)
