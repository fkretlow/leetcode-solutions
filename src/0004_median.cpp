#include <cassert>
#include <iostream>
#include <vector>

double find_median(const std::vector<int>& V)
{
    std::vector<int>::size_type m = V.size() / 2;
    if (V.size() & 1) return V[m];
    else              return (V[m-1] + V[m]) / 2.0;
}

double find_median_of_successive_arrays(const std::vector<int>& low,
                                        const std::vector<int>& high)
{
    /* Assume both arrays are sorted and low.back() <= high.front(). */
    std::vector<int>::size_type n = low.size() + high.size();
    std::vector<int>::size_type i = n / 2;
    if (n & 1) return i < low.size() ? low.at(i)   : high.at(i - low.size());
    else return  ( (i-1 < low.size() ? low.at(i-1) : high.at(i-1 - low.size()))
                 + (i   < low.size() ? low.at(i)   : high.at(i - low.size())))
                 / 2.0;
}

double find_median(const std::vector<int>& V1, const std::vector<int>& V2)
{
    /* Peel off edge cases. */
    if      (V1.size() == 0)          return find_median(V2);
    else if (V2.size() == 0)          return find_median(V1);
    else if (V1.back() <= V2.front()) return find_median_of_successive_arrays(V1, V2);
    else if (V2.back() <= V1.front()) return find_median_of_successive_arrays(V2, V1);

    /* Now we know that the arrays are intertwined, which eliminates a thicket of awkward edge
     * cases. Perform a binary search on the smaller array, A, to find two indices i, j such that
     *     (1) i + j = |A U B| / 2
     *     (2) A[i] >= B[j-1] and B[j] >= A[i-1]. */

    const std::vector<int> *A, *B;
    if (V1.size() < V2.size()) { A = &V1; B = &V2; }
    else                       { A = &V2; B = &V1; }
    assert(A->size() <= B->size());

    std::vector<int>::size_type i, j, lo, hi, m;
    m = (A->size() + B->size()) / 2;
    lo = 0;
    hi = A->size();

    for ( ;; ) {
        i = (lo + hi) / 2;
        j = m - i;
        if               (A->at(i) < B->at(j-1)) lo = i + 1;
        else if (i > 0 && B->at(j) < A->at(i-1)) hi = i;
        else                                     break;
    }

    if ((A->size() + B->size()) & 1) return std::min(A->at(i), B->at(j));
    else return (std::max(A->at(i-1), B->at(j-1)) + std::min(A->at(i), B->at(j))) / 2.0;
}

int main()
{
    std::vector<int> A { 2,4 };
    std::vector<int> B { 1,3 };
    std::cout << find_median(A, B) << std::endl;
    return 0;
}
