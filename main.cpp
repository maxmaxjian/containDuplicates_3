// // solution 1
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <iterator>
// #include <cmath>

// class solution {
//   public:
//     bool containDuplicates(const std::vector<int> & nums, int k, int t) {
//         size_t start = 0;
//         while (start <= nums.size()-k) {
//             // attempt 1
//             // std::vector<int> temp;
//             // std::transform(nums.begin()+start, nums.begin()+start+k, std::inserter(temp, temp.begin()),
//             //           [&](int i){
//             //               return i - nums[0];
//             //           });
//             // if (std::any_of(temp.begin(), temp.end(), [&](int i){return abs(i) > t;}))
//             //     return true;
//             // else
//             //     start++;

//             // attempt 2
//             // if (start+k < nums.size()) {
//             //     auto it_pair = std::minmax_element(nums.begin()+start, nums.begin()+start+k+1);
//             //     std::cout << " start = " << start << ", min = " << *it_pair.first << ", max = " << *it_pair.second << std::endl;
//             //     if (*it_pair.second-*it_pair.first <= t)
//             //         return true;
//             //     start++;
//             // }
//             // else {
//             //     auto it_pair = std::minmax_element(nums.begin()+start, nums.end());
//             //     std::cout << " start = " << start << ", min = " << *it_pair.first << ", max = " << *it_pair.second << std::endl;
//             //     if (*it_pair.second-*it_pair.first <= t)
//             //         return true;
//             //     start++;
//             // }
            
//         }
//         return false;
//     }
// };

// solution 2 brute force
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class solution {
  public:
    bool containNearbyAlmostDuplicates(const std::vector<int> & nums, int k, int t) {
        int begin, end;
        for (int center = 0; center < nums.size(); ++center) {
            begin = (center > k-1) ? center-k : 0;
            end = (center+k < nums.size()) ? center+k : nums.size()-1;
            std::cout << "center  = " << center << " -> From " << begin << " to " << end << std::endl;
            int max = *std::max_element(nums.begin()+begin, nums.begin()+end+1,
                                        [&](int i, int j){
                                            // std::cout << abs(i-nums[center]) << "," << abs(j-nums[center]) << std::endl;
                                            return abs(i-nums[center]) < abs(j-nums[center]);
                                        });
            std::cout << "max diff = " << abs(max-nums[center]) << std::endl;
            if (abs(max-nums[center]) < t)
                return true;
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
    bool exist = soln.containNearbyAlmostDuplicates(nums, k, t);
    std::cout << std::boolalpha << exist << std::endl;
}
