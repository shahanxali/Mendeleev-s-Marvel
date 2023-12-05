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
//global because i have to use it in every functions
map<int, string> elementMap;


// Vector to store selected elements
vector<string> selectedElements;
vector<int> indexel;

vector<pair<int, int>> selectedCells;

int counting = 1;

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









int gridSize = 6;
float cellSize = 1.0 / gridSize;
int selectedRow = -1;
int selectedCol = -1;

vector<int> randoms = generateUniqueRandomNumbers(36, 1, 40);

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



    string no = "your score is: ";
    for(char c: no){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    for (char c : countingString) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    
    glutPostRedisplay();
    
    
}




void drawGrid() {


    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);  // Set the orthographic view

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (selectedRow == -1 || selectedCol == -1) {
        selectedElements.clear();
    }

    for (int i = 0; i < gridSize; ++i) {
        vector<string> row;
        vector<int> row2;
        for (int j = 0; j < gridSize; ++j) {

            // Check if the current cell is in the list of selected cells
            auto it = find(selectedCells.begin(), selectedCells.end(), make_pair(i, j));
            if (it != selectedCells.end()) {
                // Highlight the selected grid with a lighter color
                glColor3f(0.7, 0.7, 0.2); // Adjust the color as needed
            } else {
                // Set the default color
                glColor3f((float)i / gridSize, (float)j / gridSize, 0.5);
            }

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

            row.push_back(elementMap[randoms[(6 * i) + j]]);
            row2.push_back(randoms[(6 * i) + j]);

            for (char c : row[j]) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
            }
        }
    }



    if(selectedElements.size()>=2){
        
        if(indexel[indexel.size()-1] == indexel[indexel.size()-2] + 1){
            
            counting++;
        }
        else{

            drawBlackScreen();
        }
    }

    
    
    glFlush();
}

void onMouseClick(int button, int state, int x, int y) {



    if (button == GLUT_LEFT_BUTTON && (state == GLUT_DOWN)) {
        // Convert mouse coordinates to grid indices
        selectedCol = x / (glutGet(GLUT_WINDOW_WIDTH) / gridSize);
        selectedRow = gridSize - y / (glutGet(GLUT_WINDOW_HEIGHT) / gridSize) - 1;
       
        // Add the clicked cell to the list of selected cells
        selectedCells.push_back(make_pair(selectedCol, selectedRow));

        // glutPostRedisplay();  // Trigger a redraw only on mouse click
    }
    
}


void initialize() {
    
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set the background color (white)
    glutMouseFunc(onMouseClick);
    
}

int main(int argc, char** argv) {

    properties();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600); // Adjust the window size as needed
    glutCreateWindow("Mendeleev's Marvel");

    initialize();

    glutDisplayFunc(drawGrid);
    
    glutMainLoop();

    return 0;
}
