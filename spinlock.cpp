#include<iostream>
#include<thread>
#include<atomic>
using namespace std;

class SpinLock 
{
    public:
        atomic_flag flag = ATOMIC_FLAG_INIT;
        SpinLock() {}
        void lock()
        {
            while(flag.test_and_set());
        }
        void unlock()
        {
            flag.clear();
        }
};

SpinLock spin;

void critical_section()
{
    spin.lock();
    this_thread::sleep_for(chrono::milliseconds(15000));
    for(int i = 0 ; i < 10 ; i++)
    {
        cout << i << " ";
    }
    cout << endl;
    spin.unlock();
}

int main()
{
    thread t1(critical_section);
    thread t2(critical_section);
    t1.join();
    t2.join();
}