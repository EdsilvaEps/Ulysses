"""
Created by Edson Silva in 21/08/2022
initial script for executing programs
and urls on certain schedules and days
"""

import subprocess
import webbrowser

# opens an url on default web browser
def openBrowserUrl(url):
    webbrowser.open(url)

url = "https://www.geeksforgeeks.org"

openBrowserUrl(url)