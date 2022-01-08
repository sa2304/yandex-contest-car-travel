/**
 * https://contest.yandex.ru/contest/8458/problems/G/
 */

#include <cassert>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;

struct Point {
  int x;
  int y;
};

int distanceBetween(const Point &p1, const Point &p2) {
  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

vector<int> getReachableCities(int start, int max_road_length, const vector<Point> &coordinates) {
  vector<int> result;
  const Point &start_coord = coordinates.at(start);
  for (int i = 0; i < coordinates.size(); ++i) {
    if (start == i) { continue; }

    const Point &to_coord = coordinates.at(i);
    if (distanceBetween(start_coord, to_coord) <= max_road_length) { result.push_back(i); }
  }

  return result;
}

void TestGetReachableCities() {
  // FIXME
  vector<Point> c{{0, 0}, {1, 1}, {3, -3}, {-4, -1}, {-5, 2}, {-4, 3}};
  assert((vector<int>{}) == getReachableCities(0, 0, c));
  assert((vector<int>{}) == getReachableCities(0, 1, c));
  assert((vector<int>{1}) == getReachableCities(0, 2, c));
  assert((vector<int>{1}) == getReachableCities(0, 3, c));
  assert((vector<int>{1}) == getReachableCities(0, 4, c));
  assert((vector<int>{1, 3}) == getReachableCities(0, 5, c));
  assert((vector<int>{1, 2, 3}) == getReachableCities(0, 6, c));
  assert((vector<int>{1, 2, 3, 4, 5}) == getReachableCities(0, 7, c));

  assert((vector<int>{}) == getReachableCities(1, 0, c));
  assert((vector<int>{}) == getReachableCities(1, 1, c));
  assert((vector<int>{0}) == getReachableCities(1, 2, c));
  assert((vector<int>{0}) == getReachableCities(1, 3, c));
  assert((vector<int>{0}) == getReachableCities(1, 4, c));
  assert((vector<int>{0}) == getReachableCities(1, 5, c));
  assert((vector<int>{0,2}) == getReachableCities(1, 6, c));
  assert((vector<int>{0,2,3,4,5}) == getReachableCities(1, 7, c));
//  assert((vector<int>{0}) == getReachableCities(1, 5, c));


  assert((vector<int>{}) == getReachableCities(2, 5, c));
  assert((vector<int>{0, 4, 5}) == getReachableCities(3, 5, c));
  assert((vector<int>{3, 5}) == getReachableCities(4, 5, c));
  assert((vector<int>{3, 4}) == getReachableCities(5, 5, c));
}

int countMinRoads(int from, int to, int k, const vector<Point> &coordinates) {
  // FIXME Test #15: Wrong Answer
  queue<int> q;
  unordered_set<int> visited;
  q.push(from);
  int level = 0;
  while (not q.empty()) {
    clog << "level = "s << level << endl;
    clog << "queue size = "s << q.size() << endl;
    int count = q.size();
    for (int i = 0; i < count; ++i) {
      int stop = q.front();
      clog << "next stop = "s << stop << endl;
      q.pop();
      visited.insert(stop);
      if (distanceBetween(coordinates.at(stop), coordinates.at(to)) <= k) { return level + 1; }
      for (int intermediate: getReachableCities(stop, k, coordinates)) {
        if (not visited.count(intermediate)) {
          clog << intermediate << "is reachable"s << endl;
          q.push(intermediate);
        }
      }
    }
    ++level;
  }

  return -1;
}

void TestCountMinRoads() {
  {
    vector<Point> coordinates{{0, 0}, {0, 2}, {2, 2}, {0, -2}, {2, -2}, {2, -1}, {2, 1}};
    assert(2 == countMinRoads(0, 2, 2, coordinates));
  }
  {
    vector<Point> coordinates{{0, 0}, {1, 0}, {0, 1}, {1, 1}};
    assert(1 == countMinRoads(0, 3, 2, coordinates));
  }
  {
    vector<Point> coordinates{{0, 0}, {2, 0}, {0, 2}, {2, 2}};
    assert(-1 == countMinRoads(0, 3, 1, coordinates));
  }
  {
    vector<Point> c{{0, 0}, {1, 1}, {3, -3}, {-4, -1}, {-5, 2}, {-4, 3}};
    assert(-1 == countMinRoads(0, 3, 1, c));
    assert(-1 == countMinRoads(0, 3, 2, c));
    assert(-1 == countMinRoads(0, 3, 3, c));
    assert(-1 == countMinRoads(0, 3, 4, c));
    assert(1 == countMinRoads(0, 3, 5, c));

    assert(3 == countMinRoads(1, 5, 5, c));
    assert(3 == countMinRoads(1, 5, 6, c));
    assert(1 == countMinRoads(1, 5, 7, c));

    
  }
}

void ProcessInput() {
//  unordered_map<pair<int, int>, int> distances;
  vector<Point> coordinates;
  int cities_count;
  cin >> cities_count;
  string line;
  getline(cin, line);
  coordinates.reserve(cities_count);
  for (int i = 0; i < cities_count; ++i) {
    int x, y;
    cin >> x >> y;
    getline(cin, line);
    coordinates.push_back({x, y});
  }

  int k;
  cin >> k;
  getline(cin, line);

  int from, to;
  cin >> from >> to;
  getline(cin, line);

  cout << countMinRoads(from - 1, to - 1, k, coordinates) << endl;
}

int main() {
  TestGetReachableCities();
//  TestCountMinRoads();
  cout << "Ok!"s << endl;
//  ProcessInput();
  return 0;
}