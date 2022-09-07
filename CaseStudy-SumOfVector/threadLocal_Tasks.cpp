#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <future>
#include <thread>

using namespace std;
typedef long long int ll;

constexpr ll sz = 100000000;
constexpr ll fir =  25000000;
constexpr ll sec =  50000000;
constexpr ll thi =  75000000;
constexpr ll fou = 100000000;


void summation(promise < ll >&& prom , vector < int >& arr , ll start , ll end) {
    ll tempSum = 0;
    for(ll i = start ; i < end ; i++) {
        tempSum += arr[i];
    }
    prom.set_value(tempSum);
}

int main() {
    cout << "Calculating time for Sum of Vectors using Tasks!!" << endl;

    // Calculating the sum of random values (uniform distribution(1 , 10)) of vector using Loops

    vector < int > randomValues;
    randomValues.reserve(sz);
    random_device seed;
    mt19937 engine(seed());
    uniform_int_distribution < int > uniformDist(1 , 10);
    for(ll i = 0 ; i < sz ; i++) {
        randomValues.push_back(uniformDist(engine));
    }
    promise < ll > prom1;
    promise < ll > prom2;
    promise < ll > prom3;
    promise < ll > prom4;

    auto fut1 = prom1.get_future();
    auto fut2 = prom2.get_future();
    auto fut3 = prom3.get_future();
    auto fut4 = prom4.get_future();

    const auto start = chrono::steady_clock::now();
    thread t1(summation , move(prom1) , ref(randomValues) , 0ll , fir);
    thread t2(summation , move(prom2) , ref(randomValues) , fir , sec);
    thread t3(summation , move(prom3) , ref(randomValues) , sec , thi);
    thread t4(summation , move(prom4) , ref(randomValues) , thi , fou);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    ll sum = fut1.get() + fut2.get() + fut3.get() + fut4.get();

    chrono::duration < double > dur = chrono::steady_clock::now() - start;
    cout << "Total duration : " << dur.count() << " seconds" << endl;
    cout << "Sum : " << sum << endl;
}