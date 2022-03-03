"""Dobre Adriana Lia, Guțu Ștefania Alexandra, Pirlogea Luciana Elena, grupa 141
~ Lab 4.1 ~
Folosirea expresiilor regulate pentru a extrage link-urile dintr-o pagina web"""

import sys
import urllib.request, urllib.error, urllib.parse
import re

url = sys.argv[1]

try:
    response = urllib.request.urlopen(url)
    webContent = response.read()
    print(webContent)
except:
    print("Error")
webContent = str(webContent)

def find_url(string):
    #regex = r"(?i)\b((?:https?://|www\d{0,3}[.]|[a-z0-9.\-]+[.][a-z]{2,4}/)(?:[^\s()<>]+|\(([^\s()<>]+|(\([^\s()<>]+\)))*\))+(?:\(([^\s()<>]+|(\([^\s()<>]+\)))*\)|[^\s`!()\[\]{};:'\".,<>?«»“”‘’]))" ->varianta inspirata de pe internet
    #regex="href\s*=\s*\"(.*?)\""
    regex="href=\"(.*?)\""
    url = re.findall(regex, string)
    for x in url:
        print(x[0])
    print(len(url)) # afisam numarul link-urilor extrase

find_url(webContent)