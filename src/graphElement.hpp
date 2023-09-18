#ifndef GRAPHELEMENT_HPP
#define GRAPHELEMENT_HPP

#include <vector>

using namespace std;

class GraphElement {
public:
    enum ElementType{
        CHECKPOINT,
        VICTIM,
        HOLE,
        LEVELCHANGE,
        DEFAULT
    };

    GraphElement() : value(0), type(DEFAULT) {}

    GraphElement(int val) : value(val), type(DEFAULT) {};

    GraphElement(ElementType ty) : value(0), type(ty) {};

    GraphElement(int val, ElementType ty) : value(val), type(ty) {};

    int getValue() const {
        return value;
    }

    void setValue(int val){
        value = val;
    }

    ElementType getType() const {
        return type;
    }

private:
    vector<GraphElement> adjacent;
    int value;
    ElementType type;
};

#endif // GRAPHELEMENT_HPP
