#include <unordered_map>
#include <vector>
using namespace std;

// Group: connected component
struct Group {
  vector<int> vertices; 
  int edge_cnt;

  void addVertex(int vertex) {
    vertices.push_back(vertex);
    ++edge_cnt;
  }

  void combine(Group& other) {
    vertices.insert(vertices.end(), other.vertices.begin(), other.vertices.end());
    edge_cnt += other.edge_cnt;
    ++edge_cnt;
  }
};

class Solution {
public:
  int countCompleteComponents(int n, vector<vector<int>>& edges) {
    // A connected component with n vertices <=> 
    // has n * (n - 1) / 2 distinctive edge
    // Notice that: There are no repeated edges.
    // So, we just need to record the number
    // of vertices and edges of each connected 
    // component (group).

    // graph -> key: group number, value: Group
    unordered_map<int, Group> graph;
    // group[i] = j means vertex i is in group j
    vector<int> groups(n, -1);
    int new_group_no = 0; // An increasing number, should never decrease

    for (const vector<int>& edge : edges) {
      const int gnl = groups[edge[0]]; // group number of left vertex
      const int gnr = groups[edge[1]]; // group number of right vertex

      if (gnl < 0 && gnr < 0) {
        // Allocate new group for them
        groups[edge[0]] = new_group_no;
        groups[edge[1]] = new_group_no;
        graph.insert({new_group_no, {edge, 1}});
        ++new_group_no;
      } else if (gnl < 0) {
        // Add left vertex to gnr
        groups[edge[0]] = gnr;
        graph[gnr].addVertex(edge[0]);
      } else if (gnr < 0) {
        // Add right vertex to gnl
        groups[edge[1]] = gnl;
        graph[gnl].addVertex(edge[1]);
      } else {
        // If already in same group
        if (gnl == gnr) {
          ++graph[gnl].edge_cnt;
          continue;
        } 
        
        // merge gnr into gnl
        for (int& group_no : groups) {
          if (group_no == gnr) group_no = gnl;
        }
        graph[gnl].combine(graph[gnr]);
        graph.erase(gnr);
      }
    }

    int ans = 0;
    for (const auto& group : graph) {
      int edge_cnt = group.second.edge_cnt;
      int vertex_cnt = group.second.vertices.size();
      if (edge_cnt == (vertex_cnt * (vertex_cnt - 1)) / 2) {
        ++ans;
      }
    }

    // Add isolated vertices
    for (const int& group : groups) {
      if (group < 0) ++ans;
    }
    return ans;
  }
};