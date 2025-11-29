#include<iostream>
//overloading += and -= operators to work with custom data types

using namespace std;

class Marks {
    int mark;
    public:
        Marks() {
            mark = 0;
        }
        Marks(int m) {
            mark = m;
        }
        
        void YourMarkPlease() {
            cout << "Your mark is : " << mark << endl;
        }

        //overloading

        void operator+=(int bonusMark) { //current object will be passed implicitly, and we are adding bonusMark to the object
            mark = mark + bonusMark;
        }

        //ovrloading -= using friend function : here the current object will not be passed implicitly. So we need to specify it as a parameter.
        friend void operator-=(Marks &curobj, int ufmDeduction) {
            curobj.mark -= ufmDeduction;
        } //complete this tomorrow
};