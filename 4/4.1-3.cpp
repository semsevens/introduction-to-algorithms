#include <iostream>
#include <climits>
#include <cmath>
#define MIN -INT_MAX

using namespace std;

struct Result {
    int low;
    int high;
    int sum;
};

Result findMaxinumSubarrayImproved(int * arr, int low, int high);
Result findMaxinumSubarrayViolently(int * arr, int low, int high);
Result findMaxinumSubarray(int * arr, int low, int high);
Result findCrossingMaxinumSubarray(int * arr, int low, int mid, int high);

int main(void) {
    int in[16] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    // int in[16] = {-13, -3, -25, -20, -3, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7};
    Result res = findMaxinumSubarrayImproved(in, 0, 15);
    cout << res.low << " " << res.high << " " << res.sum;
    return 0;
}

Result findMaxinumSubarrayImproved(int * arr, int low, int high) {
    int n = high - low + 1;
    if (log(n) / log(2) < n) {
        return findMaxinumSubarray(arr, low, high);
    } else {
        return findMaxinumSubarrayViolently(arr, low, high);
    }
}

Result findMaxinumSubarrayViolently(int * arr, int low, int high) {
    int sum = 0;
    int maxSum = MIN;
    int maxLeftIndex = -1;
    int maxRightIndex = -1;
    for (int i = low; i <= high; i++) {
        sum = arr[i];
        if (sum > maxSum) {
            maxSum = sum;
            maxLeftIndex = maxRightIndex = i;
        }
        for (int j = i + 1; j <= high; j++) {
            sum += arr[j];
            if (sum > maxSum) {
                maxSum = sum;
                maxLeftIndex = i;
                maxRightIndex = j;
            }
        }
    }
    return Result{maxLeftIndex, maxRightIndex, maxSum};
}

Result findMaxinumSubarray(int * arr, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        Result leftMax = findMaxinumSubarray(arr, low, mid);
        Result rightMax = findMaxinumSubarray(arr, mid + 1, high);
        Result crossingMax = findCrossingMaxinumSubarray(arr, low, mid, high);
        if (leftMax.sum > rightMax.sum && leftMax.sum > crossingMax.sum)
            return leftMax;
        else if (rightMax.sum > leftMax.sum && rightMax.sum > crossingMax.sum)
            return rightMax;
        if (crossingMax.sum > rightMax.sum && crossingMax.sum > leftMax.sum)
            return crossingMax;
    } else {
        return Result{low, high, arr[low]};
    }
}

Result findCrossingMaxinumSubarray(int * arr, int low, int mid, int high) {
    if (low >= high)
        return Result{low, high, arr[low]};

    int leftMaxSum = MIN;
    int leftSum = 0;
    int leftMaxIndex = -1;
    for (int i = mid; i >= low; i--) {  // find leftMaxSum
        leftSum += arr[i];
        if (leftSum > leftMaxSum) {
            leftMaxSum = leftSum;
            leftMaxIndex = i;
        }
    }

    int rightMaxSum = MIN;
    int rightSum = 0;
    int rightMaxIndex = -1;
    for (int i = mid + 1; i <= high; i++) {  // find rightMaxSum
        rightSum += arr[i];
        if (rightSum > rightMaxSum) {
            rightMaxSum = rightSum;
            rightMaxIndex = i;
        }
    }

    return Result{leftMaxIndex, rightMaxIndex, leftMaxSum + rightMaxSum};
}
