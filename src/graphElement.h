#ifndef GRAPHELEMENT_HPP
#define GRAPHELEMENT_HPP

class GraphElement {
public:
  enum ElementType {
    POOL,
    CHECKPOINT,
    VICTIM,
    HOLE,
    LEVELCHANGE,
    PADRAO
  };

  GraphElement() : value(2), type(PADRAO) {}

  GraphElement(int val) : value(val), type(PADRAO) {};

  GraphElement(ElementType ty) : value(2), type(ty) {};

  GraphElement(int val, ElementType ty) : value(val), type(ty) {};

  int getValue() const {
    return value;
  }

  void setValue(int val) {
    value = val;
  }

  void setType(ElementType ty) {
    if(type != PADRAO){
      type = ty;
    }
  }

  ElementType getType() const {
    return type;
  }

private:
  int value;
  ElementType type;
};

#endif // GRAPHELEMENT_HPP
