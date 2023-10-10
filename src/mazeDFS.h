#include "List.h"
#include "point.h"

List<Point> path;

List<GraphElement*> findAdjacent(GraphElement* element, List<List<GraphElement>>& graph, int tamanhoMaximo) {
  List<GraphElement*> adjacent;

  for (int y = 0; y < tamanhoMaximo; y++) {
    for (int x = 0; x < tamanhoMaximo; x++) {
      if (element == &graph[y][x]) {
        if (x > 0)
          adjacent.push_back(&graph[y][x - 1]);

        if (x < tamanhoMaximo - 1)
          adjacent.push_back(&graph[y][x + 1]);

        if (y > 0)
          adjacent.push_back(&graph[y - 1][x]);

        if (y < tamanhoMaximo - 1)
          adjacent.push_back(&graph[y + 1][x]);

        return adjacent;
      }
    }
  }

  return adjacent;
}

bool isValid(int x, int y, List<List<GraphElement>> graph) {
  return x >= 0 && x < tamanhoMaximo && y >= 0 && y < tamanhoMaximo && graph[x][y].getValue() == 0;
}

bool findPathDFS(Point src, Point dest, int tamanhoMaximo, List<List<GraphElement>> graph) {
  bool visited[tamanhoMaximo][tamanhoMaximo];

  if (!isValid(src.x, src.y, graph) || visited[src.x][src.y]) {
    return false;
  }

  List<GraphElement*> adjacent = findAdjacent(&graph[src.x][src.y], graph, tamanhoMaximo);
  for (int c = 0; c < static_cast<int>(path.getSize()) - 2; c++) {
    for (GraphElement* adj : adjacent) {
      if (adj == &graph[path[c].x][path[c].y]) {
        return false;
      }
    }
  }

  visited[src.x][src.y] = true;
  path.push_back(src);

  if (src.x == dest.x && src.y == dest.y) {
    return true;
  }

  int dx[] = {-1, 1, 0, 0};
  int dy[] = {0, 0, -1, 1};

  for (int i = 0; i < 4; i++) {
    int newX = src.x + dx[i];
    int newY = src.y + dy[i];

    if (isValid(newX, newY, graph)) {
      if (findPathDFS({newX, newY}, dest, visited, graph)) {
        return true;
      }
    }
  }

  path.pop_back();
  return false;
}
