#include <iomanip>
#include <iostream>
#include <memory>

class BST {
    struct Node;

    using NodePtr = std::unique_ptr<Node>;

    struct Node {
        int _data {-1};
        NodePtr _left {nullptr};
        NodePtr _right {nullptr};
    };

    NodePtr _root {nullptr};

public:
    void insert(const int num) {
        insert(num, _root);
    }

    void insert(const int num, NodePtr& node) {
        if (node == nullptr) {
            // insert node at bottom of tree
            node = std::make_unique<Node>(num);
        } else if (num < node->_data) {
            // insert to the left of the root node
            insert(num, node->_left);
        } else if (num > node->_data) {
            // insert to the right of the root node
            insert(num, node->_right);
        }
    }

    void print_tree(std::ostream& output, const NodePtr& node, const int indent) {
        if (node != nullptr) {
            print_tree(output, node->_right, indent + 8);
            output << std::setw(indent) << node->_data << std::endl;
            print_tree(output, node->_left, indent + 8);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, BST& tree);
};

std::ostream& operator<<(std::ostream& os, BST& tree) {
    tree.print_tree(os, tree._root, 0);
    return os;
}

int main() {
    BST bst;

    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);

    // test 1
    std::cout << "Test 1: add nodes to search tree" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    std::cout << bst << std::endl;

    return 0;
}
