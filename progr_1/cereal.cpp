/* Algorithm

    Binary Search for possible medians (mid) from 1 to N -> O(logn)
    Check if mid might be at least a median is a subarray containing at least K-elements -> O(n)
    (We are doing this by calculating the prefix sum of the array C)
        If it is then check for [mid+1, N]
        If not then check for [1, mid-1]

    Complexity -> O(nlogn)
*/

#include <iostream> 
#include <algorithm>

using namespace std;

// Check if median is a minimum possible median
bool its_median(int *C, int &N, int &K, int &mid) {

    // Implementation of pref_sum
    int *pref_sum = new int[N];
    for (int i=0; i < N; i++) {
        pref_sum[i] = (C[i] >= mid) ? 1 : -1;
        if (i > 0) {
            pref_sum[i] += pref_sum[i-1];
        }
    }

    int mn = 0, break_val = -1;
    for (int i=K; i<N; i++) {
        mn = min(mn, pref_sum[i-K]);
        break_val = max(break_val, pref_sum[i]-mn);
        if (break_val > 0) { 
            return true;
        }
    }
    delete [] pref_sum;
    return false;
}

// Find max median
int find_max_median(int N, int K, int *C)  {

    int l = 1, r = N+1, mid, max_median;
    int *pref_sum = new int[N];

    // Binary search on median
    while (r >= l) {
        mid = l + (r-l)/2; // Current median that we are searching

        if (its_median(C, N, K, mid)) {
            max_median = mid;
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return max_median;
}

int main (int argc, char **argv) {
    
    int N; // Supermarkets in total
    int K; // Minimun consecutive number

    // Read from std input
    cin >> N >> K;

    // Create a dynamic array with N positions in total 
    int *C = new int[N];
    int i;
    for (i=0; i<N; i++) {
	    cin >> C[i];
    }

    int max_median = find_max_median(N, K, C);
    
    cout << max_median << endl; // Print final result

    // Delete arrays
    delete [] C;
    return 0;
}

