#include <iostream>
#include <thread>
using namespace std;

int main() {
    cout << "Demonstration of thread methods starts from here!!" << endl;

    cout << "Hardware concurrency of this machine is " << thread::hardware_concurrency() << endl;

    thread t1([]{cout << "Thread t1 id = " << this_thread::get_id() << endl;});
    thread t2([]{cout << "Thread t2 id = " << this_thread::get_id() << endl;});

    cout << endl;

    cout << "From main id of t1 = " << t1.get_id() << endl;
    cout << "From main id of t2 = " << t2.get_id() << endl;

    swap(t1 , t2);

    cout << "Swapping of thread are done!!" << endl;

    cout << "From main id of t1 = " << t1.get_id() << endl;
    cout << "From main id of t2 = " << t2.get_id() << endl;

    cout << "id of main thread = " << this_thread::get_id() << endl;

    cout << "t1 is joinable = " << t1.joinable() << endl;
    cout << "t2 is joinable = " << t2.joinable() << endl;

    t1.join();
    t2.join();
    cout << "Thread joinings are complete!!" << endl;
    cout << "t1 is joinable = " << t1.joinable() << endl;
    cout << "t2 is joinable = " << t2.joinable() << endl;
}