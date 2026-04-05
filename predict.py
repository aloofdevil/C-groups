import joblib
import sys

model = joblib.load("model.pkl")

# Input from C++
latency = float(sys.argv[1])

# Simple input (no history yet)
prediction = model.predict([[latency, latency, latency]])

print(int(prediction[0]))