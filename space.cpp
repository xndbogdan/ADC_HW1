//ALSO UPLOADED ON https://pastebin.com/0qHUCN1c
#include <iostream>
#include <fstream>

using namespace std;
#define INTMAX INT32_MAX;
ifstream fin;
ofstream fout;

void pause() {
    //would've used windows.h and 'pause' cmd command, but I wanted this to also compile on linux
    cout << "Press any key to continue";
    cin.get();
}

void cpyvector(int target[], int source[], int n) //for equal vectors only!
{
    for (int i = 0; i < n; i++) {
        target[i] = source[i];
    }
}

int wrap_around(int n, int nr_elem) {
    while (n < 0) n = nr_elem + n;
    while (n > nr_elem - 1) n = n - nr_elem;
    return n;
}

int maxdist(int starting_planet, int n_planets, int fuel, int cost_vector[]) {
    int current_planet = starting_planet;
    int visited = 0;
    bool can_go = true;
    //GOTO-RIGHT
    while (can_go) {
        if (fuel >= cost_vector[current_planet]) {
            visited++;
            fuel -= cost_vector[current_planet];
            cost_vector[current_planet] = INTMAX;
            current_planet = wrap_around(current_planet + 1, n_planets);
        } else can_go = false;
    }
    visited++; //consider last planet visited
    return visited;
}

int maxdist_rev(int starting_planet, int n_planets, int fuel, int cost_vector[]) {
    int current_planet = starting_planet;
    int visited = 0;
    bool can_go = true;
    //GOTO-RIGHT
    while (can_go) {
        if (fuel >= cost_vector[wrap_around(current_planet - 1, n_planets)]) {
            visited++;
            fuel -= cost_vector[wrap_around(current_planet - 1, n_planets)];
            cost_vector[wrap_around(current_planet - 1, n_planets)] = INTMAX;
            current_planet = wrap_around(current_planet - 1, n_planets);
        } else can_go = false;
    }
    visited++; //consider last planet visited
    return visited;
}

int main() {
    int n_planets;
    fin.open("space.in");
    if (fin.fail()) {
        cout << "Cannot open input file. Exiting\n";
        pause();
        return EXIT_FAILURE;
    }
    fin >> n_planets;
    int cost_vector[n_planets];
    int cost_vetor_cpy[n_planets];

    int dummy;
    fin >> dummy; //We don't need number of queries since we read until the end

    for (int i = 0; i < n_planets; i++) {
        fin >> cost_vector[i];
        cost_vetor_cpy[i] = cost_vector[i];
    }

    int starting_planet;
    int fuel;

    fout.open("space.out");
    while (fin >> starting_planet) {
        fin >> fuel;
        //goto-right
        int visited1 = maxdist(starting_planet, n_planets, fuel, cost_vector);
        cpyvector(cost_vector, cost_vetor_cpy, n_planets);
        //goto-left
        int visited2 = maxdist_rev(starting_planet, n_planets, fuel, cost_vector);
        visited1 > visited2 ? fout << visited1 << endl : fout << visited2 << endl;
    }
    fin.close();
    fout.close();
    return EXIT_SUCCESS;
}