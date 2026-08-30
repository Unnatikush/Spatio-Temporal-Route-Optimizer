Spatio-Temporal Route Optimizer

A C++ based multi-criteria route optimization system that uses graph traversal and constraint-aware DFS to find optimal flight routes across a dynamically connected network.

Features
Graph-based representation of a flight network
Depth First Search (DFS) for route exploration
Multiple route discovery between source and destination
Cycle prevention using visited-path checking
Constraint-aware route traversal
Early pruning for invalid routes
Budget constraints
Travel time constraints
Maximum flight count constraints
Cheapest route optimization
Fastest route optimization
Minimum flights optimization
Balanced multi-objective route optimization
Optimization Criteria

The system allows users to select different optimization strategies:

Cheapest Route - Minimizes total travel fare.
Fastest Route - Minimizes total travel time.
Minimum Flights - Minimizes the number of flights.
Balanced Route - Uses a weighted multi-objective score considering fare, travel time, and number of flights.

The balanced optimization score is calculated using normalized values:

Score =
0.4 × Normalized Fare +
0.3 × Normalized Time +
0.3 × Normalized Flights

The route with the lowest score is selected as the balanced optimal route.

Algorithm

The project uses a graph-based DFS traversal approach.

Source City
     |
     v
Explore Connected Flights
     |
     v
Check Constraints
     |
     +---- Constraint Violated ----> Stop Exploration
     |
     v
Continue DFS
     |
     v
Destination Reached
     |
     v
Store Valid Route
     |
     v
Apply Optimization Strategy
     |
     v
Return Optimal Route
Constraints

During route traversal, the following constraints are checked:

Total Fare ≤ Maximum Budget
Total Travel Time ≤ Maximum Travel Time
Number of Flights ≤ Maximum Allowed Flights

Routes violating any constraint are pruned early during DFS traversal.

Technologies Used
C++
Standard Template Library (STL)
Graph Data Structures
Depth First Search (DFS)
Multi-Objective Optimization
How to Run

Compile the program using:

g++ main.cpp -o routeOptimizer

Run the program:

.\routeOptimizer
Example Input
Enter Source City: Delhi
Enter Destination City: Chennai

Enter Maximum Budget (Rs.): 10000
Enter Maximum Travel Time (hours): 6
Enter Maximum Number of Flights: 3

Choose Optimization Preference: 4
Project Structure
Spatio-Temporal-Route-Optimizer
│
├── main.cpp
└── README.md
Future Improvements
Integration with real-time flight data
Priority queue-based optimization algorithms
Dijkstra's algorithm for shortest path comparison
Dynamic flight availability
Interactive user interface
Database integration
Advanced multi-objective optimization techniques
