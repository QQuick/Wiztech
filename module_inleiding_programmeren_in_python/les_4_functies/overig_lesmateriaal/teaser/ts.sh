transcrypt -n -p .user mondrian.py 
python -m http.server &
chromium http://localhost:8000/mondrian.html
