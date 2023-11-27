import csv
import os
import datetime
x = 1
y = 2
z = 3
mag = 10
hr = 5
timeIndex = -1
ONSET = 6
TST = 10
def inRange(date, start, end):
    if (date >= start) and (date<=end):
        return True
    return False
def am(time):
    if time.hour < 12:
        return 1
    return 0
def timeate(t):
    '''take string in form %H:%M and convert to datetime from 7 jan 2017 assuming anytime past midnight is the next day'''
    secStr = None
    try:
        if t.count(':') == 1:
            hourStr,minuteStr = t.split(':')
        else:
            hourStr,minuteStr,secStr = t.split(':')
    except ValueError:
        input(t)
    time = datetime.time(int(hourStr),int(minuteStr)) if secStr == None else datetime.time(int(hourStr),int(minuteStr),int(secStr))
    return datetime.datetime(2017,1,7+am(time),time.hour,time.minute) 



for i in range(1,23):
    X = []
    Y = []
    j=0
    yTimes = []
    with open(f"user_{i}\\Actigraph.csv",newline='') as csvX:
        with open(f"user_{i}\\sleep.csv",newline='') as csvY:
            inputreader = csv.reader(csvX)
            outputreader = csv.reader(csvY)
            for row in outputreader:
                if j==0:
                    j+=1
                    continue
                startTime = timeate(row[ONSET])
                timeSleeping = datetime.timedelta(minutes=int(row[TST]))
                yTimes.append((startTime, startTime+timeSleeping))
            for row in inputreader:
                if j==1:
                    j+=1
                    continue
                X.append((row[mag],row[hr]))#has to be strings to convert use join
                Y.append(int(any([inRange(timeate(row[timeIndex]), i[0], i[1]) for i in yTimes])))
            csvX.close()
            csvY.close()
    with open(f"users\\user_{i}.txt",'a') as file:
        for ind, x in enumerate(X):
            file.write(f"{Y[ind]} {' '.join(x)}\n")
        file.close()
    print(f"Done with user_{i}")
    


