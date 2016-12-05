#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>

class solution {
  public:
    bool containDuplicates(const std::vector<int> & nums, int k, int t) {
        size_t start = 0;
        while (start <= nums.size()-k) {
            std::vector<int> temp;
            std::transform(nums.begin()+start, nums.begin()+start+k, std::inserter(temp, temp.begin()),
                      [&](int i){
                          return i - nums[0];
                      });
            if (std::any_of(temp.begin(), temp.end(), [&](int i){return abs(i) > t;}))
                return true;
            else
                start++;
        }
        return false;
    }
};

int main() {
    // std::vector<int> nums{1,2,4,5};
    // int k = 2, t = 4;
    std::vector<int> nums{7,1,3};
    int k = 2, t = 3;
    
    solution soln;
    bool exist = soln.containDuplicates(nums, k, t);
    std::cout << std::boolalpha << exist << std::endl;
}
