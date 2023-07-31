#include <iostream> 
#include <vector>
using namespace std;

// Debug helping function
void print_vec(vector<int> vec) {
    for (int i=0; i<vec.size(); i++ ) { 
        cout << vec[i] << " ";
    }
    cout << endl;
}

// Binary addition to the array - GOOD STATE
void binary_add(int elmnt, vector<int> &arr) {
    int l = 0, r = arr.size()-1;

    // Binary search
    while (r >= l) {
        int curr_pointer = l + (r-l)/2; 

        if (elmnt == arr[curr_pointer]) { break;}
        if (elmnt < arr[curr_pointer]) {
            if (curr_pointer != 0) {
                if (arr[curr_pointer-1] < elmnt) {
                    arr[curr_pointer] = elmnt;
                    break;
                }
                else { 
                    r = curr_pointer - 1;
                }
            }
            else {
                arr[curr_pointer] = elmnt;
                break;
            }
        }
        else {
            if (curr_pointer != arr.size()-1) {
                l = curr_pointer + 1;
            }
            else {
                arr.push_back(elmnt);
                break;
            }
        }
    }
}

// Find max subsequence
int find_max_subsequence(int N, int K, int *C) {

    vector<int> arr, right_arr;
    int max_sb, max_sb_new = -1, left_size, last_index, prev_left_size, prev_last_elmnt; 

    for (int i=0; i<N; i++) {
        // Binary search for the array the keeps records of subsequences
        if (i == 0) {
            arr.push_back(C[i]);
            max_sb = 1;
            prev_left_size = max_sb;
        }
        else {
            // Add element to the vector
            prev_last_elmnt = arr[arr.size()-1];
            binary_add(C[i], arr);
            // print_vec(arr);

            max_sb = arr.size(); // Longest increasing subsequence with no modifications

            // There is right sequence
            if (!right_arr.empty()) {
                if (C[i]+K > right_arr[right_arr.size()-1] && right_arr.size() > left_size) {
                    left_size = right_arr.size();
                    right_arr.clear();
                    right_arr.push_back(C[i]);
                }
                else {
                    binary_add(C[i], right_arr);
                    max_sb_new = left_size + right_arr.size();
                }
            }
            // New sequence
            else {
                if (prev_left_size == max_sb && C[i]+K > prev_last_elmnt) {
                    right_arr.push_back(C[i]);
                    left_size = max_sb;
                    max_sb_new = left_size + right_arr.size();
                }
            }

            // Reset - delete right array
            if (max_sb > max_sb_new) { 
                right_arr.clear();
            }
            prev_left_size = max_sb;
        }
    }

    return max(max_sb, max_sb_new);
}

int main (int argc, char **argv) {
    // Initial Variables
    int N, K;

    // Read from std input
    cin >> N >> K;

    // Create a dynamic array with N elements in total 
    int *C = new int[N];
    for (int i=0; i<N; i++) {
	    cin >> C[i];
    }
    int max_subsequence = find_max_subsequence(N, K, C);
    cout << max_subsequence << endl; 

    // Delete arrays
    delete [] C;
    return 0;
}

// In case i need it 
    /* DEBUGGING 
    vector<int> a;
    for (int i=0; i<N; i++) {
        a.push_back(C[i]);
    }
    binary_add(K, a);
    for (int i=0; i<a.size(); i++ ){ 
        cout << a[i] << " ";
    }
    cout << endl; */

