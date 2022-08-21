// Solving the deadlock problem in deadlocks.cpp

/*
Problem is solved using std::unique_lock and defer_lock locking strategy
*/

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;

struct CriticalData {
    mutex mut;
};

void deadlock(CriticalData& a , CriticalData& b) {
    unique_lock < mutex > lk1(a.mut , defer_lock);
    cout << "Get the first mutex and thread id is : " << this_thread::get_id() << endl;
    this_thread::sleep_for(chrono::milliseconds(1));
    unique_lock < mutex > lk2(b.mut , defer_lock);
    cout << "Get the second mutex and thread id is : " << this_thread::get_id() << endl;

    cout << "Both mutex and thread id is : " << this_thread::get_id() << endl;
    lock(lk1 , lk2);
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