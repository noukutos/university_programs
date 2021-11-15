#include <algorithm>
#include <iostream>
#include <list>
#include <string>
class Component {
protected:
    int a;
    int b;
    std::list<Component*> lst;
public:
    virtual std::string Execute() { return (""); };
    void Add(Component* child) {
        lst.push_back(child);
    }
};

class Leaf : public Component {
public:
    Leaf(int a_, int b_ = NULL){
        this->a = a_;
    }
    std::string Execute() override {
        return (std::to_string(a));
    }
};

class Box : public Component {
public:
    Box(int a_, int b_ = NULL){
        this->a = a_;
        if (b_ != NULL) {
            this->b = b_;
        }
        else {
            this->b = 1;
        }
    }
    std::string Execute() override {
        std::string output = "";
        for (auto const& c : lst) {
            output = "(" + output + std::to_string(a) + " + " + std::to_string(b) + "/" + c->Execute() + ")";
        }
        return (output);
    }
};

class IFractionBuilder{
protected:
    Component* box;
public:
    virtual void SetFraction(int arr_a[], int n, int arr_b [] = NULL) = 0;
    std::string GetFraction() {
        return(this->box->Execute());
    }
};

class SimpleFractionBuilder : public IFractionBuilder{
public:
    void SetFraction(int arr_a[], int n, int arr_b [] = NULL) override {

        Component* leaf = new Leaf(arr_a[n-1]);
        this -> box = new Box(arr_a[n-2]);
        this->box->Add(leaf);

        for (int i = n - 3; i > 0; i--) {
            Component* box_new = new Box(arr_a[i]);
            box_new->Add(box); 
            box = box_new;
            if (i == 1) {
                this->box = box_new;
            }
        }
    }
};

class ComplexFractionBuilder : public IFractionBuilder {
public:
    void SetFraction(int arr_a[], int n, int arr_b[]) override {

        Component* leaf = new Leaf(arr_a[n - 1]);
        this->box = new Box(arr_a[n - 2], arr_b[n - 2]);
        this->box->Add(leaf);

        for (int i = n - 3; i > 0; i--) {
            Component* box_new = new Box(arr_a[i], arr_b[i]);
            box_new->Add(box);
            box = box_new;
            if (i == 1) {
                this->box = box_new;
            }
        }
    }
};

int main() {

    int arr1[] = {2, 3, 4, 5, 6, 7};
    int n = 6;
    IFractionBuilder* builder1 = new SimpleFractionBuilder;
    builder1->SetFraction(arr1, n);
    std::cout << builder1->GetFraction();

    int arr2[] = { 2, 3, 4, 5, 6, 7 };
    int arr3[] = { 2, 3, 4, 5, 6};
    int n1 = 6;
    IFractionBuilder* builder2 = new ComplexFractionBuilder;
    builder2->SetFraction(arr2, n1, arr3);
    std::cout <<"\n" + builder2->GetFraction();

    return 0;
}
