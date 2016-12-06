// // solution 1 brute force
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <cmath>

// class solution {
//   public:
//     bool containNearbyAlmostDuplicates(const std::vector<int> & nums, int k, int t) {
//         int begin, end;
//         for (int center = 0; center < nums.size(); ++center) {
//             // begin = (center > k-1) ? center-k : 0;
//             // end = (center+k < nums.size()) ? center+k : nums.size()-1;
// 	    begin = center;
// 	    end = center+k;
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

// solution 2
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <deque>
#include <iterator>

namespace std {
    std::ostream & operator<<(std::ostream & os, const std::pair<int,std::deque<int>> & dq) {
        os << dq.first << " -> ";
        std::copy(dq.second.begin(), dq.second.end(), std::ostream_iterator<int>(os, " "));
        return os;
    }
}

class solution {
  public:
    bool containNearbyAlmostDuplicates(const std::vector<int> & nums, int k, int t) {
	std::map<int,std::deque<int>> dict;
	int i, j;
	for (i = 0, j = i; i < nums.size();) {
	    while (j < nums.size() && j-i <= k) {
                if (j != i) {
                    if (dict.find(nums[j]) == dict.end())
                        dict[nums[j]] = std::deque<int>();
                    dict[nums[j]].push_back(j);
                }
		j++;
	    }
            std::copy(dict.begin(), dict.end(),
                      std::ostream_iterator<std::pair<int,std::deque<int>>>(std::cout, "\n"));
            auto it = dict.lower_bound(nums[i]-t);
            while (it != dict.end() && it->first > nums[i]+t)
                ++it;
            if (it != dict.end() && it->first <= nums[i]+t)
                return true;
            i++;
            while (!dict[nums[i]].empty() && dict[nums[i]].front() <= i)
                   dict[nums[i]].pop_front();
            if (dict[nums[i]].empty())
                dict.erase(nums[i]);
	}
	return false;
    }
};

int main() {
    std::vector<int> nums{1,2,4,5};
    int k = 2, t = 3;      // expected result = true
    
    // std::vector<int> nums{7,1,3};
    // int k = 2, t = 3;         // expected result = true

    // std::vector<int> nums{3,6,0,4};
    // int k = 2, t = 2;
    
    solution soln;
    bool exist = soln.containNearbyAlmostDuplicates(nums, k, t);
    std::cout << std::boolalpha << exist << std::endl;
    // if (exist)
    // 	std::cout << "There is a center within the distance of " << k << " the difference is not great than " << t << std::endl;
    // else
    // 	std::cout << "There isn't a center within the distance of " << k << " the difference is not great than " << t << std::endl;
}
