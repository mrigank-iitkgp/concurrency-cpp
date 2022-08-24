#include <iostream>
#include <thread>
#include <future>
#include <utility>

using namespace std;


void doTheWork() {
    cout << "Processing the shared Data" << endl;
}

void waitingForWork(future < void >&& fut) {
    cout << "Worker thread is waiting for the work !!" << endl;
    fut.wait();
    doTheWork();
    cout << "Work is completed by the worker thread !!" << endl;
}

void setDataReady(promise < void >&& prom) {
    cout << "Data is ready. Proceed for Work !!" << endl;
    prom.set_value();
}

using namespace std;

int main() {
    cout << "Thread Sync using Promise and Future" << endl;

    promise < void > syncProm;
    future < void > syncFut = syncProm.get_future();
    thread t1(waitingForWork , move(syncFut));
    this_thread::sleep_for(chrono::seconds(2));
    thread t2(setDataReady , move(syncProm));

    t1.join();
    t2.join();
}