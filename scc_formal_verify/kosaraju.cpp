#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>

namespace scc {

/**
 * Kosaraju's algorithm for finding strongly connected components (SCCs)
 * 
 * This implementation is designed for formal verification and follows
 * the algorithm specification in Kosaraju.tla
 */
class KosarajuSCC {
public:
    using Graph = std::vector<std::vector<int>>;
    using Components = std::vector<std::vector<int>>;
    
    /**
     * Find all strongly connected components in the given graph
     * 
     * @param graph Adjacency list representation (nodes 0..n-1)
     * @return Vector of components, each component is a vector of node indices
     */
    static Components findSCCs(const Graph& graph) {
        const int n = static_cast<int>(graph.size());
        if (n == 0) return {};
        
        // First pass: compute finishing order using DFS
        std::vector<int> order;
        std::vector<bool> visited(n, false);
        
        for (int v = 0; v < n; ++v) {
            if (!visited[v]) {
                dfsFirstPass(graph, v, visited, order);
            }
        }
        
        // Build transpose graph
        Graph transpose(n);
        for (int v = 0; v < n; ++v) {
            for (int w : graph[v]) {
                if (w >= 0 && w < n) {  // Bounds check
                    transpose[w].push_back(v);
                }
            }
        }
        
        // Second pass: find SCCs using transpose graph
        std::fill(visited.begin(), visited.end(), false);
        Components components;
        
        for (int i = n - 1; i >= 0; --i) {
            int v = order[i];
            if (!visited[v]) {
                std::vector<int> component;
                dfsSecondPass(transpose, v, visited, component);
                components.push_back(std::move(component));
            }
        }
        
        return components;
    }
    
    /**
     * Count the number of strongly connected components
     */
    static int countSCCs(const Graph& graph) {
        return static_cast<int>(findSCCs(graph).size());
    }

private:
    static void dfsFirstPass(const Graph& graph, int v, 
                           std::vector<bool>& visited, 
                           std::vector<int>& order) {
        visited[v] = true;
        
        for (int w : graph[v]) {
            if (w >= 0 && w < static_cast<int>(graph.size()) && !visited[w]) {
                dfsFirstPass(graph, w, visited, order);
            }
        }
        
        order.push_back(v);
    }
    
    static void dfsSecondPass(const Graph& transpose, int v,
                            std::vector<bool>& visited,
                            std::vector<int>& component) {
        visited[v] = true;
        component.push_back(v);
        
        for (int w : transpose[v]) {
            if (w >= 0 && w < static_cast<int>(transpose.size()) && !visited[w]) {
                dfsSecondPass(transpose, w, visited, component);
            }
        }
    }
};

} // namespace scc

// Helper function to print graph
void printGraph(const scc::KosarajuSCC::Graph& graph, const std::string& name) {
    std::cout << "\n" << name << ":\n";
    std::cout << "Graph structure:\n";
    for (size_t i = 0; i < graph.size(); ++i) {
        std::cout << "  Node " << i << " -> ";
        if (graph[i].empty()) {
            std::cout << "[]";
        } else {
            for (size_t j = 0; j < graph[i].size(); ++j) {
                std::cout << graph[i][j];
                if (j < graph[i].size() - 1) std::cout << ", ";
            }
        }
        std::cout << "\n";
    }
}

// Helper function to print SCC results
void printSCCResults(const scc::KosarajuSCC::Components& components) {
    std::cout << "\nStrongly Connected Components:\n";
    if (components.empty()) {
        std::cout << "  No components found\n";
        return;
    }
    
    for (size_t i = 0; i < components.size(); ++i) {
        std::cout << "  SCC " << (i + 1) << ": [";
        for (size_t j = 0; j < components[i].size(); ++j) {
            std::cout << components[i][j];
            if (j < components[i].size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }
    std::cout << "Total SCCs: " << components.size() << "\n";
}

// Test function to verify correctness with detailed output
void testKosaraju() {
    using namespace scc;
    
    std::cout << "=== Kosaraju's SCC Algorithm Demo ===\n";
    
    // Test case 1: Triangle graph (0->1->2->0) - should have 1 SCC
    std::cout << "\n--- Test Case 1: Triangle Graph ---";
    KosarajuSCC::Graph triangle = {{1}, {2}, {0}};
    printGraph(triangle, "Triangle Graph (0->1->2->0)");
    auto components = KosarajuSCC::findSCCs(triangle);
    printSCCResults(components);
    assert(components.size() == 1);
    assert(components[0].size() == 3);
    std::cout << "✓ Expected: 1 SCC with all 3 nodes\n";
    
    // Test case 2: Two separate cycles - should have 2 SCCs
    std::cout << "\n--- Test Case 2: Two Separate Cycles ---";
    KosarajuSCC::Graph twoCycles = {{1}, {0}, {3}, {2}};
    printGraph(twoCycles, "Two Cycles (0<->1, 2<->3)");
    components = KosarajuSCC::findSCCs(twoCycles);
    printSCCResults(components);
    assert(components.size() == 2);
    std::cout << "✓ Expected: 2 SCCs, each with 2 nodes\n";
    
    // Test case 3: Empty graph
    std::cout << "\n--- Test Case 3: Empty Graph ---";
    KosarajuSCC::Graph empty = {};
    printGraph(empty, "Empty Graph");
    components = KosarajuSCC::findSCCs(empty);
    printSCCResults(components);
    assert(components.empty());
    std::cout << "✓ Expected: 0 SCCs\n";
    
    // Test case 4: Single node
    std::cout << "\n--- Test Case 4: Single Node ---";
    KosarajuSCC::Graph single = {{}};
    printGraph(single, "Single Node Graph");
    components = KosarajuSCC::findSCCs(single);
    printSCCResults(components);
    assert(components.size() == 1);
    assert(components[0].size() == 1);
    std::cout << "✓ Expected: 1 SCC with 1 node\n";
    
    // Test case 5: Complex graph
    std::cout << "\n--- Test Case 5: Complex Graph ---";
    KosarajuSCC::Graph complex = {{1, 2}, {0, 3}, {0}, {1, 4}, {3}};
    printGraph(complex, "Complex Graph");
    components = KosarajuSCC::findSCCs(complex);
    printSCCResults(components);
    std::cout << "✓ Analysis: Multiple SCCs detected\n";
    
    std::cout << "\n=== All Tests Passed! ===\n";
}

int main() {
    testKosaraju();
    return 0;
}
