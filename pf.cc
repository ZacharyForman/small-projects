#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

struct Point {
  int x, y;
  bool operator<(const Point &p) const {
    return std::tie(x, y) < std::tie(p.x, p.y);
  }

  Point operator+(const Point &p) const {
    return {x + p.x, y + p.y};
  }

  bool operator==(const Point &p) const {
    return std::tie(x, y) == std::tie(p.x, p.y);
  }

  bool operator!=(const Point &p) const {
    return std::tie(x, y) != std::tie(p.x, p.y);
  }
};

struct Node {
  Point curr, pre;
  double cost, h;
  unsigned ts;
  bool operator<(const Node &n) const {
    return std::tie(h, ts) > std::tie(n.h, n.ts);
  }
};

using Map = std::vector<std::vector<char>>;
using PriorityQueue = std::priority_queue<Node>;
using Queue = std::queue<Node>;

bool ReadInput(const char *file, unsigned &h, unsigned &w,
               Point &src, Point &dest, Map &map)
{
  std::fstream f(file);
  if (!(f >> h >> w >> src.x >> src.y >> dest.x >> dest.y)) return false;
  map.push_back(std::vector<char>(w + 2, 'X'));
  for (unsigned i = 0; i < h; i++) {
    map.push_back(std::vector<char>(w + 2, 'X'));
    for (unsigned j = 0; j < w; j++) {
      f >> map[i+1][j+1];
    }
  }
  map.push_back(std::vector<char>(w + 2, 'X'));
  return f;
}

void PrintMap(const Map &map)
{
  for (unsigned i = 1; i < map.size()-1; i++) {
    std::cout << map[i][1];
    for (unsigned j = 2; j < map[i].size()-1; j++) {
      std::cout << " " << map[i][j];
    }
    std::cout << std::endl;
  }
}

Node pop(Queue &q)
{
  Node n = q.front();
  q.pop();
  return n;
}

Node pop(PriorityQueue &q)
{
  Node n = q.top();
  q.pop();
  return n;
}

constexpr Point adjacencies[] = {{1,0},{-1,0},{0,-1},{0,1}};

template<typename QueueType, typename Heuristic>
bool FindPath(Map &map, Point src, Point dest, Heuristic h)
{
  unsigned ts = 0;
  std::map<Point, Point> predecessor;
  QueueType q;
  q.push({src, {0,0}, 0, h(src), ts++});
  while (!q.empty()) {
    Node n = pop(q);
    Point curr = n.curr;
    if (map[curr.x][curr.y] == 'X' || predecessor.count(curr)) continue;
    predecessor[curr] = n.pre;
  if (curr == dest) break;
    for (const auto &adj : adjacencies) {
      Point next = curr + adj;
      double dist = std::max(1, map[next.x][next.y] - map[curr.x][curr.y]);
      q.push({next, curr, n.cost + dist, n.cost + dist + h(next), ts++});
    }
  }
  if (!predecessor.count(dest)) return false;
  for (Point p = dest; p != Point({0,0}); p = predecessor[p]) {
    map[p.x][p.y] = '*';
  }
  return true;
}

int main(int argc, char **argv)
{
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " f type [heuristic]" << std::endl;
    return 1;
  }

  unsigned h, w;
  Point src, dest;
  Map map;
  if (!ReadInput(argv[1], h, w, src, dest, map)) {
    std::cerr << "Cannot read input file " << argv[1] << std::endl;
    return 1;
  }

  bool found = false;
  auto none = [](Point p) -> double { return 0.0; };
  auto manhattan = [dest](Point p) -> double {
    return std::abs(p.x - dest.x) + std::abs(p.y - dest.y);
  };
  auto euclidean = [dest](Point p) -> double {
    return std::sqrt(std::pow(p.x - dest.x, 2) + std::pow(p.y - dest.y, 2));
  };

  if (std::string(argv[2]) == "bfs") {
    found = FindPath<Queue>(map, src, dest, none);
  } else if (std::string(argv[2]) == "ucs") {
    found = FindPath<PriorityQueue>(map, src, dest, none);
  } else if (std::string(argv[2]) == "astar") {
    if (argc < 3) {
      std::cerr << "No heuristic given" << std::endl;
      return 1;
    } else if (std::string(argv[3]) == "manhattan") {
      found = FindPath<PriorityQueue>(map, src, dest, manhattan);
    } else if (std::string(argv[3]) == "euclidean") {
      found = FindPath<PriorityQueue>(map, src, dest, euclidean);
    } else {
      std::cerr << "Unknown heuristic " << argv[3] << std::endl;
      return 1;
    }
  }
  if (found) {
    PrintMap(map);
  } else {
    std::cout << "null" << std::endl;
  }
  return 0;
}
