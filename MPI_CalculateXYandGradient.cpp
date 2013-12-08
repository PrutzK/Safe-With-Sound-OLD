//Written in MPI, try first with 2-4 processors for testing

//For after you've gotten you distance data stored as (distance_in_cm*1,000,000 + time_in_ms*1,000 + probe_ID)
//This collapse all needed data into a single number to fit into a 1D array - supercomputers like 1D arrays

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <math.h>
using namespace std;

int main()
{
    int x, y, old_y, gradient;
    int theta = 15;
    
    //Arrays of distances for each probe
    int Probe1[100]; //highest probe
    int Probe2[100];
    int Probe3[100];
    int Probe4[100];
    int Probe5[100];
    int Probe6[100];
    int Probe7[100];
    int Probe8[100]; //lowest probe
    
    
    for (int data = 1; data <= 100; data++){
    //take the distance and calculate the x distance
    //x distance will tell you where to begin drawing horizontal line
        x = Probe1[data]*cos(theta);
    //calculate y and gradient
    //y will decide the gradient for the line
        y = Probe1[data]*sin(theta);
        if ((y - old_y)>0){
            if ( (255*(y-old_y)/old_y) > (255-255*(y-old_y)/old_y) )
                gradient = 255*(y-old_y)/old_y; 
            else if ( (255*(y-old_y)/old_y) < (255-255*(y-old_y)/old_y) )
                gradient = 255-255*(y-old_y)/old_y;
        }
        else if ((y - old_y)<0){
            if ((255*(old_y-y)/old_y)<(255-255*(old_y-y)/old_y))
                gradient = 255*(y-old_y)/old_y;
            else if ((255*(old_y-y)/old_y)>(255-255*(old_y-y)/old_y))
                gradient = 255-255*(y-old_y)/old_y;
        }
        

    //draw the line starting at x with gradient g(y)
    //top left corner of drawing is (0,0) - will draw 1/2 of face which will be duplicated and flipped, assumes symmetry until I can control noise when probes are used on both sides
    //probe 1 will draw horizontal line at y = 5
    //probe 2, y = 10 and so on - for the initial test
    
    }
    
    
    
    return 0;
}







