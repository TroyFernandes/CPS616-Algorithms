# CPS616-Algorithms


### [Lab 1 - Sorting and Problem Size](https://github.com/TroyFernandes/CPS616-Algorithms/tree/master/Lab%201%20-%20Sorting%20and%20Problem%20Size/Lab%201)
Comparison of O(n<sup>2</sup>) algorithms (Selection Sort + Merge Sort). Three cases are tested:

1) Standard Selection Sort
2) Standard Merge Sort
3) Merge Sort with Selection Sort when the subarrays are small enough

### [Lab 2 - Divide and Conquer](https://github.com/TroyFernandes/CPS616-Algorithms/tree/master/Lab%202%20-%20Divide%20and%20Conquer/Lab%202%20-%20Divide%20and%20Conquer)

Large integer multiplication, where the result is too large to be stored in regular integer data types. Strings + Vectors are used to represent these large numbers

### [Lab 3 - Minimum Spanning Trees](https://github.com/TroyFernandes/CPS616-Algorithms/tree/master/Lab%203%20-%20Minimum%20Spanning%20Trees/Lab%203%20-%20Minimum%20Spanning%20Trees)

Finds the minimum spanning tree of an undirected graph, given as an adjacency matrix using [Prim's Algorithm](https://en.wikipedia.org/wiki/Prim%27s_algorithm)

One thing to note, this version of Prim's is NOT using a binary heap. This is the standard O(|V|<sup>2</sup>) complexity using an adjacency matrix (which is more rare I think?). Check out the code if you're looking for help on how to implement Prim's using an adjacency matrix.

### [Lab 4 - Greedy Interval Scheduling](https://github.com/TroyFernandes/CPS616-Algorithms/tree/master/Lab%204%20-%20Greedy%20Interval%20Scheduling/Lab%204%20-%20Greedy%20Interval%20Scheduling)

Implements a greedy algorithm for accommodating bookings in a hotel with N rooms

### [Lab 5 - Dynamic 0/1 Knapsack](https://github.com/TroyFernandes/CPS616-Algorithms/tree/master/Lab%205%20-%20Dynamic%20Knapsack/Lab%205%20-%20Dynamic%20Knapsack)

Finds an optimal solution to the 0/1 Knapsack problem. Two functions are implemented:

1) The brute force method O(2<sup>n</sup>)
2) Dynamic method O(nW) where n = # of items, W = capacity of knapsack


