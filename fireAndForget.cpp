#include <iostream>
#include <future>

using namespace std;

int main() {
    cout << "Demonstration the Fire and Forget Future !!" << endl;

    async(launch::async , []{
        this_thread::sleep_for(chrono::seconds(2));
        cout << "First Thread !!" << endl;
    });

    async(launch::async , []{
        this_thread::sleep_for(chrono::seconds(1));
        cout << "Second Thread !!" << endl;
    });

    cout << "Main Thread !!" << endl;
}