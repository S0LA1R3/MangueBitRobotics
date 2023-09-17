#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int>> graph = {
    {0, 0, 0, 1, 1, 1},
    {1, 1, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 1, 0, 1, 1, 0},
    {0, 1, 0, 1, 0, 0},
    {0, 0, 0, 1, 1, 1}
};

struct Point {
    int x, y;
};

bool isValid(int x, int y, vector<vector<int>> graph) {
    return x >= 0 && x < graph.size() && y >= 0 && y < graph[x].size() && graph[x][y] == 0;
}

bool findPathDFS(Point src, Point dest, vector<Point>& path, vector<vector<bool>>& visited, vector<vector<int>> graph) {
    if (!isValid(src.x, src.y, graph) || visited[src.x][src.y]) {
        return false;
    }

    cout << "(" << src.x << ", " << src.y << ")" << endl;

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

        if(isValid(newX, newY, graph)){
            if (findPathDFS({newX, newY}, dest, path, visited, graph)) {
                return true;
            }
        }
    }

    path.pop_back();
    return false;
}

int main() {
    Point src = {0, 0};     // Origin
    Point dest = {4, 4};    // Destiny

    vector<Point> path;
    vector<vector<bool>> visited(graph.size(), vector<bool>(graph[0].size(), false));

    if (isValid(dest.x, dest.y, graph) && findPathDFS(src, dest, path, visited, graph)) {
        cout << "Caminho encontrado:" << endl;
        for (const Point& point : path) {
            cout << "(" << point.x << "," << point.y << ") ";
        }
        cout << endl;
    } else {
        cout << "Não foi possível encontrar um caminho." << endl;
    }

    return 0;
}
