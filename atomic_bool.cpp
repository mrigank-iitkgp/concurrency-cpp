#include<iostream>
#include<thread>
#include<atomic>
#include<vector>
#include<chrono>
using namespace std;

vector < int > shared_values;
atomic_bool flag(false);

void setData()
{
    cout << "Waiting" << endl;
    while(!flag)
    {
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    shared_values[1] = 5;
    cout << "Work done" << endl;
}

void getData()
{
    cout << "Getting Data in progress" << endl;
    shared_values.push_back(1);
    shared_values.push_back(1);
    shared_values.push_back(1);
    for(auto x : shared_values)
    {
        cout << x << " ";
    }
    cout << endl;
    flag = true;
    cout << "Data Read complete" << endl;
}


int main()
{

    thread t1(getData);
    thread t2(setData);

    t1.join();
    t2.join();

    for(auto x : shared_values)
    {
        cout << x << " ";
    }
    cout << endl;
}