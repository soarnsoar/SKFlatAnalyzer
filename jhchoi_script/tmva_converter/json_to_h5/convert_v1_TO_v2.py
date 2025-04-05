import tensorflow.compat.v1 as tf
tf.disable_v2_behavior()
tf.disable_eager_execution()
from tensorflow.keras.layers import BatchNormalization
from tensorflow import keras
import numpy as np


import os
import glob
import sys



def Convert(inputpath):


    dummy_input1=[0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.8,0.7,0.6,0.5]
    dummy_input1=[0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.]
    


    ##---For backup---##
    if not os.path.isfile(inputpath+"__v1.h5"):
        os.system("cp "+inputpath+" "+inputpath+"__v1.h5")
    else:
        print("Use backup file->",inputpath+"__v1.h5")
        os.system("cp "+inputpath+"__v1.h5 "+inputpath)

    ##--load model
    model = tf.keras.models.load_model(inputpath)

    ##---Make dummy input with proper inputsize
    print(model.input_shape)
    model_inputsize=model.input_shape[1]
    print("model input size=",model_inputsize)
    
    dummy_list=[]
    for i in range(model_inputsize): 
        dummy_list.append(dummy_input1[i])

    dummy_input=np.array([dummy_list])

    ##--conver to json
    model_json = model.to_json()
    with open("model.json", "w") as json_file:
        print("write->model.json")
        json_file.write(model_json)

    model.save_weights("weights.h5")
    with open("model.json", "r") as json_file:
        print("write->model.json")
        loaded_model_json = json_file.read()

    loaded_model = keras.models.model_from_json(loaded_model_json)
    loaded_model.load_weights("weights.h5",by_name=True)

    loaded_model.compile()
    for layer in loaded_model.layers:
        continue
        if isinstance(layer, BatchNormalization):
            layer.trainable = False

    
    a = loaded_model.predict(dummy_input)
    print(a)    


    model.summary()

        
    savepath=inputpath+"__v2.h5"
    #model.save(savepath)
    loaded_model.save(savepath)
    
    os.system("cp "+savepath+" "+inputpath)

    a = model.predict(dummy_input)
    print(a)


if __name__ == '__main__':


    inputpath=sys.argv[1]
    Convert(inputpath)
    
