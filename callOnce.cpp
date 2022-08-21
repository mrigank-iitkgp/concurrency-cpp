#include <iostream>
#include <thread>
#include <mutex>
#include <string>

using namespace std;

once_flag onceFlag;

void doOnce(const string& s) {
    call_once(onceFlag , [&] {cout << "Only once by thread " << s << " of id : " << this_thread::get_id();});
}

int main() {
    cout << "Demonstration of std::call_once & std::once_flag" << endl;

    thread t1(doOnce , "T1");
    thread t2(doOnce , "T2");
    thread t3(doOnce , "T3");
    thread t4(doOnce , "T4");

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}