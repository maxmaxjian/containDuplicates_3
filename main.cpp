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

// // solution 2 brute force
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <cmath>

// class solution {
//   public:
//     bool containNearbyAlmostDuplicates(const std::vector<int> & nums, int k, int t) {
//         int begin, end;
//         for (int center = 0; center < nums.size(); ++center) {
//             begin = (center > k-1) ? center-k : 0;
//             end = (center+k < nums.size()) ? center+k : nums.size()-1;
//             std::cout << "center  = " << center << " -> From " << begin << " to " << end << std::endl;
//             int max = *std::max_element(nums.begin()+begin, nums.begin()+end+1,
//                                         [&](int i, int j){
//                                             // std::cout << abs(i-nums[center]) << "," << abs(j-nums[center]) << std::endl;
//                                             return abs(i-nums[center]) < abs(j-nums[center]);
//                                         });
//             std::cout << "max diff = " << abs(max-nums[center]) << std::endl;
//             if (abs(max-nums[center]) < t)
//                 return true;
//         }
//         return false;
//     }
// };

// solution
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

class solution {
  public:
    bool containNearbyAlmostDuplicates(const std::vector<int> & nums, int k, int t) {
        std::map<int, std::queue<int>> maxmap, minmap;
        int curr = 0, begin, end;
        while (curr < nums.size()) {
            begin = curr > k ? curr-k : 0;
            end = curr+k < nums.size() ? curr+k : nums.size()-1;
            if (maxmap.empty()) {
                auto it = std::minmax_element(nums.begin()+begin, nums.begin()+end+1);
                for (int i = begin; i <= end; i++) {
                    if (nums[i] == *it.first) {
                        if (minmap.find(curr) == minmap.end())
                            minmap[curr] = std::queue<int>();
                        minmap[curr].push(i);
                    }
                    else if (nums[i] == *it.second) {
                        if (maxmap.find(curr) == maxmap.end())
                            maxmap[curr] = std::queue<int>();
                        maxmap[curr].push(i);
                    }
                }
            }
            else {
                if (nums[end] < nums[minmap[curr-1].front()]) {
                    minmap[curr] = std::queue<int>{end};
                }
                else {
                    minmap[curr] = minmap[curr-1];
                    while (!minmap[curr].empty() && minmap[curr].front() < begin)
                        minmap[curr].pop();
                    if (minmap[curr].empty())
                        minmap[curr].push();
                    else if (*it.first == nums[minmap[curr].front()])
                        minmap[curr].push(it.first-nums.begin());
                }

                if (*it.second > nums[maxmap[curr-1].front()]) {
                    maxmap[curr] = std::queue<int>{it.second-nums.begin()};
                }
                else {
                    maxmap[curr] = maxmap[curr-1];
                    while (!maxmap[curr].empty() && maxmap[curr].front() < begin)
                        maxmap[curr].pop();
                    if ()
                }
            }
        }
    }
};

int main() {
    // std::vector<int> nums{1,2,4,5};
    // int k = 2, t = 4;      // expected result = true
    
    std::vector<int> nums{7,1,3};
    int k = 2, t = 3;         // expected result = false
    
    solution soln;
    bool exist = soln.containNearbyAlmostDuplicates(nums, k, t);
    std::cout << std::boolalpha << exist << std::endl;
}
