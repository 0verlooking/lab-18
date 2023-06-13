#include <iostream>
#include <vector>
#include <memory>
#include <map>

class Node {
public:
    std::string name;

    Node(const std::string& n) : name(n) {}

    // Додавання інформації про суміжні вершини необхідне, якщо граф неорієнтований
    std::vector<std::shared_ptr<Node>> adjacents;
};

class Graph {
public:
    std::map<std::string, std::shared_ptr<Node>> nodes;

    std::shared_ptr<Node> addNode(const std::string& name) {
        auto node = std::make_shared<Node>(name);
        nodes[name] = node;
        return node;
    }

    void addEdge(const std::string& name1, const std::string& name2) {
        auto node1 = nodes[name1];
        auto node2 = nodes[name2];
        node1->adjacents.push_back(node2);
        node2->adjacents.push_back(node1); // Цей рядок необхідний, якщо граф неорієнтований
    }

    void printGraph() {
        for (const auto& pair : nodes) {
            std::cout << pair.first << " is connected to: ";
            for (const auto& adjacent : pair.second->adjacents) {
                std::cout << adjacent->name << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    Graph graph;
    graph.addNode("Node1");
    graph.addNode("Node2");
    graph.addNode("Node3");
    graph.addEdge("Node1", "Node2");
    graph.addEdge("Node2", "Node3");

    graph.printGraph(); // Виводить список зв'язків між вузлами графа

    return 0;
}