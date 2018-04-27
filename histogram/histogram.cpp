/* 
* ========================================
* [] File Name : histogram.cpp
*
* [] Creation Date : April 2018
*
* [] Author 2 : Ali Gholami
* ========================================
*/


#include <iostream>

using namespace std;

int main() {

    // Define an array
    int size = 10;
    int* array = new int[size] {1, 2, 4, 5, 6, 3, 4, 2, 6, 7};



    // Iterate the array and print
    int max = 0;
    for(int i=0; i<sizeof(array); i++) {

        // Update max in case
        if(array[i] > max) max = array[i];

        cout << array[i] << endl;
    }

    // Define the Histogram
    int* histogram = new int[max] {0};

    // Do the Histogram
    for(int i=0; i<sizeof(array); i++) {
        int index = array[i];
        histogram[index]++;
    }

    // Print the Histogram
    for(int i=0; i<sizeof(histogram); i++) {
        cout << "["<< i <<"]: " << histogram[i] << endl;
    }

    delete [] array;
    delete [] histogram;

    return 0;
}