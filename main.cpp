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



     Element(int atomicNumber, const string& atomicName, const string& symbol, const vector<int>& color, const vector<int>& range) :
         AtomicNumber(atomicNumber), AtomicName(atomicName), Symbol(symbol), Color(color), Range(range) {}


};


//map creation for storing the corresponding name and number for faster fetch

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
    while (getline(inputFile, line)) {
        int atomicNumber;
        string atomicName, symbol;
        vector<int> color(3), range(3);

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

        elementMap[atomicNumber] = symbol;
    }

    inputFile.close();

    return;

}





vector<int> generateUniqueRandomNumbers(int count, int min, int max) {

    vector<int> uniqueNumbers;
    srand(time(0)); // Seed the random number generator with the current time

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

    random_device rd;
    mt19937 g(rd());

    // Shuffle the vector
    shuffle(uniqueNumbers.begin(), uniqueNumbers.end(), g);

    return uniqueNumbers;
}






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
            
            
            cout << setw(4) << row[j];
            cout << setw(1) << row2[j];
            

        }
        arr.push_back(row);

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
    
    properties();
    
    vector<vector<string>> check;
    vector<vector<int>> indexel;
    printingforback(check, indexel);
    
    inputoutput(check, indexel);


    return 0;
}

