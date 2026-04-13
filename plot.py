import pandas as pd
import matplotlib.pyplot as plt

# ================= LOAD DATA =================
normal = pd.read_csv("normal_log.csv")
v1 = pd.read_csv("v1_log.csv")
v2 = pd.read_csv("v2_log.csv")
ml = pd.read_csv("ml_log.csv")

# ================= GRAPH 1: ML LATENCY =================
plt.figure()
plt.plot(ml['request'], ml['latency'])
plt.title("ML: Latency vs Request")
plt.xlabel("Request")
plt.ylabel("Latency")
plt.savefig("ml_latency.png")

# ================= GRAPH 2: V1 vs V2 vs ML =================
plt.figure()
plt.plot(v1['request'], v1['latency'], label="V1")
plt.plot(v2['request'], v2['latency'], label="V2")
plt.plot(ml['request'], ml['latency'], label="ML")

plt.legend()
plt.title("Final Comparison: V1 vs V2 vs ML")
plt.xlabel("Request")
plt.ylabel("Latency")

plt.savefig("final_comparison.png")

# ================= GRAPH 3: AVERAGE LATENCY =================
avg = [
    normal['latency'].mean(),
    v1['latency'].mean(),
    v2['latency'].mean(),
    ml['latency'].mean()
]

labels = ["Normal", "V1", "V2", "ML"]

plt.figure()
plt.bar(labels, avg)
plt.title("Average Latency Comparison")
plt.savefig("avg_latency.png")

# ================= PRINT VALUES =================
print("\n===== AVERAGE LATENCIES =====")
print("Normal:", normal['latency'].mean())
print("V1:", v1['latency'].mean())
print("V2:", v2['latency'].mean())
print("ML:", ml['latency'].mean())

# ================= OPTIONAL: PRESSURE COMPARISON =================
# Only works if columns exist

if 'pressure' in v2.columns and 'predicted_pressure' in ml.columns:
    plt.figure()
    plt.plot(v2['pressure'], label="V2 Pressure")
    plt.plot(ml['predicted_pressure'], label="ML Predicted")

    plt.legend()
    plt.title("Pressure Prediction vs Actual")
    plt.savefig("pressure_compare.png")

print("\nGraphs generated successfully!")