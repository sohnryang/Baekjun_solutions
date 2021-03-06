/*
 * Baekjoon Online Judge #14438
 * https://www.acmicpc.net/problem/14438
 */

#include <algorithm>
#include <numeric>
#include <vector>
#include <cstdio>

using namespace std;

class RMQ {
 private:
  vector<long long> tree;
  int len;

  long long init_tree(vector<long long>& arr, int lo, int hi, int node) {
    if (lo == hi) return tree[node] = arr[lo];
    int mid = (lo + hi) / 2;
    long long left = init_tree(arr, lo, mid, node * 2);
    long long right = init_tree(arr, mid + 1, hi, node * 2 + 1);
    return tree[node] = min(left, right);
  }

  long long query(int lo, int hi, int node, int node_lo, int node_hi) {
    if (hi < node_lo || node_hi < lo) return numeric_limits<long long>::max();
    if (lo <= node_lo && node_hi <= hi) return tree[node];
    int mid = (node_lo + node_hi) / 2;
    return min(query(lo, hi, node * 2, node_lo, mid),
               query(lo, hi, node * 2 + 1, mid + 1, node_hi));
  }

  long long update(int idx, int newval, int node, int node_lo, int node_hi) {
    if (idx < node_lo || node_hi < idx) return tree[node];
    if (node_lo == node_hi) return tree[node] = newval;
    int mid = (node_lo + node_hi) / 2;
    return tree[node] =
               min(update(idx, newval, node * 2, node_lo, mid),
                   update(idx, newval, node * 2 + 1, mid + 1, node_hi));
  }

  long long update_delta(int idx, int delta, int node, int node_lo, int node_hi) {
    if (idx < node_lo || node_hi < idx) return tree[node];
    if (node_lo == node_hi) return tree[node] += delta;
    int mid = (node_lo + node_hi) / 2;
    return tree[node] =
               min(update_delta(idx, delta, node * 2, node_lo, mid),
                   update_delta(idx, delta, node * 2 + 1, mid + 1, node_hi));
  }

 public:
  long long query(int lo, int hi) { return query(lo, hi, 1, 0, len - 1); }

  long long update(int idx, int newval) {
    return update(idx, newval, 1, 0, len - 1);
  }

  long long update_delta(int idx, int delta) {
    return update_delta(idx, delta, 1, 0, len - 1);
  }

  RMQ(vector<long long>& arr) {
    len = arr.size();
    tree.resize(len * 4);
    init_tree(arr, 0, len - 1, 1);
  }
};

int main() {
  int N;
  scanf("%d", &N);
  vector<long long> arr;
  for (int i = 0; i < N; ++i) {
    long long n;
    scanf("%lld", &n);
    arr.push_back(n);
  }
  RMQ rmq(arr);
  int Q;
  scanf("%d", &Q);
  for (int i = 0; i < Q; ++i) {
    int cmd;
    scanf("%d", &cmd);
    if (cmd == 1) {
      int idx;
      long long d;
      scanf("%d %lld", &idx, &d);
      rmq.update(idx - 1, d);
    } else {
      int s, e;
      scanf("%d %d", &s, &e);
      printf("%lld\n", rmq.query(s - 1, e - 1));
    }
  }
  return 0;
}
