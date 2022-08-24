#include <iostream>
#include <thread>
#include <future>
#include <utility>

using namespace std;

void product(promise < int >&& intPromise , int a , int b) {
    intPromise.set_value(a * b);
}

class Division {
    public:
        void operator() (promise < int >&& intPromise , int a , int b) {
            intPromise.set_value(a / b);
        }
};

int main() {
    cout << "Demonstration of Promises and Future !!" << endl;
    int a = 20;
    int b = 10;
    promise < int > prodPromise;
    promise < int > divPromise;

    future < int > prodResult = prodPromise.get_future();
    future < int > divResult = divPromise.get_future();

    thread prodThread(product , move(prodPromise) , a , b);
    Division div;
    thread divThread(div , move(divPromise) , a , b);

    prodThread.join();
    divThread.join();

    cout << "Product of a & b = " << prodResult.get() << endl;
    cout << "Division of a & b = " << divResult.get() << endl;
}