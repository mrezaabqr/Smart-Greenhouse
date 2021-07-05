import socket
import json
import requests
import time

URL = "http://logansanders233.pythonanywhere.com/"

def get_time(url):
    headers = {'Content-type': 'application/json'}
    resp = requests.get(url, headers=headers)
    print(resp.content)
    return(resp.content)


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 5001)
sock.bind(server_address)
sock.listen(1)
print("Listening for connections")
conn, addr = sock.accept()
with conn:
    print('Connected by', addr)
    while True:
        print(conn.sendall(get_time(URL)))
        # conn.send("12/12/12".encode())    
        time.sleep(50)

        