#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;

struct CriticalData {
    mutex mut;
};

void deadlock(CriticalData& a , CriticalData& b) {
    a.mut.lock();
    cout << "Get the first mutex and thread id is : " << this_thread::get_id() << endl;
    this_thread::sleep_for(chrono::milliseconds(1));
    b.mut.lock();
    cout << "Get the second mutex and thread id is : " << this_thread::get_id() << endl;

    a.mut.unlock();
    b.mut.unlock();
}

int main() {
    cout << "Demonstration of deadlock!!" << endl;

    CriticalData a;
    CriticalData b;

    thread t1([&]{deadlock(a , b);});
    thread t2([&]{deadlock(b , a);});

    t1.join();
    t2.join();
}