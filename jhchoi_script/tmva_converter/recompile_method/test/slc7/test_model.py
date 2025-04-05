import tensorflow as tf
import numpy as np

import sys

model_path=sys.argv[1]
#model_path = "TrainedModel_DNN.h5"
#model_path = "model.h5"

model = tf.keras.models.load_model(model_path)


input_shape = model.input_shape[1:]

#dummy_input = np.random.rand(1, *input_shape)
dummy_input = np.zeros((1, 13))
#dummy_input = np.ones((1, 13))
#print dummy_input

#dummy_input=np.array([[0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.8,0.7,0.6,0.5]])


prediction = model.predict(dummy_input)


print("Model Output:", prediction)
