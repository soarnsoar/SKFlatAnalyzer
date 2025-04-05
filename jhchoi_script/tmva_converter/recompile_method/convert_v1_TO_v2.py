import numpy as np
import tensorflow as tf
from tensorflow.keras.models import load_model
from tensorflow.keras.optimizers import Nadam
import os
import glob
import sys



def Convert(inputpath):


    dummy_input1=[0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.8,0.7,0.6,0.5]
    


    ##---For backup---##
    if not os.path.isfile(inputpath+"__v1.h5"):
        os.system("cp "+inputpath+" "+inputpath+"__v1.h5")
    else:
        print("Use backup file->",inputpath+"__v1.h5")
        os.system("cp "+inputpath+"__v1.h5 "+inputpath)

    ##--load model
    model = load_model(inputpath,compile=False)

    ##---Make dummy input with proper inputsize
    print(model.input_shape)
    model_inputsize=model.input_shape[1]
    print("model input size=",model_inputsize)
    
    dummy_list=[]
    for i in range(model_inputsize): 
        dummy_list.append(dummy_input1[i])

    dummy_input=np.array([dummy_list])

    ##---calc prediction 
    a = model.predict(dummy_input)
    print(a)

    ##---define optimizer
    #optimizer = Nadam(learning_rate=0.002, beta_1=0.9, beta_2=0.999, epsilon=None)
    #optimizer=tf.keras.optimizers.Adam() ## for compatibility




    for layer in model.layers:
        continue
        ##---No training
        #layer.trainable = False
        #layer._training = False

        if isinstance(layer, tf.keras.layers.BatchNormalization):
            ##assign once explicitly
            layer.gamma.assign(layer.gamma)
            layer.beta.assign(layer.beta)            
            layer.moving_mean.assign(layer.moving_mean.numpy())
            layer.moving_variance.assign(layer.moving_variance.numpy())
            layer.trainable = False
            layer._training = False
            True
            
        elif isinstance(layer, tf.keras.layers.Dense):
            layer.kernel.assign(layer.kernel)
            layer.bias.assign(layer.bias)
            layer.trainable = False
            layer._training = False
            True

    
    #model.compile(loss="categorical_crossentropy", optimizer=optimizer, metrics=["accuracy"])
    model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])

    ##---To make mean/variance of this model features
    
    a = model.predict(dummy_input)
    print(a)

    model.summary()

        
    savepath=inputpath+"__v2.h5"
    model.save(savepath)

    os.system("cp "+savepath+" "+inputpath)

    a = model.predict(dummy_input)
    print(a)


if __name__ == '__main__':


    inputpath=sys.argv[1]
    Convert(inputpath)
    
