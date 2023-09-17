#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int>> graph = {
  {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1},
  {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1},
  {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1},
  {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1},
  {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

const int N = static_cast<int>(graph.size());
const int M = graph[0].size();

struct Point {
    int x, y;
};

bool isValid(int x, int y, vector<vector<int>> graph) {
    return x >= 0 && x < N && y >= 0 && y < M && graph[x][y] == 0;
}

bool findPathDFS(Point src, Point dest, vector<Point>& path, vector<vector<bool>>& visited, vector<vector<int>> graph) {
    if (!isValid(src.x, src.y, graph) || visited[src.x][src.y]) {
        return false;
    }

    for (const Point& point : path) {
            graph[point.x][point.y] = 5;
        }

        for(vector<int> y : graph){
            for(int x : y){
                if(x == 5){
                    cout << "- ";
                }else{
                    cout << x << " ";
                }
            }
            cout << endl;
        }
    cout << endl;

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
    Point src = {5, 0};     // Origin
    Point dest = {1, 11};    // Destiny

    vector<Point> path;
    vector<vector<bool>> visited(N, vector<bool>(M, false));

    cout << "Graph height: " << N << endl <<
        "Graph width: " << M << endl;

    if (isValid(dest.x, dest.y, graph) && findPathDFS(src, dest, path, visited, graph)) {
        cout << "Path finded:" << endl;

        for (const Point& point : path) {
            graph[point.x][point.y] = 5;
        }

        for(vector<int> y : graph){
            for(int x : y){
                if(x == 5){
                    cout << "- ";
                }else{
                    cout << x << " ";
                }
            }
            cout << endl;
        }

        cout << endl;
    } else {
        cout << "Couldn't find the way." << endl;
    }

    return 0;
}
