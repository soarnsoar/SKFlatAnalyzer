import numpy as np
import tensorflow as tf
from tensorflow.keras.models import load_model
from tensorflow.keras.optimizers import Nadam


model = load_model("TrainedModel_DNN.h5", compile=False)
optimizer = Nadam(learning_rate=0.002, beta_1=0.9, beta_2=0.999, epsilon=None)

dummy_input=np.array([[0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.8,0.7,0.6,0.5]])
a = model.predict(dummy_input)

##Add fix for some batchnorm init..(i dont know the details 
for layer in model.layers:
    layer.trainable = False
    layer._training = False
    if isinstance(layer, tf.keras.layers.BatchNormalization):
        #layer.build(input_shape=(None, *layer.input_shape[1:])) ##prediction is changed
        #print("gamma")
        #print(layer.gamma)
        #print("beta")
        #print(layer.beta)
        layer.gamma.assign(layer.gamma)
        layer.beta.assign(layer.beta)
        

        #model.layers.remove(layer) ## prediction is changed
    elif isinstance(layer, tf.keras.layers.Dense):
        layer.kernel.assign(layer.kernel)
        layer.bias.assign(layer.bias)
        
model.build(model.input_shape)

model.compile(loss="categorical_crossentropy", optimizer=optimizer, metrics=["accuracy"])



dummy_input=np.array([[0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.8,0.7,0.6,0.5]])
a = model.predict(dummy_input)


model.summary()

model.save("Converted_model.h5")



print(a)
