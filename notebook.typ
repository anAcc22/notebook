// NOTE: formatter (prettypst): https://github.com/antonWetzel/prettypst
#set page(paper: "a4", flipped: true, margin: 0.5cm, columns: 3)
#set columns(gutter: 5pt)
#set text(font: "Alegreya", size: 8pt)
#set raw(theme: "themes/Lazy.tmTheme")
#set heading(numbering: "1.")

#show raw: set text(font: "Maple Mono", size: 6pt)

#import "@preview/codelst:2.0.2": sourcecode as codelst-sourcecode, sourcefile as codelst-sourcefile

#let sourcefile(section_color, filename, ..args) = codelst-sourcefile(read(filename), file: filename, frame: block.with(
  fill: none,
  stroke: (paint: section_color, thickness: 0.75pt, dash: "densely-dash-dotted"),
  radius: 2pt,
  inset: (x: 5pt, y: 2.5pt),
), gutter: 5pt, numbers-start: 1, ..args)

#let INTRODUCTION_COLOR = color.hsl(0deg, 70%, 40%)
#let DSU_COLOR = color.hsl(50deg, 70%, 40%)
#let SORTING_COLOR = color.hsl(100deg, 70%, 40%)
#let MATCHING_COLOR = color.hsl(150deg, 70%, 40%)
#let SQRT_COLOR = color.hsl(200deg, 70%, 40%)
#let TREAP_COLOR = color.hsl(250deg, 70%, 40%)
#let GRAPH_COLOR = color.hsl(300deg, 70%, 40%)
#let FLOW_COLOR = color.hsl(350deg, 70%, 40%)
#let SPARSE_TABLE_COLOR = color.hsl(400deg, 70%, 40%)
#let FENWICK_COLOR = color.hsl(450deg, 70%, 40%)
#let SEGMENT_TREE_COLOR = color.hsl(500deg, 70%, 40%)
#let CONVOLUTION_COLOR = color.hsl(550deg, 70%, 40%)
#let MATH_COLOR = color.hsl(600deg, 70%, 40%)
#let STRING_COLOR = color.hsl(650deg, 70%, 40%)

#let INFI = 1000

= Introduction

Most snippets assume the following macros.

#sourcefile(INTRODUCTION_COLOR, "templates/base_template.cpp", showrange: (1, 38))

== Template (Proton)

#sourcefile(INTRODUCTION_COLOR, "templates/proton_template.cpp", showrange: (1, 19))

== Template (Baytoro)

#sourcefile(INTRODUCTION_COLOR, "templates/baytoro_template.cpp", showrange: (1, 9))

== I/O

For large inputs, it may be necessary to enable fast I/O.

```cpp
cin.tie(nullptr)->sync_with_stdio(false);
```

Regarding interactive problems, remember to flush the stream using `endl`!

== Order Statistic Tree

#sourcefile(INTRODUCTION_COLOR, "others/ost.cpp")

== Custom Hash

While this slows down `unordered_map` a little, it helps prevent hacks.

#sourcefile(INTRODUCTION_COLOR, "others/custom_hash.cpp", showrange: (5, 17))

== Random Number Generation

To generate a random integer, first set up `gen`.

```cpp
mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
```

After which, you can use `uniform_int_distribution` to produce a random
integer in a closed interval.

= Disjoint Set Union

Nodes with negative values are roots. `cmpCnt` and `cmpMax` find the number
of components and the size of the largest component respectively. Omit if not necessary.

#sourcefile(DSU_COLOR, "dsu/dsu.cpp", showrange: (3, INFI))

== Persistent Variant

Check if two nodes are connected at some point in time.

#sourcefile(DSU_COLOR, "dsu/persistent_dsu.cpp", showrange: (3, INFI))

= Sorting

== Custom `struct`/`class`

Suppose we have some custom `struct` representing fractions, to create a `set`,
we need to perform operator overloading of `<`.

#sourcefile(SORTING_COLOR, "sorting/fraction_example.cpp", showrange: (1, INFI))

== Inversions Count

An array's _inversions count_ refers to the number of adjacent swaps required
to sort an array. It can be computed via a modified merge sort, which has
the side effect of sorting the array.

#sourcefile(SORTING_COLOR, "sorting/inversions.cpp", showrange: (3, INFI))

= Matching

== Maximum Cardinality Bipartite Matching (MCBM)

A maximum matching contains as many edges of a graph $G$ as
possible such that each vertex is part of at most one edge of
the subset. Assume that `0 <= u < lsize` and `0 <= v < rsize` in the
following implementation.

#sourcefile(MATCHING_COLOR, "matching/hopcroft_karp.cpp", showrange: (3, INFI))

=== Minimum Vertex Cover

Assuming you have obtained the matching above, you can retrieve the _minimum vertex
cover_ (the smallest set of vertices that includes at least one endpoint of every edge of the graph)
by constructing a new _directed_ graph. Edges that belong to the matching will go from right to left,
whereas all other edges will go from left to right. Perform a depth first search starting at
all left vertices that are not incident to any edges in the matching.

The minimum vertex cover includes all visited right vertices of the matching, as well as all
unvisited left vertices of the matching.

Note that some problems also have situations where there are isolated nodes (degree zero) that have
to be taken.

#sourcefile(MATCHING_COLOR, "matching/min_vertex_cover.cpp", showrange: (3, INFI))

== Perfect Matching

A perfect matching is one where every vertex is included in exactly one edge of the
matching. The following implementation finds the minimum weight perfect matching. To
obtain the maximum weight variant, simply invert all the costs.

#sourcefile(MATCHING_COLOR, "matching/min_weight_perfect_matching.cpp", showrange: (3, INFI))

= Square Root Decomposition

Assuming `block` represents the size of a chunk, `a` represents the original, full-sized array,
and `b` represents the values of each block, the example snippet demonstrates a sum query. A
good value for `block` is around $250$.

#sourcefile(SQRT_COLOR, "sqrt_decomposition/sqrt_query.cpp", showrange: (5, INFI))

== Mo's Algorithm

#sourcefile(SQRT_COLOR, "sqrt_decomposition/mo.cpp", showrange: (5, INFI))

= Treap

== Implicit Variant

Insertion and deletion are done based on the zero-indexed position of an element
within the tree. Nodes in the snippet store `string` values, remember to modify
depending on the problem.

#sourcefile(TREAP_COLOR, "treap/implicit.cpp", showrange: (5, 118))

== Cartesian Tree

We may also construct it from an array, assuming no further updates to the array
are required. The smallest value belongs to the `root`, which stores the corresponding
index. Assuming all values are distinct, the resulting tree is unique.

#sourcefile(TREAP_COLOR, "treap/cartesian_tree.cpp", showrange: (3, INFI))

== Lazy Propagation

The following snippet illustrates a non-implicit treap with
range addition.

#sourcefile(TREAP_COLOR, "treap/range_addition.cpp", showrange: (3, INFI))

= Graphs

== Cycle Retrieval

In problems where `a[i]` represents the next "jump" from position `i`,
the following snippet finds all cycles, which may be used for further
processing.

#sourcefile(GRAPH_COLOR, "graphs/cycle.cpp", showrange: (5, 28))

== Diameter

The furthest distance a node `u` is from some other node in a tree is equivalent to
`max(dist(dia_u, u), dist(dia_v, v))`, where `dia_u` and `dia_v` represent the endpoints
of some diameter.

#sourcefile(GRAPH_COLOR, "graphs/diameter.cpp", showrange: (3, INFI))

== Bridges

A _bridge_ is an edge of a graph whose deletion increases the graph's
number of connected components. `memo[u]` represents the number of
_back-edges_ passing over the edge between `u` and its parent.

#sourcefile(GRAPH_COLOR, "graphs/bridges.cpp", showrange: (3, INFI))

== Cut Vertices

When a _cut vertex_ is removed, the graph is disconnected.

#sourcefile(GRAPH_COLOR, "graphs/cut_vertices.cpp", showrange: (3, INFI))

== Edge Cactus

Every edge belongs to at most one cycle. You may find all cycles by merging the
edges with `DSU`.

#sourcefile(GRAPH_COLOR, "graphs/edge_cactus.cpp", showrange: (23, INFI))

== Eulerian Paths/Circuits

=== Undirected
Assuming we have an undirected _connected_ graph, if all vertices have an
_even_ degree, an Eulerian circuit exists; otherwise, if we have two
vertices of odd degree, an Eulerian path exists (`o1` and `o2` represent
the two odd vertices).

Be careful about self-loops, they don't count towards the degree!
In general this algorithm is pretty expensive, so perform it _just once_ if possible.

#sourcefile(GRAPH_COLOR, "graphs/eulerian_path.cpp", showrange: (3, INFI))

=== Directed
A directed graph has an Eulerian circuit if and only if it is _connected_
and each vertex has the same in-degree as out-degree. A directed graph
has an Eulerian path if and only if it is connected and each vertex
except two has an in-degree as out-degree.

One of the two should have an out-degree one greater than in-degree
(_start vertex_), while the other has an in-degree one greater than
out-degree (_end vertex_). The core algorithm is the same as that
for the undirected graph.

== Binary Lifting

Before we can perform binary lifting, we have to first construct a table
`tab`, where `tab[i][h]` represents the $2ʰ$-th ancestor of `i`.

#sourcefile(GRAPH_COLOR, "graphs/binary_lifting.cpp", showrange: (3, INFI))

== Heavy Light Decomposition

If you want to update the value of node `u`, you need to update `pos[u]`.
`query` needs to be tweaked depending on the problem.

#sourcefile(GRAPH_COLOR, "graphs/hld.cpp", showrange: (39, INFI))

== Tree Hashing

You can hash a _rooted_ tree like so. If it isn't rooted, you may find a
centroid first before using it as a root to perform the hash. Some trees
may have _two_ centroids, in which case you have to retrieve two hashes. Among
the two, put the smaller one before the larger one in a pair of integers
(e.g., in `V<int>`).

#sourcefile(GRAPH_COLOR, "graphs/tree_hashing.cpp", showrange: (87, INFI))

== Centroid Decomposition

`ancestors[u]` returns the list of ancestors of `u` (along with the distance)
as we go up the centroid decomposition tree.

#sourcefile(GRAPH_COLOR, "graphs/centroid_decomposition.cpp", showrange: (5, INFI))

== 2-SAT

#sourcefile(GRAPH_COLOR, "graphs/two_sat.cpp", showrange: (3, INFI))

== Small-To-Large Merging

Instead, of each node having its own set of objects, try to reuse the children
sets as much as possible. This reduces the number of swaps/inserts and improves
the constant factor. The following snippet solves CSES's Distinct Colors, which asks
you to find the number of distinct colors in each subtree.

#sourcefile(GRAPH_COLOR, "graphs/small_to_large.cpp", showrange: (5, INFI))

= Flows

== Edmonds-Karp

Suppose we have already set up `adj` and `cap`, where `cap` represents
the capacity of each edge; we may use this algorithm to determine
the maximum flow in a flow network. When adding an edge, we need to include both
$(u, v)$ and $(v, u)$ in `adj`, however, we'll only set the capacity of $(u, v)$
to whatever it is.

To determine the *minimum cut*, find all vertices that can be reached from
the source, using only edges with positive residual capacity.

#sourcefile(FLOW_COLOR, "flows/edmonds_karp.cpp", showrange: (5, INFI))

== Dinic's Algorithm

Remember to reset all the edges if you need to compute the flow to some new
destination. It's also possible to get the incremental flow by adding edges and
calling `flow` repeatedly.

#sourcefile(FLOW_COLOR, "flows/dinic.cpp", showrange: (3, INFI))

= Sparse Table

#sourcefile(SPARSE_TABLE_COLOR, "sparse_table/rmq.cpp", showrange: (3, INFI))

= Fenwick Tree

== One-Dimensional Queries

#sourcefile(FENWICK_COLOR, "fenwick/1d.cpp", showrange: (3, INFI))

== Two-Dimensional Queries

#sourcefile(FENWICK_COLOR, "fenwick/2d.cpp", showrange: (3, INFI))

== Range Addition/Queries

This is a tiny bit faster compared to using segment trees.

#sourcefile(FENWICK_COLOR, "fenwick/range_addition.cpp", showrange: (3, INFI))

= Segment Tree

== RMQ (Iterative)

It can help to avoid TLE in certain situations.

#sourcefile(SEGMENT_TREE_COLOR, "segment_tree/rmq_iterative.cpp", showrange: (3, INFI))

== RMQ (Recursive)

#sourcefile(SEGMENT_TREE_COLOR, "segment_tree/rmq_recursive.cpp", showrange: (3, INFI))

== Lazy Propagation

=== Range Addition/Assignment (Min Query)

#sourcefile(SEGMENT_TREE_COLOR, "segment_tree/lazy_min.cpp", showrange: (3, INFI))

=== Range Addition/Assignment (Sum Query)

#sourcefile(SEGMENT_TREE_COLOR, "segment_tree/lazy_sum.cpp", showrange: (3, INFI))

=== Range Addition/Multiplication (Sum Query)

#sourcefile(SEGMENT_TREE_COLOR, "segment_tree/lazy_add_multiply.cpp", showrange: (85, INFI))

=== Polynomial Queries

Add `[base, base+1, base+2, ...]` to the range `[l, r]`.

#sourcefile(SEGMENT_TREE_COLOR, "segment_tree/polynomial.cpp", showrange: (3, INFI))

=== Range Addition (Count Minimums)

`query` returns the minimum value in a range, as well as the corresponding count.

#sourcefile(SEGMENT_TREE_COLOR, "segment_tree/range_add_count_minimums.cpp", showrange: (3, INFI))

== Persistent Segment Tree

Stores earlier versions of the tree. To create a new version, use `cpy_root`.

#sourcefile(SEGMENT_TREE_COLOR, "segment_tree/persistent_tree.cpp", showrange: (3, INFI))

== Merge Sort Tree

Stores the result of merge sort operations; may be used to answer queries such as finding
the number of items $<= x$ within a range.

#sourcefile(SEGMENT_TREE_COLOR, "segment_tree/merge_sort_tree.cpp", showrange: (3, INFI))

= Convolution

== Number Theoretic Transform

#sourcefile(CONVOLUTION_COLOR, "convolution/ntt.cpp", showrange: (3, INFI))

= Math

== Extended Euclidean Algorithm

Finds $x$ and $y$ such that $x a + y b = gcd(a, b)$.

#sourcefile(MATH_COLOR, "math/extended_euclid.cpp", showrange: (3, INFI))

== `Mint`

#sourcefile(MATH_COLOR, "math/mint.cpp", showrange: (3, INFI))

== Sieve of Eratosthenes

#sourcefile(MATH_COLOR, "math/sieve.cpp", showrange: (3, INFI))

=== Euler's Totient Function

$phi(n)$ computes the positive integers up to $n$ that are coprime to $n$. We can
compute it from the prime factors of $n$.

#sourcefile(MATH_COLOR, "math/euler_totient.cpp", showrange: (5, INFI))

We can also compute it using a modified `sieve`.

#sourcefile(MATH_COLOR, "math/sieve_euler_totient.cpp", showrange: (3, INFI))

== Fast Factorization

Runs in about $cal(O)(n^(1 / 4))$ time, to be used sparingly.

#sourcefile(MATH_COLOR, "math/fast_factor.cpp", showrange: (3, INFI))

== Frobenius Number

The _Frobenius number_ is the largest integer that _can't_ be
expressed as a non-negative linear combination of two coprime integers
$p$ and $q$. It is computed as $p q - p - q$.

== Matrix

May be helpful for matrix multiplication problems.

#sourcefile(MATH_COLOR, "math/matrix.cpp", showrange: (3, INFI))

= Strings

== String Splitting

Because `C++` doesn't offer a `split` function by default, we may have to
write our own sometimes.

#sourcefile(STRING_COLOR, "strings/string_split.cpp", showrange: (3, INFI))

== Hashing

You may use two different prime numbers to create a stronger hash.

#sourcefile(STRING_COLOR, "strings/hash.cpp", showrange: (85, INFI))

== Manacher's Algorithm

Computes the maximum length of a palindrome centered at any index.

#sourcefile(STRING_COLOR, "strings/manacher.cpp", showrange: (3, INFI))

== Z-function

The _Z-function_ of a string is an array of length $n$ where the $i$\-th
element is equal to the greatest number of characters starting from
position $i$ that coincides with the first characters of the string.

#sourcefile(STRING_COLOR, "strings/z_function.cpp", showrange: (3, INFI))

== Trie

#sourcefile(STRING_COLOR, "strings/trie.cpp", showrange: (3, INFI))

You can also find the maximum XOR of a subarray.

#sourcefile(STRING_COLOR, "strings/max_xor_subarray.cpp", showrange: (3, INFI))

== Suffix Array

A _suffix array_ contains integers that represent the _starting indexes_
of all suffixes of a given string, in sorted order.

#sourcefile(STRING_COLOR, "strings/suffix_array.cpp", showrange: (3, INFI))

You can also modify it to retrieve the length of the longest common prefix
between two suffixes starting at `i` and `j`.

#sourcefile(STRING_COLOR, "strings/lcp.cpp", showrange: (3, INFI))

== Aho-Corasick Algorithm

This variant checks if any substring of a string `s` matches any string in
the dictionary.

#sourcefile(STRING_COLOR, "strings/aho_corasick.cpp", showrange: (3, INFI))
