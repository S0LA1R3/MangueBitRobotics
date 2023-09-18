#include <iostream>
#include <vector>
#include <stack>
#include "graphElement.hpp"

using namespace std;

vector<vector<int>> source = {
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

const int N = static_cast<int>(source.size());
const int M = source[0].size();
struct Point {
    int x, y;
};

bool isValid(int x, int y, vector<vector<GraphElement>> graph) {
    return x >= 0 && x < N && y >= 0 && y < M && graph[x][y].getValue() == 0;
}

bool findPathDFS(Point src, Point dest, vector<Point>& path, vector<vector<bool>>& visited, vector<vector<GraphElement>> graph) {
    if (!isValid(src.x, src.y, graph) || visited[src.x][src.y]) {
        return false;
    }

    for (const Point& point : path) {
            graph[point.x][point.y].setValue(5);
        }

        for(vector<GraphElement> y : graph){
            for(GraphElement x : y){
                if(x.getValue() == 5){
                    cout << "- ";
                }else{
                    cout << x.getValue() << " ";
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

    vector<vector<GraphElement>> graph(N, vector<GraphElement>(M));

	for(int y = 0; y < N; y++){
		for(int x = 0; x < M; x++){
		graph[y][x].setValue(source[y][x]);
		}
	}

    cout << "Graph height: " << N << endl <<
        "Graph width: " << M << endl;

    if (isValid(dest.x, dest.y, graph) && findPathDFS(src, dest, path, visited, graph)) {
        cout << "Path finded:" << endl;

        for (const Point& point : path) {
            graph[point.x][point.y].setValue(5);
        }

        for(vector<GraphElement> y : graph){
            for(GraphElement x : y){
                if(x.getValue() == 5){
                    cout << "- ";
                }else{
                    cout << x.getValue() << " ";
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
