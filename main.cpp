#include<bits/stdc++.h>
using namespace std;



//creating the blueprint of the elements (properties)

class Element {
public:
    int AtomicNumber;
    string AtomicName;
    string Symbol;
    vector<int> Color;
    vector<int> Range;


    //constructor to call and give the values to the properties each time called
    Element(int atomicNumber, const string& atomicName, const string& symbol, const vector<int>& color, const vector<int>& range) : AtomicNumber(atomicNumber), AtomicName(atomicName), Symbol(symbol), Color(color), Range(range) {}


};



//map creation for storing the corresponding name and number for faster fetch
//global because i have to use it in every functions
map<int, string> elementMap;




void properties() {


    ifstream inputFile("datasets.txt");

    //file error handling
    // if (!inputFile) {
    //     cerr << "Error: Failed to open the file." << endl;
    //     return;
    // }

    vector<Element> elements;

    string line;

    //while till last read dataset text line by line
    while (getline(inputFile, line)) {

        int atomicNumber;
        string atomicName, symbol;
        vector<int> color(3), range(3);

        //split each line into elements
        istringstream iss(line);
        iss >> atomicName >> atomicNumber >> symbol;
        for (int i = 0; i < 3; i++) {
            iss >> color[i];
        }
        for (int i = 0; i < 3; i++) {
            iss >> range[i];
        }

        Element element(atomicNumber, atomicName, symbol, color, range);
        elements.push_back(element);

        //hasmap storage of atomic number and its symbol
        elementMap[atomicNumber] = symbol;

    }

    inputFile.close();

    return;

}





vector<int> generateUniqueRandomNumbers(int count, int min, int max) {

    vector<int> uniqueNumbers;
    srand(time(0)); // Seed the random number generator with the current time (different random generation everytime you call)

    // Generate at least 5 consecutive numbers
    int randomNumfirst = rand() % ((max -5) - min + 1) + min;
    for (int i = randomNumfirst; i < randomNumfirst+5; i++) {
        uniqueNumbers.push_back(min + i);
    }

    // Generate the remaining random numbers
    while (uniqueNumbers.size() < count) {
        int randomNum = rand() % (max - min + 1) + min;

        // Check if the random number is not already in the list
        if (find(uniqueNumbers.begin(), uniqueNumbers.end(), randomNum) == uniqueNumbers.end()) {
            uniqueNumbers.push_back(randomNum);
            
        }
    }


    //this code sets up a random number generator (mt19937) and
    //seeds it with a value from a hardware-based source of random entropy (random_device).
    //This is a common way to generate random numbers with good statistical properties for various applications.
    //and it is better than rand() function as it generates higher quality random numbers that is repeatation takes times.
    random_device rd;
    mt19937 g(rd());

    // Shuffle the vector
    shuffle(uniqueNumbers.begin(), uniqueNumbers.end(), g);

    return uniqueNumbers;
}





//print the grids in the terminal
int printingforback(vector<vector<string>>& arr, vector<vector<int>>& indexel){
    cout<<"  ";
    for(int i=0;i<6;i++){
        cout<<setw(5)<<i;
    }

    vector<int> randoms = generateUniqueRandomNumbers(36, 1, 40);


    for(int i=0;i<6;i++){
        vector<string> row;
        vector<int> row2;
        for(int j=0;j<6;j++){
            if(j==0){
                int k=i+65;
                cout<<"\n"<<i<<" ";
            }
            
            row.push_back(elementMap[randoms[(6 * i) + j]]);

            row2.push_back(randoms[(6 * i) + j]);
            
            
            cout << setw(4) << row[j]; //setw() function gives fixed space for each time it is called.
            cout << setw(1) << row2[j];
            

        }

        //for user
        arr.push_back(row);

        //for developer
        indexel.push_back(row2);
    }
    cout<<"\n";
    return 0;
}



int inputoutput(vector<vector<string>> arr, vector<vector<int>> indexel){

    int a,b;
    cout<<"Enter the Index: ";
    cin>>a>>b;


    int current = indexel[a][b]; // Initialize the current number
    
    int consecutiveCount = 0; // Initialize the consecutive count

    while (true) {
        cout << "Enter the next index: ";
        int userInput1,userInput2;
        cin >> userInput1 >> userInput2;

        if (indexel[userInput1][userInput2] == current + 1) {
            current = indexel[userInput1][userInput2]; // Update the current number
            
            consecutiveCount++; // Increment the consecutive count
        } 
        else {
            break; // Exit the loop when a non-consecutive number is provided
        }
    }

    cout << "Your score: " << consecutiveCount + 1 << " consecutive numbers" << endl;


    return 0;

}






//Start rendering all the called elements









//main function

int main() {
    
    properties(); //dataset reading and creation of all the object with the name of each elements from the periodic table;
    
    vector<vector<string>> check; //storing to print and watch in the terminal
    vector<vector<int>> indexel; //storing for me (developer) to get element name to number or number to element;

    printingforback(check, indexel); //print in terminal
    
    inputoutput(check, indexel); //take input and check the input or outputl


    return 0;
}



//In the end it doesnt even matter
