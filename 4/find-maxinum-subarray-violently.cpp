#include <iostream>
#include <climits>
#define MIN -INT_MAX

using namespace std;

struct Result {
    int low;
    int high;
    int sum;
};

Result findMaxinumSubarrayViolently(int * arr, int low, int high);

int main(void) {
    int in[16] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    // int in[16] = {-13, -3, -25, -20, -3, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7};
    Result res = findMaxinumSubarrayViolently(in, 0, 15);
    cout << res.low << " " << res.high << " " << res.sum;
    return 0;
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
