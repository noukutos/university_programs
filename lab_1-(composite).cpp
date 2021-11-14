#include <algorithm>
#include <iostream>
#include <list>
#include <string>
class Component {
protected:
    int value;
    std::list<Component*> lst;
public:
    Component(int value_) {
        this->value = value_;
    }
    virtual std::string Execute() { return (""); };
    void Add(Component* child) {
        lst.push_back(child);
    }
};

class Leaf : public Component {
public:
    Leaf(int value_) : Component(value_) {}
    std::string Execute() override {
        return (std::to_string(value));
    }
};

class Box : public Component {
public:
    Box(int value_) : Component(value_) {}
    std::string Execute() override {
        std::string output = "";
        for (auto const& c : lst) {
            output = "(" + output + std::to_string(value) + " + 1/" + c->Execute() + ")";
        }
        return (output);
    }
};

int main() {

    Component* leaf_1 = new Leaf(3);

    Component* box_1 = new Box(4);
    Component* box_2 = new Box(5);
    Component* box_3 = new Box(6);
    Component* box_4 = new Box(7);

    box_1->Add(leaf_1);
    box_2->Add(box_1);
    box_3->Add(box_2);
    box_4->Add(box_3);

    std::string output = box_4->Execute();
    std::cout << output << std::endl;

    return 0;
}
