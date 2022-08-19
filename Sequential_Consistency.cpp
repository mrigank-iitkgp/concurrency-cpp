#include<iostream>
#include<atomic>
#include<thread>
#include<string>
using namespace std;

string work;
atomic < bool > ready(false);

void consumer()
{
    while(!ready);
    cout << work << endl;
}

void producer()
{
    work = "done";
    ready = true;
}

int main()
{
    thread prod(producer);
    thread cons(consumer);
    prod.join();
    cons.join();
}