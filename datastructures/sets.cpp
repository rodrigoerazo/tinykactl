/*****************************************************************************
 * 
 * MST1: sets
 * ==========
 *
 * Simple set routines to easily determine if two elements are in the
 * same set. The only operation is link (union).
 *
 * The set routines main usage is for finding the connected components
 * of a graph or Kruskal's MST algorithm. They have a entirely different
 * usage than STL's sets.
 *
 * (uses path compression and union by rank)
 *
 * COMPLEXITY  O(1) (in average every set operation runs in constant time)
 *
 * ------------------------------------------------------------------------- *
 *
 * NADA acmlib (10 March 2002)
 * Templates for KTH-NADA, Ballons'R'Us, ACM 2001-2002
 *   Swedish competition, Link?ping 6 Oct 2001
 *   Revised for SWERC, Portu, Portugal 17 Nov 2001
 *   Revised for World Finals, Honolulu, 23 Mar 2002
 *   David Rydh, Mattias de Zalenski, Fredrik Niemel?
 *
 *****************************************************************************/

#include <vector>

struct sets {
  struct set_elem {
    int head, rank; // rank is a pseudo-height with height<=rank
    set_elem(int elem) : head(elem), rank(0) {}
  };
  vector<set_elem>  elems;

  sets(int nElems) {
    for(int i = 0; i < nElems; i++) elems.push_back(set_elem(i));
  }

  int get_head( int i ) { // Find head of set with path-compression
    if (i != elems[i].head) elems[i].head = get_head(elems[i].head);
    return elems[i].head;
  }

  bool equal(int a, int b) { return (get_head(a) == get_head(b)); }

  void link( int a, int b ) { // union sets
    a = get_head(a); b = get_head(b);
    if(elems[a].rank > elems[b].rank) elems[b].head = a;
    else {
      elems[a].head = b;
      if(elems[a].rank == elems[b].rank) elems[b].rank++;
    }
  }
};
