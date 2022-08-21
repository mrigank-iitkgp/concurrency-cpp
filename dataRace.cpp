#include <iostream>
#include <chrono>
#include <thread>
//#include <mutex>
using namespace std;

//mutex coutMutex;

class Worker {
    public:
        Worker(string s) : name(s) {}
        void operator()() {
            for(int i = 1 ; i <= 3 ; i++) {
                this_thread::sleep_for(chrono::milliseconds(200));
                //coutMutex.lock();
                cout << name << " : " << " doing Work " << i << endl;
                //coutMutex.unlock();
            }
        }
    private:
        string name;
};

int main() {
    cout << "Mutex demonstration starts now!!" << endl;
    thread virat = thread(Worker("Virat Kohli"));
    thread rohit = thread(Worker("Rohit Sharma"));
    thread hardik = thread(Worker("Hardik Pandya"));
    thread jasprit = thread(Worker("Jasprit Bumrah"));

    virat.join();
    rohit.join();
    hardik.join();
    jasprit.join();

    cout << "Mutex demonstration complete!!" << endl;
}