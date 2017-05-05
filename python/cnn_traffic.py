#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue May  2 16:40:18 2017

@author: kc099
"""

import numpy as np
import scipy.misc
import pickle
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import Dropout
from keras.layers import Flatten
from keras.layers.convolutional import Conv2D
from keras.layers.convolutional import MaxPooling2D
from keras.utils import np_utils
from keras import backend as K
from skimage import exposure
K.set_image_dim_ordering('th')

ftrain = 'train.p'
ftest = 'test.p'

def preprocess_dataset(X, y = None):
    #Convert to grayscale, e.g. single Y channel
    X = 0.299 * X[:, :, :, 0] + 0.587 * X[:, :, :, 1] + 0.114 * X[:, :, :, 2]
    #Scale features to be in [0, 1]
    X = (X / 255.).astype(np.float32)
      
    # Apply localized histogram localization  
#    for i in range(X.shape[0]):
#        X[i] = exposure.equalize_adapthist(X[i])
        
    if y is not None:  
        # Convert to one-hot encoding. Convert back with `y = y.nonzero()[1]`
        y = np.eye(43)[y]
        # Shuffle the data
#        X, y = shuffle(X, y)

    # Add a single grayscale channel
    X = X.reshape(X.shape + (1,)) 
    return X, y

with open(ftrain, 'rb') as f:
    x = pickle.load(f)
    
features = np.asarray(x['features'])
labels = np.asarray(x['labels'])
coords = np.asarray(x['coords'])
sizes = np.asarray(x['sizes'])

#take selected images as features
c1_fea = features[210:2430]
c1_labels = labels[210:2430]
c1_size = sizes[210:2430]
c1_coords = coords[210:2430]

c3_fea = features[2430:4680]
c3_labels = labels[2430:4680]
c3_size = sizes[2430:4680]
c3_coords = coords[2430:4680]

c4_fea = features[6090:8070]
c4_labels = labels[6090:8070]
c4_size = sizes[6090:8070]
c4_coords = coords[6090:8070]

c5_fea = features[18000:20100]
c5_labels = labels[18000:20100]
c5_size = sizes[18000:20100]
c5_coords = coords[18000:20100]

c6_fea = features[20100:22260]
c6_labels = labels[20100:22260]
c6_size = sizes[20100:22260]
c6_coords = coords[20100:22260]


#convert images to gray scale
fea_new,ynew=preprocess_dataset(c1_fea,None)
fea3_new,ynew=preprocess_dataset(c3_fea,None)
fea4_new,ynew=preprocess_dataset(c4_fea,None)
fea5_new,ynew=preprocess_dataset(c5_fea,None)
fea6_new,ynew=preprocess_dataset(c6_fea,None)

#reshape the images
X_valid1 = fea_new.reshape(fea_new.shape[0], 1, 32, 32).astype('float32')
X_valid3 = fea3_new.reshape(fea3_new.shape[0], 1, 32, 32).astype('float32')
X_valid4 = fea4_new.reshape(fea4_new.shape[0], 1, 32, 32).astype('float32')
X_valid5 = fea5_new.reshape(fea5_new.shape[0], 1, 32, 32).astype('float32')
X_valid6 = fea6_new.reshape(fea6_new.shape[0], 1, 32, 32).astype('float32')
#
#
X_valid = np.concatenate((X_valid1,X_valid3,X_valid4,X_valid5,X_valid6))
#
label1 = 0*np.ones(len(X_valid1));
label2 = 1*np.ones(len(X_valid3));
label3 = 2*np.ones(len(X_valid4));
label4 = 3*np.ones(len(X_valid5));
label5 = 4*np.ones(len(X_valid6));
#                  
y_validset = np.concatenate((label1,label2,label3,label4,label5))
#                  
#
y = np_utils.to_categorical(y_validset)           
           
num_classes = 5           
    
    
def baseline_model():
	# create model
	model = Sequential()
	model.add(Conv2D(3, (5, 5), input_shape=(1,32, 32), activation='relu'))
	model.add(MaxPooling2D(pool_size=(2, 2)))
#	model.add(Dropout(0.2))
	model.add(Flatten())
	model.add(Dense(20,activation='relu'))
	model.add(Dense(num_classes, activation='softmax'))
#	Compile model
	model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
	return model


# build the model
model = baseline_model()

# Fit the model
model.fit(X_valid, y, epochs=100, batch_size=500, verbose=2,validation_split=0.1)    

scores = model.evaluate(X_valid, y, verbose=0)
print("Baseline Error: %.2f%%" % (100-scores[1]*100))


for layer in model.layers:
    weights = layer.get_weights()   
#    
i=0
h=['0','0','0','0','0','0']

#print weight matrices
for layer in model.layers:
    g=layer.get_config()
    h[i]=layer.get_weights()  
    i+=1
    
    
    
    
    
    
    
    
    
