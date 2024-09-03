#ifndef BST_H
#define BST_H
#include <functional>
#include <iostream>

class BST
{
public:
    class Node {
    public:
        Node(int value, Node* left = nullptr, Node* right = nullptr) : 
            value(value), left(left), right(right) {};
        Node() : value(0), left(nullptr), right(nullptr) {};
        Node(const Node& node) : value(node.value), left(node.left),
                right(node.right) {};

        int value;
        Node* left;
        Node* right;

        auto operator<=>(int value) {
            return this->value <=> value;
        }

        bool operator==(int value) {
            return this->value == value;
        }

        friend std::ostream& operator<<(std::ostream& out, const Node& node);
    };
    BST() : root(nullptr) {};
    BST(BST& bst) : root(nullptr) {
        bst.bfs([this](Node*& node){this->add_node(node->value);});
    };
    BST(BST&& bst) noexcept : root(bst.root) {
        bst.root = nullptr;
    }
    template<typename... Args>
    BST(Args... args) {
        root = nullptr;
        add_nodes(args...);
    }

    ~BST()
    {
	    clear();
    }

    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);

    friend std::ostream& operator<<(std::ostream& out, BST& bst);
    BST& operator++();
    BST operator++(int);

    BST& operator=(BST& bst);
    BST& operator=(BST&& bst) noexcept;

    void add_nodes() {    };
    template<typename T, typename... Args>
    void add_nodes(T first, Args... args) {
        add_node(first);
        add_nodes(args...);
    };

    void clear();


private:
    Node* root;
};







#endif //BST_H