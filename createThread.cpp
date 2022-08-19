#include<iostream>
#include<thread>

void helloFunction() {
    std::cout << "This is a function" << std::endl;
}

class HelloFunctionObject{
    public:
        void operator()() const {
            std::cout << "This is a function object" << std::endl;
        }
};

int main() {
    std::cout << "Demo of thread execution" << std::endl;
    std::thread t1(helloFunction);
    HelloFunctionObject hello;
    std::thread t2(hello);
    std::thread t3([]{std::cout << "This is a lambda function" << std::endl;});
    t1.join();
    t2.join();
    t3.join();
    std::cout << std::thread::hardware_concurrency() << std::endl;
}