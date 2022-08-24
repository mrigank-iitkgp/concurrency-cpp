#include <iostream>
#include <thread>
#include <future>
#include <utility>

using namespace std;

class Division {
    public:
        void operator() (promise < int >&& intPromise , int a , int b) {
            try
            {
                if(b == 0) {
                    string errMsg = "Illegal division by zero";
                    throw runtime_error(errMsg);
                }
                intPromise.set_value(a / b);
            }
            catch(...)
            {
                intPromise.set_exception(current_exception());
            }
        }
};

void executeDivision(int numerator , int denominator) {
    promise < int > divPromise;
    future < int > divResult = divPromise.get_future();

    Division div;
    thread divThread(div , move(divPromise) , numerator , denominator);

    divThread.join();

    try
    {
        cout << numerator << " / " << denominator << " = " << divResult.get() << endl;
    }
    catch(runtime_error& e)
    {
        cout << e.what() << '\n';
    }
}

int main() {
    executeDivision(10 , 0);
    executeDivision(20 , 10);
}