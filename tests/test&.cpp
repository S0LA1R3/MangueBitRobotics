#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<int> a = {1, 2, 3};
    vector<int> b = a[];
    b[1] = 2;

    cout << a[1] << endl;
    return 0;
}
