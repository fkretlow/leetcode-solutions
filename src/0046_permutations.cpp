/*************************************************************************************************
 *
 * 46. Permutations
 * Given an array of distinct integers, return all the possible permutations in any order.
 *
 * Runtime: 78.01%, Memory Usage: 90.7%
 *
 ************************************************************************************************/

#include <functional>
#include <iostream>
#include <bitset>
#include <vector>
#include "util.h"

constexpr unsigned short k_max_size = 6;

template<typename T>
class Permutator {
public:
    std::vector<std::vector<T>> operator()(const std::vector<T>& A) noexcept
    {
        permutations.clear();
        permutations.reserve(faculty(A.size()));
        current.clear();
        current.reserve(A.size());
        used.reset();

        permute_r(A);
        return permutations;
    }
private:
    std::vector<std::vector<T>> permutations;
    std::vector<T> current;
    std::bitset<k_max_size> used;

    void permute_r(const std::vector<T>& A)
    {
        if (current.size() == A.size()) {
            permutations.emplace_back(current);
            return;
        }

        for (typename std::vector<T>::size_type i = 0; i < A.size(); ++i) {
            if (!used.test(i)) {
                current.emplace_back(A.at(i));
                used.set(i);
                permute_r(A);
                current.pop_back();
                used.reset(i);
            }
        }
    }

    unsigned faculty(unsigned x) const noexcept
    {
        unsigned f = x--;
        while (x > 1) f *= x--;
        return f;
    }
};

static inline void test(const std::vector<int> nums)
{
    static auto permute = Permutator<int>();
    std::cout << nums << std::endl;
    std::cout << permute(nums) << std::endl;
}


int main()
{
    test({1,2,3});
    test({1,2});
    test({1});
    return 0;
}
