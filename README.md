# ✈️ Spatio-Temporal Route Optimizer

A **C++ based multi-criteria route optimization system** that uses **Graph Traversal** and **Constraint-Aware Depth First Search (DFS)** to find optimal flight routes.

---

## 🚀 Features

- 🗺️ **Graph-based representation** of a flight network
- 🔍 **Depth First Search (DFS)** for route exploration
- 🛣️ Discovery of **multiple routes** between source and destination
- 🔄 **Cycle prevention** using visited-path checking
- ⚡ **Constraint-aware DFS traversal**
- ✂️ **Early pruning** of invalid routes
- 💰 **Maximum budget constraint**
- ⏱️ **Maximum travel time constraint**
- ✈️ **Maximum flight count constraint**
- 💸 **Cheapest route optimization**
- ⚡ **Fastest route optimization**
- 🛫 **Minimum flights optimization**
- ⚖️ **Balanced multi-objective optimization**

---

## 🎯 Optimization Criteria

The system provides **four optimization strategies**:

### 💰 1. Cheapest Route

Minimizes the **total travel fare**.

### ⏱️ 2. Fastest Route

Minimizes the **total travel time**.

### ✈️ 3. Minimum Flights

Minimizes the **number of flights required**.

### ⚖️ 4. Balanced Route

Considers **fare, travel time, and number of flights** using a weighted multi-objective score.

### 📊 Balanced Optimization Score

```text
Score = 0.4 × Normalized Fare
      + 0.3 × Normalized Time
      + 0.3 × Normalized Flights
