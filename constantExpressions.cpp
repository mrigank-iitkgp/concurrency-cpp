#include <iostream>
using namespace std;

class MyConstantExpression {
    private:
        double val1;
        double val2;
    public:
        constexpr MyConstantExpression(double v1 , double v2) : val1(v1) , val2(v2) {};
        constexpr double getSum() const { return val1 + val2 ; };
};

int main() {
    constexpr double myVal1 = 10.96;
    constexpr MyConstantExpression myConstantExpression(10.88 , myVal1);
    constexpr double result = myConstantExpression.getSum();
    cout << "The sum is : " << result << endl;
}