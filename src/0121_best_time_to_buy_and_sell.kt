/*************************************************************************************************
 *
 * 121. Best Time to Buy and Sell Stock
 * Given an array of prices where prices[i] is the price of a given stock on the ith day, find
 * the maximum profit you can achieve by buying on one day and selling on another.
 *
 * In abstract terms, find two indices i, j with i < j such that A[j] - A[i] is maximized.
 *
 ************************************************************************************************/

class Solution {
    fun maxProfit(prices: IntArray): Int {
        var maxd: Int = 0
        var minp: Int = Int.MAX_VALUE
        for (i in prices.indices) {
            if (prices[i] < minp) minp = prices[i]
            else maxd = maxOf(maxd, prices[i] - minp)
        }
        return maxd
    }
}

fun IntArray.show(): String = "[" + this.joinToString(",") + "]"

fun test(prices: IntArray, expected: Int) {
    val actual = Solution().maxProfit(prices)
    if (actual == expected) {
        println("OK: maxProfit(${prices.show()}) = $expected")
    } else {
        println("ERROR: maxProfit(${prices.show()}) = $actual, expected $expected")
    }
}

fun main() {
    test(intArrayOf(7,1,5,3,6,4), 5)
    test(intArrayOf(7,6,4,3,1), 0)
}
