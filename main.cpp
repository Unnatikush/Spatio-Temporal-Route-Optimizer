#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;


// Structure to store flight information
struct Flight {
    string destination;
    int fare;
    float time;
};


// Structure to store complete route information
struct Route {
    vector<string> path;
    int totalFare;
    float totalTime;
    int flightCount;
};


// DFS function with Early Pruning
void findRoutes(
    string current,
    string destination,
    map<string, vector<Flight>>& graph,
    vector<string>& path,
    vector<Route>& routes,
    int totalFare,
    float totalTime,
    int maxBudget,
    float maxTime,
    int maxFlights
) {

    // Add current city to path
    path.push_back(current);


    // Calculate current number of flights
    int currentFlights = path.size() - 1;


    // EARLY PRUNING
    // Stop immediately if any constraint is violated
    if (totalFare > maxBudget ||
        totalTime > maxTime ||
        currentFlights > maxFlights) {

        path.pop_back();
        return;
    }


    // Destination reached
    if (current == destination) {

        Route route;

        route.path = path;
        route.totalFare = totalFare;
        route.totalTime = totalTime;
        route.flightCount = currentFlights;

        routes.push_back(route);

        path.pop_back();
        return;
    }


    // Explore all connected flights
    for (Flight flight : graph[current]) {

        bool alreadyVisited = false;


        // Prevent cycles
        for (string city : path) {

            if (city == flight.destination) {
                alreadyVisited = true;
                break;
            }
        }


        // Continue DFS only if city has not been visited
        if (!alreadyVisited) {

            findRoutes(
                flight.destination,
                destination,
                graph,
                path,
                routes,
                totalFare + flight.fare,
                totalTime + flight.time,
                maxBudget,
                maxTime,
                maxFlights
            );
        }
    }


    // Backtracking
    path.pop_back();
}


// Function to print route
void printRoute(Route route) {

    cout << "\nRoute: ";

    for (int i = 0; i < route.path.size(); i++) {

        cout << route.path[i];

        if (i != route.path.size() - 1) {
            cout << " -> ";
        }
    }

    cout << "\nTotal Fare: Rs." << route.totalFare;

    cout << "\nTotal Time: "
         << route.totalTime
         << " hours";

    cout << "\nNumber of Flights: "
         << route.flightCount;

    cout << endl;
}


int main() {

    cout << "===== SPATIO-TEMPORAL ROUTE OPTIMIZER =====\n";


    // Graph representing flight network
    map<string, vector<Flight>> graph;


    // =====================================================
    // FLIGHT NETWORK
    // =====================================================

    graph["Delhi"].push_back({"Mumbai", 4000, 2});
    graph["Delhi"].push_back({"Jaipur", 2500, 1});
    graph["Delhi"].push_back({"Lucknow", 3000, 1.2});
    graph["Delhi"].push_back({"Chandigarh", 2800, 1});

    graph["Mumbai"].push_back({"Pune", 1200, 0.5});
    graph["Mumbai"].push_back({"Ahmedabad", 2200, 1});
    graph["Mumbai"].push_back({"Goa", 2500, 1});
    graph["Mumbai"].push_back({"Bangalore", 3500, 2});

    graph["Bangalore"].push_back({"Chennai", 1800, 1});
    graph["Bangalore"].push_back({"Hyderabad", 2000, 1});
    graph["Bangalore"].push_back({"Kochi", 2200, 1.2});
    graph["Bangalore"].push_back({"Mysore", 1000, 0.5});

    graph["Chennai"].push_back({"Hyderabad", 2500, 1});
    graph["Chennai"].push_back({"Kochi", 2000, 1});
    graph["Chennai"].push_back({"Coimbatore", 1200, 0.5});

    graph["Hyderabad"].push_back({"Bangalore", 2000, 1});
    graph["Hyderabad"].push_back({"Chennai", 2500, 1});
    graph["Hyderabad"].push_back({"Pune", 2500, 1});
    graph["Hyderabad"].push_back({"Nagpur", 1800, 1});

    graph["Kolkata"].push_back({"Bhubaneswar", 1500, 0.8});
    graph["Kolkata"].push_back({"Patna", 1800, 1});
    graph["Kolkata"].push_back({"Guwahati", 2200, 1.2});
    graph["Kolkata"].push_back({"Delhi", 4500, 2.5});

    graph["Pune"].push_back({"Mumbai", 1200, 0.5});
    graph["Pune"].push_back({"Hyderabad", 2500, 1});
    graph["Pune"].push_back({"Nagpur", 1800, 1});

    graph["Ahmedabad"].push_back({"Mumbai", 2200, 1});
    graph["Ahmedabad"].push_back({"Jaipur", 1800, 0.8});
    graph["Ahmedabad"].push_back({"Udaipur", 1200, 0.6});

    graph["Jaipur"].push_back({"Delhi", 2500, 1});
    graph["Jaipur"].push_back({"Ahmedabad", 1800, 0.8});
    graph["Jaipur"].push_back({"Udaipur", 1000, 0.5});
    graph["Jaipur"].push_back({"Jodhpur", 1100, 0.5});

    graph["Lucknow"].push_back({"Delhi", 3000, 1.2});
    graph["Lucknow"].push_back({"Patna", 1500, 0.8});
    graph["Lucknow"].push_back({"Varanasi", 1000, 0.5});
    graph["Lucknow"].push_back({"Kanpur", 700, 0.3});

    graph["Chandigarh"].push_back({"Delhi", 2800, 1});
    graph["Chandigarh"].push_back({"Amritsar", 1000, 0.5});
    graph["Chandigarh"].push_back({"Shimla", 800, 0.4});

    graph["Goa"].push_back({"Mumbai", 2500, 1});
    graph["Goa"].push_back({"Bangalore", 2800, 1.2});
    graph["Goa"].push_back({"Kochi", 2500, 1.2});

    graph["Kochi"].push_back({"Bangalore", 2200, 1.2});
    graph["Kochi"].push_back({"Chennai", 2000, 1});
    graph["Kochi"].push_back({"Trivandrum", 1000, 0.5});

    graph["Bhubaneswar"].push_back({"Kolkata", 1500, 0.8});
    graph["Bhubaneswar"].push_back({"Visakhapatnam", 1400, 0.7});

    graph["Patna"].push_back({"Kolkata", 1800, 1});
    graph["Patna"].push_back({"Lucknow", 1500, 0.8});
    graph["Patna"].push_back({"Varanasi", 1200, 0.6});

    graph["Guwahati"].push_back({"Kolkata", 2200, 1.2});
    graph["Guwahati"].push_back({"Imphal", 1300, 0.6});
    graph["Guwahati"].push_back({"Shillong", 800, 0.4});

    graph["Nagpur"].push_back({"Hyderabad", 1800, 1});
    graph["Nagpur"].push_back({"Pune", 1800, 1});
    graph["Nagpur"].push_back({"Bhopal", 1400, 0.7});

    graph["Udaipur"].push_back({"Jaipur", 1000, 0.5});
    graph["Udaipur"].push_back({"Ahmedabad", 1200, 0.6});

    graph["Jodhpur"].push_back({"Jaipur", 1100, 0.5});

    graph["Varanasi"].push_back({"Lucknow", 1000, 0.5});
    graph["Varanasi"].push_back({"Patna", 1200, 0.6});
    graph["Varanasi"].push_back({"Prayagraj", 800, 0.4});

    graph["Kanpur"].push_back({"Lucknow", 700, 0.3});
    graph["Kanpur"].push_back({"Prayagraj", 900, 0.4});

    graph["Amritsar"].push_back({"Chandigarh", 1000, 0.5});

    graph["Shimla"].push_back({"Chandigarh", 800, 0.4});
    graph["Shimla"].push_back({"Manali", 1200, 0.6});

    graph["Mysore"].push_back({"Bangalore", 1000, 0.5});

    graph["Coimbatore"].push_back({"Chennai", 1200, 0.5});
    graph["Coimbatore"].push_back({"Madurai", 900, 0.4});

    graph["Trivandrum"].push_back({"Kochi", 1000, 0.5});

    graph["Visakhapatnam"].push_back({"Bhubaneswar", 1400, 0.7});
    graph["Visakhapatnam"].push_back({"Hyderabad", 2000, 1});

    graph["Imphal"].push_back({"Guwahati", 1300, 0.6});

    graph["Shillong"].push_back({"Guwahati", 800, 0.4});

    graph["Bhopal"].push_back({"Nagpur", 1400, 0.7});
    graph["Bhopal"].push_back({"Indore", 1000, 0.5});

    graph["Indore"].push_back({"Bhopal", 1000, 0.5});
    graph["Indore"].push_back({"Ahmedabad", 2000, 1});

    graph["Prayagraj"].push_back({"Varanasi", 800, 0.4});
    graph["Prayagraj"].push_back({"Kanpur", 900, 0.4});

    graph["Manali"].push_back({"Shimla", 1200, 0.6});
    graph["Manali"].push_back({"Leh", 2500, 1.5});

    graph["Leh"].push_back({"Manali", 2500, 1.5});

    graph["Madurai"].push_back({"Coimbatore", 900, 0.4});
    graph["Madurai"].push_back({"Chennai", 1500, 0.8});

    graph["Surat"].push_back({"Mumbai", 1800, 0.8});
    graph["Surat"].push_back({"Ahmedabad", 1200, 0.5});

    graph["Ranchi"].push_back({"Kolkata", 1800, 1});
    graph["Ranchi"].push_back({"Patna", 1400, 0.7});

    graph["Raipur"].push_back({"Nagpur", 1600, 0.8});
    graph["Raipur"].push_back({"Hyderabad", 2200, 1});

    graph["Dehradun"].push_back({"Delhi", 1800, 0.8});
    graph["Dehradun"].push_back({"Chandigarh", 1200, 0.5});

    graph["Srinagar"].push_back({"Delhi", 3500, 1.5});
    graph["Srinagar"].push_back({"Jammu", 1200, 0.6});

    graph["Jammu"].push_back({"Srinagar", 1200, 0.6});
    graph["Jammu"].push_back({"Chandigarh", 1800, 0.8});


    // Display Flight Network
    cout << "\nFlight Network:\n";

    for (auto city : graph) {

        cout << city.first << " -> ";

        for (auto flight : city.second) {

            cout << flight.destination
                 << " (Rs." << flight.fare
                 << ", " << flight.time
                 << " hrs)  ";
        }

        cout << endl;
    }


    // Source and Destination
    string source, destination;

    cout << "\nEnter Source City: ";
    cin >> source;

    cout << "Enter Destination City: ";
    cin >> destination;


    // Validate Source
    if (graph.find(source) == graph.end()) {

        cout << "Source city does not exist!" << endl;
        return 0;
    }


    // Validate Destination
    if (graph.find(destination) == graph.end()) {

        cout << "Destination city does not exist!" << endl;
        return 0;
    }


    // User Constraints
    int maxBudget;
    float maxTime;
    int maxFlights;

    cout << "\nEnter Maximum Budget (Rs.): ";
    cin >> maxBudget;

    cout << "Enter Maximum Travel Time (hours): ";
    cin >> maxTime;

    cout << "Enter Maximum Number of Flights: ";
    cin >> maxFlights;


    // Find valid routes directly using constraint-aware DFS
    vector<string> path;
    vector<Route> validRoutes;


    findRoutes(
        source,
        destination,
        graph,
        path,
        validRoutes,
        0,
        0,
        maxBudget,
        maxTime,
        maxFlights
    );


    // No valid route found
    if (validRoutes.empty()) {

        cout << "\nNo route satisfies all constraints!" << endl;
        return 0;
    }


    // Display valid routes
    cout << "\n===== VALID ROUTES =====\n";

    for (int i = 0; i < validRoutes.size(); i++) {

        cout << "\nRoute " << i + 1 << ":";

        printRoute(validRoutes[i]);
    }


    // Optimization preference
    int choice;

    cout << "\n===== OPTIMIZATION OPTIONS =====\n";

    cout << "1. Cheapest Route\n";
    cout << "2. Fastest Route\n";
    cout << "3. Minimum Flights\n";
    cout << "4. Balanced Route\n";

    cout << "\nChoose Optimization Preference: ";
    cin >> choice;


    // Initially select first valid route
    Route bestRoute = validRoutes[0];


    // Cheapest Route
    if (choice == 1) {

        for (Route route : validRoutes) {

            if (route.totalFare < bestRoute.totalFare) {
                bestRoute = route;
            }
        }

        cout << "\n===== CHEAPEST ROUTE =====\n";
    }


    // Fastest Route
    else if (choice == 2) {

        for (Route route : validRoutes) {

            if (route.totalTime < bestRoute.totalTime) {
                bestRoute = route;
            }
        }

        cout << "\n===== FASTEST ROUTE =====\n";
    }


    // Minimum Flights
    else if (choice == 3) {

        for (Route route : validRoutes) {

            if (route.flightCount < bestRoute.flightCount) {
                bestRoute = route;
            }
        }

        cout << "\n===== MINIMUM FLIGHTS ROUTE =====\n";
    }


    // Balanced Multi-Objective Route
    else if (choice == 4) {

        float bestScore = 1000000;

        for (Route route : validRoutes) {

            float normalizedFare =
                (float)route.totalFare / maxBudget;

            float normalizedTime =
                route.totalTime / maxTime;

            float normalizedFlights =
                (float)route.flightCount / maxFlights;


            // Weighted multi-objective score
            float score =
                0.4 * normalizedFare +
                0.3 * normalizedTime +
                0.3 * normalizedFlights;


            if (score < bestScore) {

                bestScore = score;
                bestRoute = route;
            }
        }

        cout << "\n===== BALANCED OPTIMAL ROUTE =====\n";
    }


    // Invalid choice
    else {

        cout << "\nInvalid choice!" << endl;
        return 0;
    }


    // Display best route
    printRoute(bestRoute);


    cout << "\n===== ROUTE OPTIMIZATION COMPLETE =====\n";

    return 0;
}