import tensorflow as tf
from tensorflow.keras.models import load_model
from tensorflow.keras.optimizers import Nadam


model = load_model("model.h5", compile=False)
optimizer = Nadam(learning_rate=0.002, beta_1=0.9, beta_2=0.999, epsilon=None)

model.compile(loss="categorical_crossentropy", optimizer=optimizer, metrics=["accuracy"])

model.save("Converted_model.h5")
