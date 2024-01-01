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
from datetime import datetime

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
            if event['startupmode'] == 'date': # scheduled event, compare with todays date
                if weekday in event['days']:
                    todaysEvents.append(event)

    except ValueError as error:
        print(error)

def checkTasks():
    # here check tasks for notification or execution conditions
    # like startup or schedule
    current_date = datetime.now()
    # check todays events for those that could be close to the current time
    for event in todaysEvents:
        timestr = event['time'][0:5]
        eventime = datetime.strptime(timestr, "%H:%M")
        print(eventime)
        # TODO:compare only hours/minutes, otherwise larger aspects (years, months) will affect comparison
        if(current_date > eventime):
            print("event time has already passed")

            delta = current_date - eventime
            print(delta)
            continue
        else:
            delta = eventime -  current_date
            print(delta)


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
checkTasks()

