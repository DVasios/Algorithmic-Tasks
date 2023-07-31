#include <iostream> 
#include <unordered_map>
#include <algorithm>

using namespace std;

int find_min_number(int N, int K, int *C) {

    int *pref_sum = new int[N]; // Prefix sum of the initial array
    unordered_map<int, int> values; // Stores prefix sum in unordered map 
    int curr_min_number = N+1;

    // Complexity, worst case Kn^2 but K is constant so -> O(n^2)
    for (int i=0; i<N; i++) {

        // If current element is equal to K
        if (C[i] == K) { 
            return 1; 
        }        

        // Implementation of prefix sum
        if (i > 0) {
            pref_sum[i] = pref_sum[i-1] + C[i];
        }
        else {
            pref_sum[i] = C[i];
        }

        // Store prefix sum in unordered map
        values.insert({pref_sum[i], i});

        int right_sum = 0, left_sum = 0;
        int k; // helper pointer for the left sum
        if (i > 0 && (pref_sum[i] >= K)) {

            k = i-1; 
            right_sum = pref_sum[i] - pref_sum[k];

            // Constant time - Worst Case O(Kn)
            while (right_sum <= K) {
                if (right_sum == K) {
                    curr_min_number = min((i-k), curr_min_number);
                    break;
                }
                else {
                    left_sum = K - right_sum;
                    // left sum exists at unordered map
                    if (values.count(left_sum) == 1) {
                        curr_min_number = min(curr_min_number, (i-k) + (values.at(left_sum)+1));
                    }
                    // look for subarray from 0->k
                    else {
                        for (int j=0; j<=k; j++) {
                            if (pref_sum[j] > left_sum) {
                                if (values.count(pref_sum[j] - left_sum) == 1) 
                                curr_min_number = min(curr_min_number, (i-k) + (j - values.at(pref_sum[j]-left_sum)));
                            }
                        }
                    }
                    k-= 1;
                    right_sum = pref_sum[i] - pref_sum[k];
                }
            }
        }
    }

    if (curr_min_number == N+1) {
        return -1;
    }
    return curr_min_number;
}

int main () {
    
    int N, K; 

    // Read from std input
    cin >> N >> K;

    // Create a dynamic array with N positions in total 
    int *C = new int[N];
    int i;
    for (i=0; i<N; i++) {
	    cin >> C[i];
    }

    // Print result
    cout << find_min_number(N, K, C) << endl;

    // Delete array C 
    delete [] C;
    return 0;
}