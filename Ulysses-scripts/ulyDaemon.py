"""
Created by Edson Silva in 26/12/2023
script for running background service that 
executes functions for Ulysses App
"""

dataPath = "../ulysses_conf/"
dataFile = "testfile.json"
path = dataPath + dataFile

import json
import subprocess
import sys
import os
import webbrowser
from datetime import datetime, timedelta

startupEvents = []
todaysEvents = []

def notify(message):

    # if windows
    # TODO: add windows notification code

    # if UBUNTU : 
    if sys.platform.startswith('linux'):
        subprocess.Popen(['notify-send', 'Ulysses Task Notification', message])
    if sys.platform.startswith('cygwin') or sys.platform.startswith('win32'):
        # do something
        pass

def executeEvents(events):
    # given a list of events, run them
    for event in events:
        if event['type'] == 'link':
            webbrowser.open(event['path'])
        if event['type'] == 'script_shell':
            script = event['path']
            args = ' '.join(event['args'])
            os.system(f"gnome-terminal -e 'bash -c \"sh {script} {args}; exec bash\"'")

        if event['type'] == 'script_python':
            script = event['path']
            args = ' '.join(event['args'])
            os.system(f"gnome-terminal -e 'bash -c \"python3 {script} {args}; exec bash\"'")


# organize list of events so we have a sublist for
# startup events and another for events that will trigger today
# to decrease number of operations
def organizeEvents():
    # Get the current date
    current_date = datetime.now()

    # Get the day of the week
    weekday = current_date.strftime("%A")

    try:
        events = getEvents()
        for event in events:
            if event['startupmode'] == 'atStartup':
                startupEvents.append(event)
                print("organized startup event")
            if event['startupmode'] == 'date': # scheduled event, compare with todays date
                if weekday in event['days']:
                    todaysEvents.append(event)
                    print("organized today event")

    except ValueError as error:
        print(error)

def checkTasks():
    # here check tasks for notification or execution conditions
    # like startup or schedule
    current_date = datetime.now()
    # check todays events for those that could be close to the current time
    closeEvents = []
    executeNowEvents = []

    for event in todaysEvents:
        timestr = event['time']
        eventime = datetime.strptime(timestr, "%I:%M %p")
        eventime = eventime.replace(year=current_date.year, month=
                                    current_date.month, day=current_date.day)

        print(eventime)
        if(current_date < eventime):
            # event has not yet passed, check how much time until it should trigger
            delta = eventime - current_date
        else:
            continue

        #  5 mins => delta > 4 mins 
        if delta <= timedelta(minutes=5) and delta > timedelta(minutes=4):
            closeEvents.append(event) # those events will be notified as close to execution to user

        if delta <= timedelta(minutes=1):
            executeNowEvents.append(event) # those events will be executed

    # notify user of upcoming events
    if(len(closeEvents) > 1):
        notify(f"{len(closeEvents)} starting in 5 minutes")
    elif(len(closeEvents) == 1):
        name = closeEvents[0]['name']
        notify(f"{name} starting in 5 minutes")

    return executeNowEvents


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

    if not data:
        raise ValueError("no data available")

    # example event
    for data_event in data:
        print(data_event)

    return data

getEvents()
organizeEvents()
executeEvents(checkTasks())

