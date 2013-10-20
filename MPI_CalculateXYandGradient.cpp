// MPI CODE 
//For after you've gotten you distance data stored as   (distance_in_cm*1,000,000 + time_in_ms*1000 + probe_ID)
//This collapse all needed data into a single number to fit into a 1D arrays - supercomputers like 1D arrays

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include "mpi.h"
using namespace std;


class XX{
public:
    XX(){}
    XX(int xx):x(xx){}
    int x;
};
class YY{
public:
    YY(){}
    YY(int yy):y(yy){}
    int y;
};
class gradient{
public:
    gradient(){}
    gradient(int gg):g(gg){}
    int g;
};
class FullGradient{
public:
    FullGradient(){}
    FullGradient(int ffgg):fg(ffgg){}
    int fg;
};


int main(){
    
    clock_t begin_time = clock();
    
    ifstream fin;
    fin.open("DataRun1.txt", ios::in);
    
    int d; //distance
    int x, y;
    char symbol=',';
    vector<XX> x_vec;
    vector<YY> y_vec;
    vector<gradient> g_vec;
    int g, j, numNodes, rank;
    
    MPI::Init();
    numNodes = MPI::COMM_WORLD.Get_size();
    rank= MPI::COMM_WORLD.Get_rank();
    
    if (rank!=0){
        while (!fin.eof()){
            fin>>d>>symbol;
            //remember that d is stored as distance_in_cm*1,000,000 + time_in_ms*1000 + probe_ID
            int d = d/1000000; //force integer division to get d back 
            
            x = d * 0.76;
            x = x*1000000 + time_in_ms*1000 + probe_ID; //don't forget to keep track of the other data
            x_vec.push_back(x);
            y = d * 0.65;
            y = y*1000000 + time_in_ms*1000 + probe_ID;
            y_vec.push_back(y);
            
        }
    
        for (int i=(rank-1)*x_vec.size()/numNodes+5; i<x_vec.size()/numNodes; i++){
            j = i-5;
            z = 1/1000000; 
            g = (x_vec[i-5]*z + x_vec[i-4]*z + x_vec[i-3]*z + x_vec[i-2]*z + x_vec[i-1]*z + x_vec[i]*z)/5 - 
                (y_vec[i-5]*z + y_vec[i-4]*z + y_vec[i-3]*z + y_vec[i-2]*z + y_vec[i-1]*z + y_vec[i]*z)/5;
            g *= -255;
            g = (g+225)/1; //force integer division
            g_vec[j] = g*1000000 + time_in_ms*1000 + probe_ID; //adds back the time and height information to the gradient value 
        
        }
        
        MPI_Send(g_vec, x_vec.size(), MPI_INT, 0, rank, MPI_COMM_WORLD);
    }
    

    if (rank==0){
        //gather data
        for (int ii=1; i<size; i++){
          MPI_Recv(g_Vec, x_vec.size(), MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          FullGradient.pushback(g_Vec);
        }
        //we don't need to worry about the order within this vector, 
        //because part of each value holds the probe height and the time


    }
    
    MPI_Finalize();
    
 
    return 0;
}





