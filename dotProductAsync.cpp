#include <iostream>
#include <future>
#include <random>
#include <vector>
#include <numeric>

const int NUM = 1000000;
typedef long long int ll;
using namespace std;

ll dotProductWithoutAsync(vector < int >& v , vector < int >& w) {
    return inner_product(v.begin() , v.end() , w.begin() , 0ll);
}

ll dotProductWithAsync(vector < int >& v , vector < int >& w) {
    auto sz = v.size();
    auto future1 = async([&] {
        return inner_product(&v[0] , &v[sz / 4] , &w[0] , 0ll);
    });
    auto future2 = async([&] {
        return inner_product(&v[sz / 4] , &v[sz / 2] , &w[sz / 4] , 0ll);
    });
    auto future3 = async([&] {
        return inner_product(&v[sz / 2] , &v[sz * 3 / 4] , &w[sz / 2] , 0ll);
    });
    auto future4 = async([&] {
        return inner_product(&v[sz * 3 / 4] , &v[sz] , &w[sz * 3 / 4] , 0ll);
    });

    return future1.get() + future2.get() + future3.get() + future4.get();
}

int main() {
    cout << "Demonstration of Dot Product Asynchronous !!" << endl;
    random_device seed;
    mt19937 engine(seed());
    vector < int > v , w;
    v.reserve(NUM);
    w.reserve(NUM);
    uniform_int_distribution < int > dist(0 , 100);
    for(int i = 0 ; i < NUM ; i++) {
        v.push_back(dist(engine));
        w.push_back(dist(engine));
    }
    auto begin1 = chrono::system_clock::now();
    cout << "Dot product without Async call = " << dotProductWithoutAsync(v , w) << endl;
    auto end1 = chrono::system_clock::now();
    auto duration1 = end1 - begin1;
    cout << "Time taken by dotProductWithoutAsync(v , w) : " << chrono::duration < double >(duration1).count() << " seconds" << endl;

    auto begin2 = chrono::system_clock::now();
    cout << "Dot product with Async call = " << dotProductWithAsync(v , w) << endl;
    auto end2 = chrono::system_clock::now();
    auto duration2 = end2 - begin2;
    cout << "Time taken by dotProductWithAsync(v , w) : " << chrono::duration < double >(duration2).count() << " seconds" << endl;
    
}