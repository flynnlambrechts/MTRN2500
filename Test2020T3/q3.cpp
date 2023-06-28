#include <iostream>
#include <vector>
#include <numeric>
// TODO: add additional headers if needed


// TODO: convert the following class into a template class
template <typename T>
class MyClass {
public:
    MyClass(const std::vector<T> &vec) : mVec {vec} {};
    int getMean() const {
        int mean;
        T sum {};
        if (mVec.empty()) {return 0;}
        mean = std::accumulate(mVec.begin(), mVec.end(), sum) / mVec.size();
        return mean;

    };
private:
    std::vector<T> mVec {};
};