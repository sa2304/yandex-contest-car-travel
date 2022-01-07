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

int countMinRoads(int from, int to, int k, const vector<Point> &coordinates) {
  // FIXME Test #15: Wrong Answer
  queue<int> q;
  unordered_set<int> visited;
  q.push(from);
  int level = 0;
  while (not q.empty()) {
    int count = q.size();
    for (int i = 0; i < count; ++i) {
      int stop = q.front();
      q.pop();
      visited.insert(stop);
      if (distanceBetween(coordinates.at(stop), coordinates.at(to)) <= k) { return level + 1; }
      for (int intermediate: getReachableCities(stop, k, coordinates)) {
        if (not visited.count(intermediate)) { q.push(intermediate); }
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
  TestFindShortestPath();
  cout << "Ok!"s << endl;
//  ProcessInput();
  return 0;
}