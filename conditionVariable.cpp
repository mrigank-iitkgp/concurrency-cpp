#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex mt;
condition_variable cv;
bool dataReady = false;

void doTheWork() {
    cout << "Processing the shared Data" << endl;
}

void waitingForWork() {
    cout << "Worker thread is waiting for the work !!" << endl;
    unique_lock < mutex > workerLock(mt);
    cv.wait(workerLock , []{return dataReady;});
    doTheWork();
    cout << "Work is completed by the worker thread !!" << endl;
}

void setDataReady() {
    {
        lock_guard < mutex > lk(mt);
        dataReady = true;
    }
    cout << "Data is ready. Proceed for Work !!" << endl;
    cv.notify_one();
}

using namespace std;

int main() {
    cout << "Demonstration of Condition Variable !!" << endl;

    thread t1(waitingForWork);
    this_thread::sleep_for(chrono::seconds(2));
    thread t2(setDataReady);

    t1.join();
    t2.join();
}