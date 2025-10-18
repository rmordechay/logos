#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec;
    for (int i = 0; i < 100000000; i++) {
        vec.push_back(i);
    }
    long long sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        sum += vec[i];
    }
    std::cout << "Sum: " << sum << std::endl;
    return 0;
}