import pandas as pd
import matplotlib.pyplot as plt

# Load data
normal = pd.read_csv("normal_log.csv")
v1 = pd.read_csv("v1_log.csv")
v2 = pd.read_csv("v2_log.csv")

# -------- GRAPH 1: Latency vs Request --------
plt.figure()
plt.plot(normal['request'], normal['latency'])
plt.title("Normal: Latency vs Request")
plt.xlabel("Request")
plt.ylabel("Latency")
plt.savefig("normal_latency.png")

# -------- GRAPH 2: V1 vs V2 Comparison --------
plt.figure()
plt.plot(v1['request'], v1['latency'], label="V1")
plt.plot(v2['request'], v2['latency'], label="V2")
plt.legend()
plt.title("V1 vs V2 Latency")
plt.xlabel("Request")
plt.ylabel("Latency")
plt.savefig("v1_v2_latency.png")

# -------- GRAPH 3: Pressure Events --------
plt.figure()
plt.plot(v2['request'], v2['pressure'])
plt.title("Memory Pressure Events (V2)")
plt.xlabel("Request")
plt.ylabel("Pressure")
plt.savefig("pressure.png")

# -------- GRAPH 4: Average Latency --------
avg = [
    normal['latency'].mean(),
    v1['latency'].mean(),
    v2['latency'].mean()
]

labels = ["Normal", "V1", "V2"]

plt.figure()
plt.bar(labels, avg)
plt.title("Average Latency Comparison")
plt.savefig("avg_latency.png")

print("Graphs generated successfully!")