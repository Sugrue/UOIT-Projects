#include <iostream>;
using namespace std;

int main() {

    //Declaring variables, intN is the number inputted by the user, intSquare holds the square of a particular number and intCube holds the cube
    float intN,i, intSquare = 0, intCube = 0;

    //Request input from the user
    cout<<"Please enter the number of cubes and squares you wish to calculate"<<endl
    <<"N = ";

    //Stores input
    cin>>intN;

    //Calculates and stores the sum of all squares and cubes up to the number inputted by the user
    for(i = 1; i<= intN; i++) {
        intSquare += pow(i, 2);
        intCube += pow(i, 3);
    }

    //Outputs the calculated values to the user
    cout<<"The addition of all cube between 1 and "<<intN<<" is "<<intCube<<endl
    <<"The addition of all squares between 1 and " <<intN<<" is "<<intSquare<<endl;


    system("Pause");
    return 0;
}
