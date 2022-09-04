#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <mutex>
#include <atomic>

using namespace std;
typedef long long int ll;

constexpr ll sz = 100000000;

int main() {
    cout << "Calculating time for Sum of Vectors with Atomics!!" << endl;

    // Calculating the sum of random values (uniform distribution(1 , 10)) of vector using Loops

    vector < int > randomValues;
    randomValues.reserve(sz);
    random_device seed;
    mt19937 engine(seed());
    uniform_int_distribution < int > uniformDist(1 , 10);
    for(ll i = 0 ; i < sz ; i++) {
        randomValues.push_back(uniformDist(engine));
    }
    atomic < ll > sum = {};
    cout << "Is sum lock Free : " << sum.is_lock_free() << endl;
    const auto start = chrono::steady_clock::now();
    for(auto val : randomValues) {
        sum += val;
    }
    chrono::duration < double > dur = chrono::steady_clock::now() - start;
    cout << "Total duration : " << dur.count() << " seconds" << endl;
    cout << "Sum : " << sum << endl;
}