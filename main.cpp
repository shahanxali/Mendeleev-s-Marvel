#include <GL/glut.h>
#include<bits/stdc++.h>

using namespace std;


//creating the blueprint of the elements (properties)

class Element {
    private:
        int AtomicNumber;
        string AtomicName;
        string Symbol;
        vector<int> Color;
        vector<int> Range;

    public:
        //constructor to call and give the values to the properties each time called
        Element(int atomicNumber, const string& atomicName, const string& symbol, const vector<int>& color, const vector<int>& range) : AtomicNumber(atomicNumber), AtomicName(atomicName), Symbol(symbol), Color(color), Range(range) {}


};



//map creation for storing the corresponding name and number for faster fetch
//global because I have to use it in every functions
map<int, string> elementMap;


// Vector to store selected elements
vector<string> selectedElements;

//Vector to store indexes of selected element (for me the dev)
vector<int> indexel;

//vector to store cells selected for inputs handeling
vector<pair<int, int>> selectedCells;


//for counting consecutiveness, to be called in different function than where it is increamented so used global variable
int counting = 1;





//The function where all the data creation and all is happening
//basically  the brain of the program where the dataset is taken, objects creation, storing of data take place and constructors are called
void properties() {


    ifstream inputFile("datasets.txt");

    // // No use of handeling corner case as mouse click input is here

    //file error handling
    // if (!inputFile) {
    //     cerr << "Error: Failed to open the file." << endl;
    //     return;
    // }


    //Storing all the objects created in vector
    vector<Element> elements;


    //From this point to last of the funciton is to take data out of the dataset, basically the file hendelling 
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
        elementMap[atomicNumber] = symbol;   //VERY VERY IMPORTANT PART

    }

    inputFile.close();

    return;

}




//To generate random numbers, for both positioning of grids as well as data random selection
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

    // Shuffle the vector, for more randomness
    shuffle(uniqueNumbers.begin(), uniqueNumbers.end(), g);

    return uniqueNumbers;
}







//FRONTEND


//Global variables for fixed values like grid size and cell size
int gridSize = 6;
float cellSize = 1.0 / gridSize;

//Global variable for selection of rows and columns as it will be used everywhere in the program in different functions
//this will give mouse input address
int selectedRow = -1;
int selectedCol = -1;

//This can be called in main function but main reason was to store it globally
//so stored in a vector form
vector<int> randoms = generateUniqueRandomNumbers(36, 1, 40);



//This function will be called at the end of the game, that is to show the final result
void drawBlackScreen() {
    
    glutSetWindow(1);  // Switch to the second window
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set the background color to black
    

    // Print the integer in the middle of the black screen
    glColor3f(1.0, 1.0, 1.0);  // Set text color to white
    
    string countingString = to_string(counting);
    float xPos = 0.4;
    float yPos = 0.5;
    glRasterPos2f(xPos, yPos);


    //print the string
    string no = "your score is: ";
    for(char c: no){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }


    //print the score
    for (char c : countingString) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    
    glutPostRedisplay();
    
    
}





//The most important function of the program is drawgrid, not only it is giving the frontend, but also is prints, stores, calculate, call 
//all the main part of the program, it is just like the bone and heart of the program
void drawGrid() {


    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);  // Set the orthographic view

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //corner case for situation in case there is no input for so long and program execution goes on
    if (selectedRow == -1 || selectedCol == -1) {
        selectedElements.clear();
    }




    //The part of the code where all it is handelled, the grids are produced and placing randomly generated elements
    //and then posting on the screen
    for (int i = 0; i < gridSize; ++i) {
        vector<string> row;
        vector<int> row2;
        for (int j = 0; j < gridSize; ++j) {


            // Set a unique color for each grid cell
            if (i == selectedRow && j == selectedCol) {
                // Highlight the selected grid with a lighter color
                glColor3f((float)i / gridSize + 0.2, (float)j / gridSize + 0.2, 0.7);
            } else {
                glColor3f((float)i / gridSize, (float)j / gridSize, 0.5);
            }

            // Draw the square
            glBegin(GL_QUADS);
            glVertex2f(j * cellSize, i * cellSize);
            glVertex2f((j + 1) * cellSize, i * cellSize);
            glVertex2f((j + 1) * cellSize, (i + 1) * cellSize);
            glVertex2f(j * cellSize, (i + 1) * cellSize);
            glEnd();

            
            glColor3f(0.0, 0.0, 0.0);  // Set text color to black
            glRasterPos2f(j * cellSize + cellSize * 0.35, i * cellSize + cellSize * 0.5);

            // Store the selected elements in the vector
            if (i == selectedRow && j == selectedCol) {
                string currentElement = elementMap[randoms[(6 * i) + j]];
                int cur = randoms[(6 * i) + j];
                
                if (selectedElements.empty() || currentElement != selectedElements.back()) {
                    selectedElements.push_back(currentElement);
                    indexel.push_back(cur);
                }

            }


            //here is we tried to store the elements in the vector both elements as well as the indexes of the element 
            //for calculation ofcourse
            row.push_back(elementMap[randoms[(6 * i) + j]]);
            row2.push_back(randoms[(6 * i) + j]);

            //print the element name on the grid
            for (char c : row[j]) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
            }
        }
    }


    //because we dont want to check for the first selected element, cant be consecutive to previous
    if(selectedElements.size()>=2){
        
        //there where is check for consecutiveness, if yes then counting is increased
        //checking by already stored elements (indexel)
        //basically we are checking if the last element stoed in indexel is one + than second last element (consecutive)
        if(indexel[indexel.size()-1] == indexel[indexel.size()-2] + 1){
            //count +1
            counting++;
        }
        else{
            //if not consecutive, call this function which just gives you the result, this function is defined earlier
            drawBlackScreen();
        }
    }

    
    glFlush();
}



//taking mouse click input
void onMouseClick(int button, int state, int x, int y) {


    //if mouse button is pressed (DOWN)
    if (button == GLUT_LEFT_BUTTON && (state == GLUT_DOWN)) {

        // Convert mouse coordinates to grid indices
        selectedCol = x / (glutGet(GLUT_WINDOW_WIDTH) / gridSize);
        selectedRow = gridSize - y / (glutGet(GLUT_WINDOW_HEIGHT) / gridSize) - 1;
       
        // Add the clicked cell to the list of selected cells
        selectedCells.push_back(make_pair(selectedCol, selectedRow));

        // //By default called so no need
        // glutPostRedisplay();  // Trigger a redraw only on mouse click
    }
    
}

//called in main function to call the mouse input event
void initialize() {
    
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set the background color (white)
    glutMouseFunc(onMouseClick);
    
}

int main(int argc, char** argv) {

    //Creating objects and data extraction
    properties();

    //for frontends
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Mendeleev's Marvel");

    //for mouse click
    initialize();

    //main calculation and interface show
    glutDisplayFunc(drawGrid);
    
    glutMainLoop();

    return 0;
}


//At last, its over, Congratulations to me





