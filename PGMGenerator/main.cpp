#include <iostream>
#include <fstream>
#include <cmath>

#define SIZE 400

using namespace std;

int generateFile(int shapes);
int placeRectangle(int x, int y, int width, int height, int grayscale);
int placeCircle(int x, int y, int radius, int grayscale);
int placeTriangle(int x, int y, int height, int grayscale);
int resetPixels();
int fillPGM();

ofstream outputShapes;
ofstream output;
int pixels[SIZE][SIZE];

int main(int argc, char *argv[]) {
    //Build white canvas
    resetPixels();

    //Check that user gave correct # of arguments
    if(argc != 3){
        cout << "incorrect # of files where given, exiting program";
        return 0;
    }


//    int shapes;
//    outputShapes.open("shapeSpecFile.txt", ofstream::out);
//
//    cout << "how many shapes?";
//    cin >> shapes;
//    generateFile(shapes);
//    outputShapes.close();

    //Open users shape file, quit if not open
    ifstream input;
    input.open(argv[1], ifstream::in);
    if(!input.is_open()){
        cerr << "1st parameter shape file not accepted, terminating..." << endl;
        return 0;
    }

    //Create user specified output pgm file, quit if not open
    output.open(argv[2], ofstream :: out);
    if(!input.is_open()){
        cerr << "2nd parameter PGM file failed to open, terminating..." << endl;
        return 0;
    }
    output << "P2" << endl << "400 400" << endl << 255 << endl;

    //Read through shape file & create each shape
    while(input){
        string shape;
        int x, y, width, height, grayscale;
        input >> shape;

        //call appropriate shape placing algorithm
        if (shape == "rectangle"){
            input >> x >> y >> width >> height >> grayscale;
            if(grayscale > 399 || grayscale < 0) grayscale = rand()%255; //correct bad grayscale
            placeRectangle(x,y,width,height,grayscale);

        }else if(shape == "square"){
            input >> x >> y >> width >> grayscale;
            if(grayscale > 399 || grayscale < 0) grayscale = rand()%255; //correct bad grayscale
            placeRectangle(x,y, width, width, grayscale);//pass width for x & y

        }else if(shape == "circle"){
            input >> x >> y >> width >> grayscale;
            if(grayscale > 399 || grayscale < 0) grayscale = rand()%255; //correct bad grayscale
            placeCircle(x,y,width,grayscale);

        }else{//triangle if shape name is bad or is a triangle
            input >> x >> y >> width >> grayscale;
            if(grayscale > 399 || grayscale < 0) grayscale = rand()%255; //correct bad grayscale
            placeTriangle(x, y, width, grayscale);
        }

    }

    fillPGM();      //fill the pgm file with the values stored in the pixel array
    output.close(); //close files
    input.close();
    cout << "complete!" << endl;
    return 0;
}

//takes in starting point of x,y and fills out the rectangle with the grayscale value
int placeRectangle(int x, int y, int width, int height, int grayscale){
    for(int i = y; i < y + height; i++){
        for(int j = x; j < x + width; j++){
            if(j > 399 || j < 0) break; //exit if out of bounds
            if(i > 399 || i < 0) break;
            pixels[i][j] = grayscale;
        }
    }
    return 0;
}

//takes in starting point (x,y) and fills out the square if the point is within the circle
int placeCircle(int x, int y, int radius, int grayscale){
    double centerX = radius + x;
    double centerY = radius + y;

    for(int i = y; i < y + radius *2; i++){
        for(int j = x; j < x + radius*2; j++){
            if(j > 399 || j < 0) break; //exit if out of bounds
            if(i > 399 || i < 0) break;
            //do nothing if the point is not within the circle
            if( sqrt( pow((j - centerX),2) +  pow((i - centerY),2)) <= radius){
                pixels[i][j] = grayscale;
            }

        }
    }
    return 0;
}

//takes in starting point (x,y) and fills out the square if the point is within the triangle
int placeTriangle(int x, int y, int size, int grayscale){
    int layer = 0;
    int midX;
    midX = x + size/2;

    for(int i = y; i < y + size/2; i++){
        for(int j = x; j < x + size; j++){
            if(j > 399 || j < 0) break; //exit if out of bounds
            if(i > 399 || i < 0) break;
            if(abs(midX - j) <= layer){ //check distance from growing center
                pixels[i][j] = grayscale;
            }
        }
        layer ++;
    }
    return 0;
}

//randomly generate a shape.txt file
int generateFile(int shapes){
    while(shapes > -1){
        int range = rand()%4; //pick random shape 0-3

        switch (range){
            case 0:
                outputShapes << "rectangle " << rand()%400 << " " << rand()%400 << " " << rand()%50 << " "  << rand()%50 << " "  << rand()%255 << endl;
                break;
            case 1:
                outputShapes << "square " << rand()%400 << " " << rand()%400 << " " << rand()%30 << " " << rand()%255 << endl;
                break;
            case 2:
                outputShapes << "circle " << rand()%400 << " " << rand()%400 << " " << rand()%30 << " " << rand()%255 << endl;
                break;
            case 3:
                outputShapes << "triangle " << rand()%400 << " " << rand()%400 << " " << rand()%50 << " " << rand()%255 << endl;
                break;
            default:
                break;
            }
        shapes --;
    }
    return 0;
}

int resetPixels(){
    for(int i = 0; i < 400; i++){
        for(int j = 0; j < 400; j++){
            pixels[i][j] = 255;
        }
    }
    return 0;
}

//write the pixels array to the output.PGM file
int fillPGM(){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            output << pixels[i][j] << endl;
        }
    }
    return 0;
}

