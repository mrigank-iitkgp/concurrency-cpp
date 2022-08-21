#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

thread_local string s = "Hello from ";
mutex coutMutex;

void printThreadName(const string& fromThread) {
    s += fromThread;
    lock_guard < mutex > coutLock(coutMutex);
    cout << s << endl;
    cout << "Address of string : " << &s << endl;
}

int main() {
    cout << "Demonstration of std::thread_local !!" << endl;

    thread t1(printThreadName , "T1");
    thread t2(printThreadName , "T2");
    thread t3(printThreadName , "T3");
    thread t4(printThreadName , "T4");

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}