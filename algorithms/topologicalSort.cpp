#include <bits/stdc++.h>
using namespace std;

// the graph class
class Graph
{
public:
  vector<vector<int>> adj;
  vector<bool> visited;
  vector<int> distances;
  vector<int> fromNode; // keeps a record of parent of every element in bfs
  vector<int> connectedComponents;
  vector<int> stronglyConnectedComponents;
  int v; // no of vertices
  int e; // no of edeges

  Graph(int v) //constructor
  {
    this->v = v;
    adj.resize(v); //resize allocates and initialises the vector of vector
    // allocating and initialising other attributes
    visited.resize(v, false);
    distances.resize(v, -1);
    fromNode.resize(v, -1);
    connectedComponents.resize(v, -1);
    stronglyConnectedComponents.resize(v, -1);
  }

  // depth first search api
  void dfs(int s)
  {
    visited.assign(v, false); // preparing the visited array for dfs
    dfs(s, visited);
  }

  // depth first search implementation
  void dfs(int s, vector<bool> &visited)
  {
    // if visited return
    if (visited[s])
    {
      return;
    }
    else
    {
      visited[s] = true;
      //for every child of s ie every element of the vector at adj[s]
      for (auto child : adj.at(s)) // do dfs on the children
      {
        dfs(child, visited);
      }
    }
  }

  // breadth first search api
  void bfs(int s)
  {
    visited.assign(v, false);
    distances.assign(v, -1);
    fromNode.assign(v, -1);
    bfs(s, visited, distances, fromNode);
  }

  //breadth first search implementation
  void bfs(int s, vector<bool> &visited, vector<int> &distances, vector<int> &fromNode)
  {
    queue<int> q;
    // processing s
    visited[s] = true;
    distances[s] = 0;
    fromNode[s] = s;
    q.push(s); // push s to the string

    while (!q.empty()) // while q is not empty
    {
      int parent = q.front(); // pop and get front element as parent
      q.pop();

      for (auto child : adj.at(parent)) // for all the children of the parent
      {
        // if visited continue
        if (visited[child])
        {
          continue;
        }
        else
        {
          visited[child] = true;                    // mark as visited
          distances[child] = distances[parent] + 1; // record the distance
          fromNode[child] = parent;                 // note the parent

          q.push(child); // push the child to the queqe so that its children could be processed
        }
      }
    }
  }

  // a method that returns the reverse graph of the current graph
  vector<vector<int>> reverseGraph() // tested: works
  {
    vector<vector<int>> result;
    result.resize(v);
    int i = 0;

    for (i = 0; i < v; i++)
    {
      for (auto child : adj.at(i))
      {
        result.at(child).push_back(i);
      }
    }
    return result;
  }

  // input methods

  // input for directed graphs
  void directedInput(int e)
  {
    this->e = e;
    for (int i = 0; i < e; i++)
    {
      int u, v;
      std::cin >> u >> v;

      addEdge(u, v);
    }
  }

  // input for undirected graphs
  void undirectedInput(int e)
  {
    this->e = e;
    for (int i = 0; i < e; i++)
    {
      int u, v;
      std::cin >> u >> v;

      addEdge(u, v);
      addEdge(v, u);
    }
  }

  void addEdge(int u, int v)
  {
    adj.at(u).push_back(v);
  }

  // a method to print the graph
  void printGraph()
  {
    std::cout << "Graph: " << endl;
    int i = 0;
    for (auto parent : adj) // here parent is also a vector inside of adj
    {
      std::cout << i++ << " -> ";
      for (auto child : parent) // here child is an integer
      {
        std::cout << child << " ";
      }
      std::cout << endl;
    }
    std::cout << endl;
  }

  // a general method used to print all the vectors in the attributes
  template <typename T>
  void printVector(vector<T> vec, std::string vectorName)
  {
    std::cout << vectorName << ": " << std::endl;
    int i = 0;
    for (auto element : vec)
    {
      std::cout << i++ << ": " << element << endl;
    }
    std::cout << endl;
  }
};
/*
theory for post order and topological sort:

so the post order is the order when an element is added to the order once it is done
in the case of a graph it is implemented using dfs and when we are done processing all the
children of a node then only it is added to the post order
the topological sort for a graph is the reverse of post order and a stack is used 
to find the reverse postorder
*/

// implementation of dfs for reverse post order
void dfsForReversePostorder(Graph &graph, int s, deque<int> &deq)
{
  if (graph.visited[s])
  {
    return;
  }
  else
  {
    graph.visited[s] = true;
    for (auto child : graph.adj.at(s))
    {
      dfsForReversePostorder(graph, child, deq);
    }
    deq.push_front(s);
  }
}

// method that returns a reverse post order in the form of a deque<int>
deque<int> reversePostorder(Graph &graph)
{
  deque<int> resultDeque;
  graph.visited.assign(graph.v, false);

  for (int i = 0; i < graph.v; i++)
  {
    if (!graph.visited[i])
    {
      dfsForReversePostorder(graph, i, resultDeque);
    }
  }
  return resultDeque;
}

// a method that prints the topological sort
void printTopologicalSort(Graph graph)
{
  deque<int> sortedOrder = reversePostorder(graph);

  std::cout << "Topological Sort: " << endl;
  for (auto num : sortedOrder)
  {
    std::cout << num << " ";
  }
  std::cout << "\n";
}

int main()
{
  freopen("builds/input.txt", "r", stdin);
  freopen("builds/output.txt", "w", stdout);

  Graph graph(5);
  graph.directedInput(6);
  printTopologicalSort(graph);
}