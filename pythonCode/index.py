# Install http requester(?)
# python -m pip install requests

import json
import requests

URL = "http://localhost:8080/"
users = []
current_user = {}

def loadUsers():
    response = requests.get(URL + "getUsers")
    return response.json()

users = loadUsers()

def checkUser():
    n = input("Numero do user")
    for x in users:
        if (x["number"] == n):
            print("Certo")
            return x
    else:
        return {}

current_user = checkUser()

def addVal():
    payload = {"index": current_user["index"], "password": "lixoinatorUser"}
    response = requests.post(URL + "addVal", data=payload)

addVal()