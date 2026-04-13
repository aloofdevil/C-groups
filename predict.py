import os
import sys
import joblib
import pandas as pd

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
model_path = os.path.join(BASE_DIR, "model.pkl")

model = joblib.load(model_path)

latency = float(sys.argv[1])
prev1 = float(sys.argv[2]) if len(sys.argv) > 2 else latency
prev2 = float(sys.argv[3]) if len(sys.argv) > 3 else latency

input_data = pd.DataFrame([[latency, prev1, prev2]],
                          columns=['latency', 'latency_prev1', 'latency_prev2'])

prediction = model.predict(input_data)

print(int(prediction[0]))