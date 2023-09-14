#include <iostream>
#include <string>
#include <vector>
using namespace std;



//creating the blueprint of the elements (properties)

class Element {
public:
    int AtomicNumber;
    string AtomicName;
    string Symbol;
    vector<int> Color;
    vector<int> Range;

};



//function to call and assign values when called

Element create(int atomicNumber, const string& atomicName,string symbol, const vector<int>& color, const vector<int>& range) {
    Element element;
    element.AtomicNumber = atomicNumber;
    element.Symbol = symbol;
    element.AtomicName = atomicName;
    element.Color = color;
    element.Range = range;
    return element;
}


// Declare elements as global variable

Element hydrogen; 
Element helium;
Element lithium;

map<int,string>periodictable;
periodictable=[1:"hydrogen",2:"helium",3:"lithium"];



//to assign all the elements as call one by one to give every element properties

void properties() {
    hydrogen = create(1, "Hydrogen", "H", {1, 1, 1}, {1, 0, 0});
    helium = create(2, "Helium", "He", {0, 0, 255}, {0, 0, 0});
    lithium = create(3, "Lithium", "Li", {0, 0, 55}, {0, 1, 0});

}





//Start rendering all the called elements








//main function

int main() {
    
    properties();
    
    


    return 0;
}

