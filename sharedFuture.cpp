#include <iostream>
#include <future>
#include <thread>
#include <mutex>
#include <utility>

using namespace std;
mutex coutMutex;

class Division {
    public:
        void operator()(promise < int >&& intPromise , int a , int b) {
            intPromise.set_value(a / b);
        }
};

class Requestor {
    public:
        void operator()(shared_future < int > fut) {
            lock_guard < mutex > lk(coutMutex);
            cout << "Requestor thread ID : " << this_thread::get_id() << " ";
            cout << "and result of division is : " << fut.get() << endl;
        }
};

int main() {
    cout << "Demonstration of the shared future !!" << endl;
    promise < int > divPromise;
    int a = 20 , b = 10;
    shared_future < int > divResult = divPromise.get_future();
    Division div;
    thread divThread(div , move(divPromise) , a , b);
    Requestor req;
    thread req1(req , divResult);
    thread req2(req , divResult);
    thread req3(req , divResult);
    thread req4(req , divResult);
    thread req5(req , divResult);

    divThread.join();

    req1.join();
    req2.join();
    req3.join();
    req4.join();
    req5.join();
}