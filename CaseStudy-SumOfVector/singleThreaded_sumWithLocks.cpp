#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <mutex>

using namespace std;
typedef long long int ll;

constexpr ll sz = 100000000;

int main() {
    cout << "Calculating time for Sum of Vectors with protection!!" << endl;

    // Calculating the sum of random values (uniform distribution(1 , 10)) of vector using Loops

    vector < int > randomValues;
    randomValues.reserve(sz);
    random_device seed;
    mt19937 engine(seed());
    uniform_int_distribution < int > uniformDist(1 , 10);
    for(ll i = 0 ; i < sz ; i++) {
        randomValues.push_back(uniformDist(engine));
    }
    mutex mt;
    const auto start = chrono::steady_clock::now();
    ll sum = 0ll;
    for(auto val : randomValues) {
        lock_guard <mutex > lk(mt);
        sum += val;
    }
    chrono::duration < double > dur = chrono::steady_clock::now() - start;
    cout << "Total duration : " << dur.count() << " seconds" << endl;
    cout << "Sum : " << sum << endl;
}