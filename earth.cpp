#include <iostream>
#include <fstream>
using namespace std;

ifstream fin;
ofstream fout;
int min_cost=INT32_MAX;
int R,D,S; // R - Max dist, D - Distance to travel, S - NUMBER OF SHIPYARDS

struct shipyard {
    int p=0,c=0,r=0; //distance from 0, cost, max range
};

shipyard shipyards[1000];

void pause() {
    //would've used windows.h and 'pause' cmd command, but I wanted this to also compile on linux
    cout << "Press any key to continue";
    cin.get();
}

void travel(int traveled, int money_spent, int max_dist, int current_shipyard=-1)
{
    if(traveled+max_dist>=D) {
        if(money_spent<min_cost) {
            min_cost=money_spent;
        }
    }
    int i=1;
    bool valid=true;
    while(valid){
        if(current_shipyard+i<S) {
            if(max_dist>=shipyards[current_shipyard+i].p-traveled){
                travel(shipyards[current_shipyard+i].p, money_spent+shipyards[current_shipyard+i].c, shipyards[current_shipyard+i].r , current_shipyard+i);
            }
            else valid=false;

        } else {
            valid=false;
        }
        i++;

    }

}

int main() {


    fin.open("earth.in");

    if(fin.fail()) {
        cout<<"Cannot open input file. Exiting\n";
        pause();
        return EXIT_FAILURE;
    }

    fin>>R>>D>>S;
    for(int i=0;i<S;i++){
        fin>>shipyards[i].p;
        fin>>shipyards[i].c;
        fin>>shipyards[i].r;
    }
    fin.close();
    travel(0,0,R);
    fout.open("earth.out");
    if(min_cost==INT32_MAX) {
        fout<<"-1";
    } else {
        fout<<min_cost;
    }
    fout.close();
    return EXIT_SUCCESS;
}