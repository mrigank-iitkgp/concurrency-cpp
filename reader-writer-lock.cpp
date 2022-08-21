#include <iostream>
#include <thread>
#include <shared_mutex>
#include <unordered_map>
#include <string>
using namespace std;

shared_timed_mutex scoreLock;
unordered_map < string , int > scoreBook{{"Virat" , 183} , {"Rohit" , 264} , {"Sachin" , 200} , {"Sehwag" , 219}};

void writer(const string& name , int score) {
    lock_guard < shared_timed_mutex > writerLock(scoreLock);
    cout << "Starting the updation of higest scores!!" << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    scoreBook[name] = score;
    cout << "Ending update for " << name << endl;
}

void reader(const string& name) {
    shared_lock < shared_timed_mutex > readerLock(scoreLock);
    if(scoreBook.find(name) == scoreBook.end()) {
        cout << "Player has not played any international cricket!!" << endl;
    } else {
        cout << name << " has highest score of " << scoreBook[name] << endl;
    }
}

int main() {
    cout << "Demonstration of reader-writer lock!!" << endl;
    thread reader1([]{ reader("Surya"); });
    thread reader2([]{ reader("Rohit"); });
    thread reader3([]{ reader("Virat"); });
    thread writer1([]{ writer("Surya", 121); });
    thread reader4([]{ reader("Surya"); });
    thread reader5([]{ reader("Sachin"); });
    thread writer2([]{ writer("Rohit",300); });
    thread reader6([]{ reader("Sehwag"); });
    thread reader7([]{ reader("Rohit"); });

    reader1.join();
    reader2.join();
    reader3.join();
    reader4.join();
    reader5.join();
    reader6.join();
    reader7.join();
    writer1.join();
    writer2.join();
    
    cout << endl;
    
    cout << "The updated score book is " <<endl;
    for(auto& x : scoreBook) {
        cout << x.first << " --> " << x.second << endl;
    }
}