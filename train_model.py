import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report
import joblib

# Load data
data = pd.read_csv("v2_log.csv")

# 🔥 Add history features
data['latency_prev1'] = data['latency'].shift(1)
data['latency_prev2'] = data['latency'].shift(2)
data = data.dropna()

# Features
X = data[['latency', 'latency_prev1', 'latency_prev2']]
y = data['pressure']

# Split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)

# Train
model = RandomForestClassifier(n_estimators=100)
model.fit(X_train, y_train)

# Evaluate
y_pred = model.predict(X_test)
print("Accuracy:", accuracy_score(y_test, y_pred))
print(classification_report(y_test, y_pred))

# 🔥 Save model
joblib.dump(model, "model.pkl")
print("Model saved as model.pkl")