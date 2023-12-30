"""
Created by Edson Silva in 26/12/2023
script for running background service that 
executes functions for Ulysses App
"""

dataPath = "../ulysses_conf/"
dataFile = "testfile.json"

import json
import subprocess
import sys

def notify(message):

    # if windows
    # TODO: add windows notification code

    # if UBUNTU : 
    if sys.platform.startswith('linux'):
        subprocess.Popen(['notify-send', 'Ulysses Task Notification', message])
    if sys.platform.startswith('cygwin') or sys.platform.startswith('win32'):
        # do something
        pass

def checkTasks():
    # here check tasks for notification or execution conditions
    # like startup or schedule
    pass

def getEvents():
    # extract json objects and create a dict list for 
    # the corresponding events
    path = dataPath + dataFile
    data = ''
    try:
        with open(path, 'r') as f:
            data = json.load(f)
    except FileNotFoundError:
        print("could not open files")
        notify("could not open files")

    # example event
    for data_event in data:
        print(data_event['name'])

getEvents()
#notify('task 4 is starting in 5 minutes')

