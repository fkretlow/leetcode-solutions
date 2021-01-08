#include <cassert>
#include <iostream>
#include <vector>

double find_median(const std::vector<int>& nums)
{
    std::vector<int>::size_type i = nums.size() / 2;
    if (nums.size() % 2 == 0) {
        return (nums[i-1] + nums[i]) / 2.0;
    } else {
        return nums[i];
    }
}

double find_median(const std::vector<int>& nums1, const std::vector<int>& nums2)
{
    if      (nums1.size() == 0) return find_median(nums2);
    else if (nums2.size() == 0) return find_median(nums1);

    const std::vector<int> *A, *B;
    if (nums1.size() < nums2.size()) { A = &nums1; B = &nums2; }
    else                             { A = &nums2; B = &nums1; }
    assert(A->size() <= B->size());

    std::vector<int>::size_type i, j, hi, lo, m;
    m = (A->size() + B->size()) / 2;
    i = A->size() / 2;
    j = m - i;
    lo = 0;
    hi = A->size();

    for ( ;; ) {
        std::cout << "i=" << i << ", j=" << j << std::endl;
        if (i == A->size())                         break;
        else if (A->at(i) < B->at(j-1))             lo = i + 1;
        else if (i > 0 && B->at(j) < A->at(i-1))    hi = i;
        else                                        break;
        i = lo + (hi - lo) / 2;
        j = m - i;
        if (i == 0)                                 break;
    }

    std::cout << "final i=" << i << ", j=" << j << std::endl;

    if ((A->size() + B->size()) % 2 == 0) {
        std::cout << "even" << std::flush;
        double med_upper, med_lower;
        if (i == 0) {
            std::cout << ", i=0" << std::flush;
            if (A->size() == B->size()) {
                std::cout << ", equal size" << std::endl;
                med_upper = A->front();
                med_lower = B->back();
            } else {
                std::cout << ", unequal size" << std::endl;
                med_upper = std::min(A->at(i), B->at(j));
                med_lower = B->at(j-1);
            }
        } else if (i == A->size()) {
            std::cout << ", i=|A|" << std::flush;
            if (A->size() == B->size()) {
                std::cout << ", equal size" << std::endl;
                med_upper = B->front();
                med_lower = A->back();
            } else {
                std::cout << ", unequal size" << std::endl;
                med_upper = B->at(j);
                med_lower = std::max(A->back(), B->at(j-1));
            }
        } else {
            std::cout << ", 0 < i < |A|" << std::endl;
            med_upper = std::min(A->at(i), B->at(j));
            med_lower = std::max(A->at(i-1), B->at(j-1));
        }
        return (med_upper + med_lower) / 2;
    } else {
        std::cout << "odd" << std::endl;
        if (i == A->size()) {
            return B->at(j);
        } else {
            return std::min(A->at(i), B->at(j));
        }
    }
}

double find_median_brute_force(std::vector<int>& A, std::vector<int>& B)
{
    std::vector<int>::size_type m = (A.size() + B.size()) / 2;
    auto itA = A.cbegin();
    auto itB = B.cbegin();
    int cur;
    for (std::vector<int>::size_type i = 0; i <= m; ++i) {
        if (*itA < *itB) cur = *itA++;
        else             cur = *itB++;
    }
    return cur;
}

int main()
{
    std::vector<int> A { 1,3 };
    std::vector<int> B { 2 };

    double m = find_median(A, B);
    std::cout << m << std::endl;
    return 0;
}
