#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <mutex>
#include <thread>

using namespace std;
typedef long long int ll;

atomic < ll > sum = {};

constexpr ll sz = 100000000;
constexpr ll fir =  25000000;
constexpr ll sec =  50000000;
constexpr ll thi =  75000000;
constexpr ll fou = 100000000;

void summation(vector < int >& arr , atomic < ll > & sum , ll start , ll end) {
    ll tempSum = 0;
    for(ll i = start ; i < end ; i++) {
        tempSum += arr[i];
    }
    sum.fetch_add(tempSum , memory_order_relaxed);
}

int main() {
    cout << "Calculating time for Sum of Vectors using thread local with atomics and relaxed semantics!!" << endl;

    // Calculating the sum of random values (uniform distribution(1 , 10)) of vector using Loops

    vector < int > randomValues;
    randomValues.reserve(sz);
    random_device seed;
    mt19937 engine(seed());
    uniform_int_distribution < int > uniformDist(1 , 10);
    for(ll i = 0 ; i < sz ; i++) {
        randomValues.push_back(uniformDist(engine));
    }
    const auto start = chrono::steady_clock::now();
    thread t1(summation , ref(randomValues) , ref(sum) , 0ll , fir);
    thread t2(summation , ref(randomValues) , ref(sum) , fir , sec);
    thread t3(summation , ref(randomValues) , ref(sum) , sec , thi);
    thread t4(summation , ref(randomValues) , ref(sum) , thi , fou);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    chrono::duration < double > dur = chrono::steady_clock::now() - start;
    cout << "Total duration : " << dur.count() << " seconds" << endl;
    cout << "Sum : " << sum << endl;
}