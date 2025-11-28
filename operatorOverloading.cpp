#include<iostream>
#include<string>
using namespace std;

struct keyboard{
    string brand;
    string model;
    
    
    keyboard(string b, string m) {
        brand = b;
        model = m;
    }
};

void operator<<(ostream& COUT, keyboard& K1) {
    COUT << "Brand : " << K1.brand;
    COUT << "Model : " << K1.model;
}

int main () {
    keyboard k1 = 
    keyboard("Cosmicbyte", "Artemis");
    cout<<k1;
}
