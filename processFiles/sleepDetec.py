#DEPRECATED, MODEL DEVELOPMENT MOVED TO GOOGLE COLLAB:
#https://colab.research.google.com/drive/1y5ZvU_mxRIWbhpT3GfhnvaB03oL48Xf9?usp=sharing
#join from umich email
import tensorflow as tf 
import numpy as np
import math
import random
from tensorflow.keras import layers

"""for i in range(len(BOD)):
        temp = []
        HR.append(float(BOD[i].split()[-1]))
        X.append(BOD[max(i-12,0):i+1])#for includings readins less than 12 long"""
lst = lambda l:  list(map(float, l.strip().split()[1:]))
stackLen = 12
def getNormX(MAT, IND):
    hrs = []
    for pair in MAT:
        hrs.append(pair[IND])
    mx = max(hrs)
    mn = min(hrs)
    if mx-mn == 0:#only occurs if whole window is full of 0's
        hrs = map(lambda x: 0.0,hrs)
    else:
        hrs = map(lambda x: round((x-mn)/(mx-mn),7),hrs)
    for ind, hr in enumerate(hrs):
        MAT[ind][IND] = hr
    return MAT
        
USERS = 3
Y=[]
X = []
for i in range(1,USERS):
    BOD=[]
    with open(f"schleepData\\users\\user_{i}.txt",'r') as file:
        BOD = file.readlines()
        file.close()
    for j in range(stackLen,len(BOD)):
        temp = BOD[j-stackLen:j]
        dataMat = []
        InpMat = list(map(lst,temp))
        #if int(BOD[i][0])==1: input(InpMat)
        InpMat = getNormX(InpMat,0)
        InpMat = getNormX(InpMat,1)
        for i in InpMat:
            dataMat.append(i[0])
            dataMat.append(i[1])
        X.append(dataMat)
        Y.append(int(BOD[j][0]))

Z = []
for i,x in enumerate(X):
    Z.append([Y[i]]+x)
random.shuffle(Z)
Y=[]
X = []
for i in Z:
    X.append(i[1:])
    Y.append(i[0])

nsamples = len(X)
valRatio = .2
testRatio = .2
tfliteModelName = "sleepDetec"
cModelName = "sleepDetec"

valSplit = int(valRatio * nsamples)
testSplit = int(valSplit + (testRatio*nsamples))
xVal, xTest, xTrain = np.split(X, [valSplit, testSplit])
yVal, yTest, yTrain = np.split(Y, [valSplit, testSplit])
assert(yTrain.size+yTest.size+yVal.size) == nsamples

model = tf.keras.Sequential()
model.add(layers.Dense(16, activation='relu', input_shape=(2*stackLen,)))
model.add(layers.Dense(16, activation='relu'))
model.add(layers.Dense(1))
#op: rmsprop, loss:mae
model.compile(optimizer='adam',loss='bce',metrics=['bce'])

history = model.fit(xTrain, yTrain, epochs=200, batch_size=100,
                        validation_data=(xVal,yVal))
input("Press enter if satisfied: ")
converter = tf.lite.TFLiteConverter.from_keras_model(model)
