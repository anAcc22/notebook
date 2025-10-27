#include "../templates/base_template.hpp"

struct FlowEdge {
  int v, u;
  ll cap, flow = 0;
  FlowEdge(int v, int u, ll cap)
      : v(v)
      , u(u)
      , cap(cap) {}
};

struct Dinic {
  const ll flow_inf = OO;
  vector<FlowEdge> edges;
  vector<vector<int>> adj;

  int n, m = 0;
  int s, t;

  vector<int> level, ptr;
  queue<int> q;

  Dinic(int n, int s)
      : n(n)
      , s(s) {
    adj.resize(n);
    level.resize(n);
    ptr.resize(n);
  }

  void add_edge(int v, int u, ll cap) { // NOTE: add edge (v -> u)
    edges.emplace_back(v, u, cap);
    edges.emplace_back(u, v, 0);
    adj[v].push_back(m);
    adj[u].push_back(m + 1);
    m += 2;
  }

  bool bfs() {
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int id : adj[v]) {
        if (edges[id].cap == edges[id].flow) continue;
        if (level[edges[id].u] != -1) continue;
        level[edges[id].u] = level[v] + 1;
        q.push(edges[id].u);
      }
    }
    return level[t] != -1;
  }

  ll dfs(int v, ll pushed) {
    if (pushed == 0) return 0;
    if (v == t) return pushed;
    for (int &cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
      int id = adj[v][cid];
      int u  = edges[id].u;
      if (level[v] + 1 != level[u]) continue;
      ll tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
      if (tr == 0) continue;
      edges[id].flow += tr;
      edges[id ^ 1].flow -= tr;
      return tr;
    }
    return 0;
  }

  ll flow(int t_) {
    t    = t_;
    ll f = 0;
    while (true) {
      fill(A(level), -1);
      level[s] = 0;
      q.push(s);
      if (!bfs()) break;
      fill(A(ptr), 0);
      while (ll pushed = dfs(s, flow_inf)) {
        f += pushed;
      }
    }
    return f;
  }
};
