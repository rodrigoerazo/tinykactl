/* KTH ACM Contest Template Library
 *
 * Graph/Shortest path/Bellman-Ford
 *
 * Credit:
 *   Based on Popup-02 lecture
 *   By Mattias de Zalenski
 */

template <class E, class M, class P, class D>
bool bellman_ford(E &edges, M &min, P &path, int start, int n, D distfun) {
  typedef typename M::value_type T;
  typedef typename E::value_type L;
  typedef typename L::const_iterator L_iter;
  T inf(1<<29);

  for (int i = 0; i < n; i++) {
    min[i] = inf;
    path[i] = -1;
  }
  min[start] = T();
  for (int i = 1; i < n; ++i) // V-1 times
    for (int node = 0; node < n; ++node) {
      const L &l = edges[node];
      for (iterator it = l.begin(); it != l.end(); ++it) {
	pair<int, T> p = distfun(*it, min[node]);
	int dest = p.first; T dist = min[node] + p.second;
	if (dist < min[dest]) {
	  min[dest] = dist;
	  path[dest] = node;
	}
      }
    }
  for (int node = 0; node < n; ++node) {
    const L &l = edges[node];
    for (iterator it = l.begin(); it != l.end(); ++it) {
      pair<int, T> p = distfun(*it, min[node]);
      int dest = p.first; T dist = min[node] + p.second;
      if (dist < min[dest]) return false; // negative cycle!
    }
  }
  return true; // graph is negative-cycle-free
}