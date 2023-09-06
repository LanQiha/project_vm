#ifndef OBJECT_H
#define OBJECT_H

// Object is an abstract class
class Object
{
    public:
        virtual void Draw() = 0; // "= 0" indicates that the function is a pure virtual function
        virtual void Update(float dt) = 0;
        virtual void Clean() = 0;
};

#endif

/*
VIRTUAL FUNCTIONS
Virtual functions have an implementation in the base class,
derived classes can choose to override (provide their own implementation) the virtual function

PURE VIRTUAL FUNCTIONS
Pure virtual functions do not have an implementation in the base class and must be overridden by derived classes

void Function() override {
    // Derived class implementation
}
*/
