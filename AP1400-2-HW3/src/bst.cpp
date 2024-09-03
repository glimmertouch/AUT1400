#include "bst.h"
#include <queue>
#include <iomanip>

#include <fstream>

using std::queue;
BST::Node*& BST::get_root() {
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func) {
    queue<Node*> q;
    Node* root = get_root();
    if(root == nullptr) {
        return;
    }
    q.push(root);
    while(!q.empty()) {
        auto node = q.front();
        func(node);
        q.pop();
        if(node->left != nullptr) {
            q.push(node->left);
        }
        if(node->right != nullptr) {
            q.push(node->right);
        }
    }
}

size_t BST::length() {
    queue<Node*> q;
    size_t ans = 0;
    Node* root = get_root();
    if(root == nullptr) {
        return 0;
    }
    q.push(root);
    while(!q.empty()) {
        auto node = q.front();
        q.pop();
        ans++;
        if(node->left != nullptr) {
            q.push(node->left);
        }
        if(node->right != nullptr) {
            q.push(node->right);
        }
    }
    return ans;
}

bool BST::add_node(int value) {
    Node*& root = get_root();
    if (root == nullptr) {
        root = new Node(value);
        return true;
    }
    Node* cur = root;
    while(1) {
        if (cur->value > value) {
            if (cur->left != nullptr) {
                cur = cur->left;
            } else {
                cur->left = new Node(value);
                return true;
            }
        } else if(cur->value < value) {
            if (cur->right != nullptr) {
                cur = cur->right;
            } else {
                cur->right = new Node(value);
                return true;
            }            
        } else {
            std::cout << value <<" has existed" << std::endl;
            return false;
        }
    }
}

BST::Node** BST::find_node(int value) {
    Node** cur = &get_root();
    while ((*cur) != nullptr) {
        if ((*cur)->value > value) {
            cur = &((*cur)->left);
        } else if ((*cur)->value < value) {
            cur = &((*cur)->right);
        } else {
            return cur;
        }
    }
    return nullptr;
}

BST::Node** BST::find_parrent(int value) {
    Node** cur = &get_root();
    if ((*cur) == nullptr || (*cur)->value == value) {
        return nullptr;
    }
    while(1) {
        if ((*cur)->value > value) {
            if ((*cur)->left == nullptr) {
                return nullptr;
            } else if ((*cur)->left->value == value){
                return cur;
            } else {
                *cur = (*cur)->left;
            }
        } else if((*cur)->value < value) {
            if ((*cur)->right == nullptr) {
                return nullptr;
            } else if ((*cur)->right->value == value) {
                return cur;
            } else {
                *cur = (*cur)->right;
            }
        } else {
            throw std::runtime_error("should not be here");
        }
    }        
}

BST::Node** BST::find_successor(int value) {
    Node** node_ptr = find_node(value);
    if (node_ptr == nullptr || (*node_ptr)->left == nullptr) {
        return nullptr;
    }
    node_ptr = &((*node_ptr)->left);
    while ((*node_ptr)->right != nullptr) {
        node_ptr = &((*node_ptr)->right);
    }
    return node_ptr;
}

bool BST::delete_node(int value) {
    Node** node_ptr = find_node(value);
    if(node_ptr == nullptr) {
        return false;
    }
    Node*& node = *node_ptr;

    if ((node->left == nullptr) && (node->right == nullptr)) {
        delete node;
        node = nullptr;
    } else if ((node->left == nullptr) || (node->right == nullptr)) {
        if (node->left == nullptr) { 
            Node* temp = node->right;
            delete node;
            node = temp;
        } else {
            Node* temp = node->left;            
            delete node;
            node = temp;
        }
    } else {
        Node*& next = *find_successor(value);
        std::cout<< *next <<std::endl;
        node->value = next->value;
        if ((next->left == nullptr) && (next->right == nullptr)) {
            delete next;
            next = nullptr;
        } else if (next->left == nullptr) { 
            delete next;
            next = next->right;
        } else {
            delete next;
            next = next->left;
        }        

    }
    return true;
}

std::ostream &operator<<(std::ostream &out, const BST::Node &node)
{
    out << std::setw(10) << &node << "  => value:" << std::setw(3) << node.value 
            << "  left:" << std::setw(10) << node.left
            << "  right:" << std::setw(10) << node.right << std::endl; 
    return out;
}

std::ostream &operator<<(std::ostream &out, BST &bst)
{
    out << "********************************************************************************" << std::endl;
    bst.bfs([&out](BST::Node* node) {
        out << std::setw(10) << node <<"  => value:" << std::setw(3) << node->value 
                    << "  left:" << std::setw(10) << node->left
                    << "  right:" << std::setw(10) << node->right << std::endl;
    });
    out << "binary search tree size: " << bst.length() << std::endl;
    out << "********************************************************************************" << std::endl;
    return out;
}

BST& BST::operator++()
{
    bfs([](Node* node) {
        node->value++;
    });
    return *this;
}

BST BST::operator++(int) {
    BST temp = *this;
    bfs([](Node* node) {
        node->value++;
    });    
    return temp;
}

BST& BST::operator=(BST &bst) {
    if (this->get_root() == bst.get_root()) {
        return *this;
    }
    clear();
    this->root = nullptr;
    bst.bfs([this](Node* node){ this->add_node(node->value); });
    return *this;
}

BST& BST::operator=(BST&& bst) noexcept {
    if (this->get_root() == bst.get_root()) {
        return *this;
    }  
    clear();
    this->root = bst.get_root();
    bst.root = nullptr;
    return *this;  
}

void BST::clear()
{
	std::vector<Node*> nodes;
	bfs([&nodes](Node*& node){nodes.push_back(node);});
	for(auto& node: nodes)
		delete node;    
}
