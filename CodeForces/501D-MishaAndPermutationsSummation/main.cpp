#include <iostream>
#include <vector>
#include <list>

using namespace std;

// binary indexed tree
int sum(vector<int> &tree, int i) {
    // compute the sum from index 1 to index i
    int s = 0;
    while (i >= 1) {
        s += tree[i];
        i -= i & (-i);
    }
    return s;
}

void update(vector<int> &tree, int i, int x) {
    // update index i of the array by x
    while (i <= tree.size() - 1) {
        tree[i] += x;
        i += (i & -i);
    }
}

int binary_search(vector<int> &tree, int k) {
    // return the kth rank entry that has not been deleted
    int left = 1, right = tree.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int x = sum(tree, mid);
        if (x == k) {
            if (sum(tree, mid - 1) < k) {
                return mid;
            } else {
                right = mid - 1;
            }
        } else if (x > k) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}

vector<int> inverse_to_permutation(vector<int> &inverse) {
    int n = inverse.size();
    vector<int> tree(n + 1, 0), res(n);

    for (int i = 1; i <= n; i++) {
        update(tree, i, 1);
    }


    for (int i = 0; i < n; i++) {
        int pos = binary_search(tree, inverse[i] + 1);
        res[i] = pos - 1;
        update(tree, pos, -1);
    }

    return res;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> p(n), q(n), inverse_p(n), inverse_q(n), tree_p(n + 1), tree_q(n + 1), inverse_sum(n);

    for (int i = 0; i < n; i++){
        cin >> p[i];
    }
        
    for (int i = 0; i < n; i++) {
        cin >> q[i];
    }

    for (int i = 0; i < n; i++) {
        update(tree_p, i + 1, 1);
        update(tree_q, i + 1, 1);
    }

    for (int i = 0; i < n; i++) {
        update(tree_p, p[i] + 1, -1);
        update(tree_q, q[i] + 1, -1);
        inverse_p[i] = sum(tree_p, p[i] + 1);
        inverse_q[i] = sum(tree_q, q[i] + 1);
        inverse_sum[i] = inverse_p[i] + inverse_q[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        int mod = n - 1 - i;
        if (inverse_sum[i] > mod) {
            inverse_sum[i] -= (mod + 1);

            if (i > 0) {
                inverse_sum[i - 1] += 1;
            }
        }
    }

    vector<int> res = inverse_to_permutation(inverse_sum);
    for (int x : res) {
        cout << x << " ";
    }

    return 0;
}