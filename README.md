# Get A Shell

-   הפרויקט הוא כלי לניטור פעילות מחשבים ברשת ומתן תמיכה טכנית בסיסית מרחוק.
    
-   מורכב מתוכנת מעקב שניתן להריץ על כל מחשב וממשק WEB אינטראקטיבי
- קטע מהמחקר שלי על הסלמת ההרשאות:
##### UAC Bypass by /System32 Directory Mocking using Taskmgr.exe and Winsta.dll

[https://youtu.be/QojO44FSQfQ](/eyalasulin.9/windows-10-local-privilege-escalation/-/blob/master/url)

An UAC bypassing on Windows available for applications that:

1.  Configured for Auto Elevation.
2.  Properly Signed.
3.  Executed from a trusted directory.

My application based on the third method, executing from trusted directory. No privilges needed to run applications from the mock directory, and this is how we exploit it. Execute an known application from System32 throutgh mock directory, and loading a malicious dll library (DLL Search Order Exploiting). I found Taskmgr.exe vulnerable for this dll hijacking (last check 01/02/2021). Written in C++ and WinAPI.

**Exploit Method:**

1.  Creating Mock Directory of System32
2.  Download Taskmgr.exe and my malicious Winsta.dll from server _[git]_.
3.  Execute Taskmgr.exe that calls for the malicious dll library.
4.  A elevated cmd shell prompt opened up.

**Usage:** just execute "Privilege Escalation UAC Bypass.exe", no compiling needed. All required files will downloaded automatically from the repository.

Current Winsta.dll is just opens a shell prompt, you can edit and recompile it to do whatever you want. [https://youtu.be/QojO44FSQfQ](/eyalasulin.9/windows-10-local-privilege-escalation/-/blob/master/url)

מדריך להרצה של המערכת:
להרצת השרת על סביבת ווינדווס יש להריץ את הקובץ run_server.bat 
והוא לבד יתאים הכל לסביבת הרצה מתאימה (ספריות, משתני סביבה וקריאה לריצת התכנית)

להרצת הלקוח-תוכנת מעקב רק נדרש להריץ את הקובץ Client.exe
