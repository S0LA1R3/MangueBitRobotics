#include <iostream>

#include "../src/graphElement.hpp"

using namespace std;

int main(){
    GraphElement element(0, GraphElement::DEFAULT);

    cout << element.getType() << element.getValue() << endl;

    return 0;
}
