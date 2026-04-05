import pandas as pd
import matplotlib.pyplot as plt

# Load data
normal = pd.read_csv("normal_log.csv")
v1 = pd.read_csv("v1_log.csv")
v2 = pd.read_csv("v2_log.csv")
ml = pd.read_csv("ml_log.csv")   # 🔥 ADD THIS

# -------- GRAPH 1: Latency vs Request (ML) --------
plt.figure()
plt.plot(ml['request'], ml['latency'])
plt.title("ML: Latency vs Request")
plt.xlabel("Request")
plt.ylabel("Latency")
plt.savefig("ml_latency.png")

# -------- GRAPH 2: V1 vs V2 vs ML --------
plt.figure()
plt.plot(v1['request'], v1['latency'], label="V1")
plt.plot(v2['request'], v2['latency'], label="V2")
plt.plot(ml['request'], ml['latency'], label="ML")   # 🔥 ADD THIS
plt.legend()
plt.title("V1 vs V2 vs ML Latency")
plt.xlabel("Request")
plt.ylabel("Latency")
plt.savefig("comparison.png")

# -------- GRAPH 3: Average Latency --------
avg = [
    normal['latency'].mean(),
    v1['latency'].mean(),
    v2['latency'].mean(),
    ml['latency'].mean()   # 🔥 ADD THIS
]

labels = ["Normal", "V1", "V2", "ML"]

plt.figure()
plt.bar(labels, avg)
plt.title("Average Latency Comparison")
plt.savefig("avg_latency.png")

print("ML graphs generated successfully!")