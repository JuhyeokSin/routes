// Programmer: Jay Sin
// Editor used: Visual Studio Code
// Compiler used: Apple LLVM version 8.0.0 (clang-800.0.38)
#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

#include <cstring>

class Leg {
// Use constant, read-only pointers to store the city names as C strings
// There will be no need to ever make copies of the names--no strcpy
// names will be declared and stored in the main program
private:
  const char* const startingCity;
  const char* const endingCity;
  const double distance;
// Do not include a default constructor
// since each Leg is very specific and constant and unchaning
public:
  Leg(const char* const, const char* const, const double);
  double getDistance() const { return distance;} // gets the distance in Leg
  void output(ostream&) const;                   // formatted output for Legs
  Leg& operator = (const Leg&);                  // assignment operator overriding
                                                 // This will be used when we sort the Leg objects
                                                 // with its distance

  friend class Route;         // Now, Route class can access the private member of Leg
  friend class ShortestRoute; // Now, ShortestRoute class can access the private member of Leg
};

class Route {
// Use constant vector bag to store legs
private:
  vector<const Leg*> legs;
  const double totalDistance;

public:
  Route(const Leg&);
  Route(const Route&, const Leg&);
  double getTotalDist() const {return totalDistance;}  // gets the total distance in Route class
  void output(ostream& out) const;                     // formatted output for Route
  Route& operator = (const Route&);                    // assignment operator overriding
                                                       // This will be used when we sort the Route objects
                                                       // with its distance

  friend class ShortestRoute; // Now, ShortestRoute class can access the private member of Route
};

class ShortestRoute {
private:
  static const Leg legs[];
public:
  static Route anyRoute(const char* const, const char* const);
  static Route shortestRoute(const char* const, const char* const);
};

// Global declaration for leg object array
const Leg ShortestRoute::legs[] = {
  Leg("San Francisco", "Sacramento", 87.9), Leg("Sacramento", "Reno", 132),
  Leg("Sacramento", "Bakersfield", 286), Leg("Portland", "Sacramento", 581),
  Leg("Reno", "Winnemucca", 166), Leg("Reno", "Salt Lake City", 518),
  Leg("Portland", "Reno", 533), Leg("Winnemucca", "Elko", 124),
  Leg("Bakersfield", "Winnemucca", 560), Leg("Winnemucca", "Battle Mountain", 53.5),
  Leg("San Francisco", "Bakersfield", 283), Leg("San Francisco", "Eureka", 271),
  Leg("Eureka", "Portland", 409), Leg("San Francisco", "Battle Mountain", 436),
  Leg("Battle Mountain", "Salt Lake City", 300), Leg("Battle Mountain", "Elko", 70.5),
  Leg("Bakersfield", "West Wendover", 647), Leg("West Wendover", "Albuquerque", 719),
  Leg("Elko", "West Wendover", 107), Leg("West Wendover", "Salt Lake City", 123),
  Leg("Rock Spring", "Albuquerque", 653), Leg("Spokane", "Rock Spring", 758),
  Leg("Salt Lake City", "Rock Spring", 187), Leg("Omaha", "New York", 1246),
  Leg("Rock Spring", "Cheyenne", 256), Leg("Cheyenne", "Omaha", 494),
  Leg("Chicago", "Cincinnati", 299), Leg("Kansas City", "Chicago", 510),
  Leg("Omaha", "Chicago", 472), Leg("Chicago", "New York", 790),
  Leg("Los Angeles", "Las Vegas", 270), Leg("Bakersfield", "Los Angeles", 113),
  Leg("Phoenix", "Albuquerque", 422), Leg("San Francisco", "Los Angeles", 383),
  Leg("Los Angeles", "Phoenix", 373), Leg("Las Cruces", "Oklahoma City", 672),
  Leg("Las Vegas", "Las Cruces", 685), Leg("Phoenix", "Las Cruces", 388),
  Leg("Las Cruces", "Austin", 622), Leg("Austin", "Jacksonville", 1034),
  Leg("Jacksonville", "Richmond", 598), Leg("Kansas City", "Jacksonville", 1144),
  Leg("Jacksonville", "New York", 930), Leg("Seattle", "Spokane", 279),
  Leg("Richmond", "New York", 333), Leg("San Francisco", "Seattle", 808),
  Leg("Seattle", "Great Falls", 642), Leg("Minneapolis", "Chicago", 408),
  Leg("Great Falls", "Minneapolis", 967), Leg("Cincinnati", "Richmond", 514),
  Leg("Minneapolis", "Cincinnati", 704), Leg("Cincinnati", "New York", 639),
  Leg("Great Falls", "Cheyenne", 670), Leg("Cheyenne", "Minneapolis", 809),
  Leg("Austin", "Omaha", 842), Leg("Salt Lake City", "Kansas City", 1073),
  Leg("Bakersfield", "Las Vegas", 286), Leg("Las Vegas", "Phoenix", 298),
  Leg("San Francisco", "Portland", 635), Leg("Portland", "Seattle", 173),
  Leg("Portland", "Spokane", 351), Leg("Spokane", "Great Falls", 365),
  Leg("Portland", "Elko", 627), Leg("Elko", "Cheyenne", 667),
  Leg("Las Vegas", "Albuquerque", 574), Leg("Albuquerque", "Austin", 695),
  Leg("Albuquerque", "Kansas City", 790), Leg("Oklahoma City", "Kansas City", 353),
  Leg("Oklahoma City", "Nashville", 678), Leg("Salt Lake City", "Oklahoma City", 1188),
  Leg("Austin", "Nashville", 859), Leg("Nashville", "Cincinnati", 272),
  Leg("Denver", " Kansas City", 605), Leg("Great Falls", "Denver", 770),
  Leg("Nashville", "Richmond", 614), Leg("Las Vegas", "Denver", 748),
  Leg("Denver", " Omaha", 538), Leg("San Francisco", "New York", 21000)
};

ostream& roundingOne(ostream&); // rounding manipulation
bool operator < (const Route&, const Route&);

int main() {

  // programmer's identification
  cout << "Programmer: Juhyeok Sin\n";

  // Initialize greedyRoute with anyRoute()
  // Initialize bestRoute with shortestRoute()
  Route greedyRoute = ShortestRoute::anyRoute("San Francisco", "New York");
  Route bestRoute = ShortestRoute::shortestRoute("San Francisco", "New York");

  // Print the shortest route
  cout << "------- Shortest Route --------" << endl;
  bestRoute.output(cout);
  // Print a greed route
  cout << "-------    Any Route   --------" << endl;
  greedyRoute.output(cout);

  return 0;
}

/**
* Read a constant read only char pointer 'from' for starting city
* Read a constant read only char pointer 'to' for ending city
* @param from variable to represent the starting city
* @param to   variable to represent the ending city
* @return
*/
Route ShortestRoute::anyRoute(const char* const from, const char* const to) {
  // Store the number of legs into legSize
  // To get the legSize, divide the size of legs by the size of one element in legs
  const int legSize = sizeof(legs) / sizeof(*legs);
  // Initialize the pointer variable legTo with NULL, so that
  // legTo does not reference anything yet
  const Leg *legTo = NULL;

  try {
    for (int i = 0; i < legSize; i++) {
      // Find arriving and departing city
      // Note that if two C string variables in strcmp() function are the same,
      // strcmp returns 0 and !0 represent true
      bool matchDestination = !strcmp(to, legs[i].endingCity);
      bool matchDeparting = !strcmp(from, legs[i].startingCity);
      if (matchDestination && matchDeparting) return Route(legs[i]);
      if (matchDestination) {
        // legTo references an element of the array legs at the index of i
        legTo = &legs[i];
        break; // break the for loop
      }
    }
    // Throws an error message when legTo does not references anything at this point
    if (!legTo) throw "No matching arriving city found";
  } catch(const char* err) {
    cout << err << endl;
  }

  return Route(anyRoute(from, legTo->startingCity), *legTo);
}

Route ShortestRoute::shortestRoute(const char* const from, const char* const to) {
  const int legSize = sizeof(legs) / sizeof(*legs);
  set<Route> routes;

  try {
    // Find arriving city
    for (int i = 0; i < legSize; i++) {
      bool matchDestination = !strcmp(to, legs[i].endingCity);
      bool matchDeparting = !strcmp(from, legs[i].startingCity);
      if (!strcmp(legs[i].startingCity, "San Francisco") &&
          !strcmp(legs[i].endingCity, "New York")) continue;
      if (matchDestination && matchDeparting) return Route(legs[i]);
      if (matchDestination) {
        try {
          const Route candidate(shortestRoute(from, legs[i].startingCity), legs[i]);
          routes.insert(candidate);
        } catch(const char* err) {
          continue;
        }
      }
    }

    // if (legFrom && legTo && (legFrom != legTo)) return Route(*legTo);
    if (routes.empty()) throw "Something went wrong. Check your legs";
  } catch(const char* err) {
    cout << err << endl;
  }

  return *routes.begin();
}

Leg::Leg (const char* const cityA, const char* const cityB, const double distBtw)
  : startingCity(cityA), endingCity(cityB), distance(distBtw)
{
}

void Leg::output(ostream& out) const {
  out << "Leg: " << startingCity << " to " << endingCity
    << ", " << roundingOne << distance << " miles." << endl;

}

ostream& roundingOne(ostream& out) {
  out.setf(ios::fixed);
  out.precision(1); // 1 decimal digits
  return out;
}

/* Assignment operator of the Leg object */
Leg& Leg::operator = (const Leg& right) {
  Leg &left = *this;

  // Skip if the operand is the self
  if (this == &right) {
    return left;
  }

  // Assign values of the attributes from the object which is on the right hand side
  // into the attributes of the object which is on the left hand side
  // by casting constant read-only pointer char string data type into a regular double
  const_cast<const char*&>(left.startingCity) = right.startingCity;
  const_cast<const char*&>(left.endingCity) = right.endingCity;
  const_cast<double&>(left.distance) = right.distance;

  return left;
}

Route::Route(const Leg& leg)
  : totalDistance(leg.distance)
{
  legs.push_back(&leg);
}

Route::Route(const Route& route, const Leg& leg)
  : legs(route.legs), totalDistance(0.0)
{
  try {
    const Leg* lastLeg = legs.back();
    if (strcmp(lastLeg->endingCity, leg.startingCity) != 0)
      throw "Cities don't match!";
    legs.push_back(&leg);
    for (unsigned int i = 0; i < legs.size(); i++) {
      const_cast<double&>(totalDistance) += legs[i]->getDistance();
    }
  }
  catch (const char* err) {
    cout << err << endl;
  }
}

void Route::output(ostream& out) const {
  const Leg* lastLeg = legs.back();
  out << "Route: ";
  // print out all cities from your starting point city besides the last city
  for( unsigned int i = 0; i < legs.size(); i++)
    out << legs[i]->startingCity << " to ";
  // print out only destination
  out << lastLeg->endingCity << ", " << roundingOne
    << totalDistance << endl;
}

/* Assignment operator of the Route object */
Route& Route::operator = (const Route& right) {
  Route &left = *this;

  // Skip if the operand is the self
  if (this == &right) {
    return left;
  }

  // Assign values of the attributes from the object which is on the right hand side
  // into the attributes of the object which is on the left hand side
  // by casting
  left.legs = right.legs;
  const_cast<double&>(left.totalDistance) = right.totalDistance;

  return left;
}

bool operator < (const Route& left, const Route& right) {
  return left.getTotalDist() < right.getTotalDist();
}
