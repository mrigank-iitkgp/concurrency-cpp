#include<iostream>
#include<thread>
#include<vector>
using namespace std;

vector < int > sharedWork;
atomic < bool > dataProduced(false);
atomic < bool > dataConsumed(false);


void dataProducer()
{
    sharedWork={ 1 , 0 , 3 };
    dataProduced.store(true , memory_order_release);
}

void deliveryBoy()
{
    while(!dataProduced.load(memory_order_acquire));
    dataConsumed.store(true , memory_order_release);
}

void dataConsumer()
{
    while(!dataConsumed.load(memory_order_acquire));
    sharedWork[1] = 2;
}

int main()
{
    thread t1(dataConsumer);
    thread t2(deliveryBoy);
    thread t3(dataProducer);

    t1.join();
    t2.join();
    t3.join();

    for(auto x : sharedWork)
    {
        cout << x << endl;
    }
}