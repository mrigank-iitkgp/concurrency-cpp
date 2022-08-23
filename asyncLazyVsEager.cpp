#include <iostream>
#include <future>
#include <chrono>

using namespace std;

int main() {
    cout << "Demonstration of Eager vs Lazy evaluation !!" << endl;

    auto begin = chrono::system_clock::now();

    auto asyncLazy = async(launch::deferred , []{ return chrono::system_clock::now(); });
    auto asyncEager = async(launch::async , []{ return chrono::system_clock::now(); });

    this_thread::sleep_for(chrono::seconds(1));

    auto lazyStart = asyncLazy.get() - begin;
    auto eagerStart = asyncEager.get() - begin;

    auto lazyStartDuartion = chrono::duration < double >(lazyStart).count();
    auto eagerStartDuration = chrono::duration < double >(eagerStart).count();

    cout << "Lazy Evaluation was started after " << lazyStartDuartion << " seconds" << endl;
    cout << "Eager Evaluation was started after " << eagerStartDuration << " seconds" << endl;
}