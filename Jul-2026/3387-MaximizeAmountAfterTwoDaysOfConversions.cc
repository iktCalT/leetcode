#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

struct Node{
  vector<Node*> next = {};
  vector<double> rate = {};
  double val = 0.0;
};

class Solution {
public:
  double maxAmount(const string ic, 
      const vector<vector<string>>& pairs1, 
      const vector<double>& rates1, 
      const vector<vector<string>>& pairs2, 
      const vector<double>& rates2) {
    unordered_map<string, double> day1;
    unordered_map<string, double> day2;
    exchangeMap(ic, day1, pairs1, rates1);
    exchangeMap(ic, day2, pairs2, rates2);
    if (day1.empty() || day2.empty()) return 1.0;

    double max_rate = 1.0;
    for (const auto [currency, val] : day1) {
      auto it = day2.find(currency);
      if (it != day2.end()) {
        max_rate = max(max_rate, val / (it->second));
      }
    }
    return max_rate;
  }

private:
  void exchangeMap(string ic,
      unordered_map<string, double>& dest,
      const vector<vector<string>>& pairs, 
      const vector<double>& rate) {
    // The input is generated such that there are no contradictions or cycles in the conversion graphs for either day
    // This means that USD -> EUR = 2.0, EUR -> JPY = 3.0, JPY -> USD = 1.0 is impossible

    unordered_map<string, Node*> table;
    int n = pairs.size();
    for (int i = 0; i < n; ++i) {
      const auto& pair = pairs[i];
      auto it0 = table.find(pair[0]);
      auto it1 = table.find(pair[1]);
      auto end = table.end();

      if (it0 == end && it1 == end) {
        Node* p0 = new Node{{nullptr}, {rate[i]}, 0.0};
        Node* p1 = new Node{{p0}, {1/rate[i]}, 0.0};
        p0->next[0] = p1;
        table.emplace(pair[0], p0);
        table.emplace(pair[1], p1);
      } else if (it0 != end && it1 == end) {
        Node* p0 = it0->second;
        Node* p1 = new Node{{p0}, {1/rate[i]}, 0.0};
        table.emplace(pair[1], p1);
        p0->next.push_back(p1);
        p0->rate.push_back(rate[i]);
      } else if (it0 == end && it1 != end) {
        Node* p1 = it1->second;
        Node* p0 = new Node{{p1}, {rate[i]}, 0.0};
        table.emplace(pair[0], p0);
        p1->next.push_back(p0);
        p1->rate.push_back(1 / rate[i]);
      } else {
        Node* p0 = it0->second;
        Node* p1 = it1->second;
        p0->next.push_back(p1);
        p0->rate.push_back(rate[i]);
        p1->next.push_back(p0);
        p1->rate.push_back(1 / rate[i]);
      }
    }
    
    // fill in values
    if (!table.contains(ic)) return;

    table[ic]->val = 1.0;
    dest.emplace(ic, 1.0);
    queue<Node*> que;
    que.push(table[ic]);
    while (!que.empty()) {
      Node* cur = que.front();
      que.pop();
      auto& next = cur->next;
      for (int i = 0; i < next.size(); ++i) {
        if (next[i]->val != 0.0) continue;

        next[i]->val = cur->val * cur->rate[i];
        que.push(next[i]);
      }
    }
    for (const auto [currency, node] : table) {
      dest.emplace(currency, node->val);
    }
  }
};

int main() {
  Solution demo;
  demo.maxAmount("B", 
    {{"HB","NZ"},{"B","S"},{"S","HB"}},
    {3.9,4.1,6.9}, 
    {{"NZ","S"},{"NZ","HB"},{"S","B"}},
    {9.9,1.5,1.8}
  );
}