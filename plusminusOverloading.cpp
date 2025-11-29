#include <iostream>

using namespace std;

class Marks{
    int intmark;
    int extmark;
    public:
        Marks(){ //default constructor
            intmark = 0;
            extmark = 0;
        }

        Marks(int im, int em){
            intmark = im;
            extmark = em;
        }

        void display() {
            cout << intmark << endl << extmark << endl;
        }

        //Overloading the "+" operator. To do this, we have to use the operator method that is executed when we use the operator
        Marks operator+(Marks m) {
            Marks temp;
            temp.intmark = intmark + m.intmark;
            temp.extmark = extmark + m.extmark;
            return temp; 
        } //there's only one parameter here because when an op function is a member function, the first parameter is automatically passed as the current object (intmark and extmark). But when the function is a friend function and not a member function like this one, both parameters have to be passed.

        Marks operator-(Marks m); //declaring operator
};

//defining operator function for overloading (outside the class)
Marks Marks :: operator-(Marks m1) {
    Marks temp;
    temp.intmark = intmark - m1.intmark;
    temp.extmark = extmark - m1.extmark;
    return temp;
}

int main() {
    //op overloading is useful when you want operators to work with custom built objects
    //To do this, we have to create operator functions (could be a member of the class or not). using keyword operator
    Marks m1(10, 20), m2(30, 40);

    Marks m3 = m1 + m2; //m1 will call the operator function => it'll be the current object, and will be passed automatically, therefore only one parameter is passed in the function declaration. 
    Marks m4 = m1 - m2; 
    
    m3.display();
    m4.display();
    return 0;
}