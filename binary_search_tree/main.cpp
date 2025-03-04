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
        ~Node() { std::cout << "deleted: " << _data << std::endl; }
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

    void remove(const int num) {
        auto node = _root.get();
        auto parent = static_cast<Node*>(nullptr);

        // search for node to delete
        while (node != nullptr) {
            if (num < node->_data) {
                // look on the left branch
                parent = node;
                node = node->_left.get();
            } else if (num > node->_data) {
                // look on the right branch
                parent = node;
                node = node->_right.get();
            } else {
                // found it!
                break;
            }
        }

        // did I find the node I'm looking for?
        if (node == nullptr) return; // no, I didn't

        // disconnect node from parent

        // does the node have two children?
        if (node->_left != nullptr && node->_right != nullptr) {
            // yes it does!

            // so, find a successor to delete

            // start on the left subtree
            auto successor = node->_left.get();

            // go as far right as possible
            parent = node;
            while (successor->_right != nullptr) {
                parent = successor;
                successor = successor->_right.get();
            }

            // swap data between node and successor
            node->_data = successor->_data;
            // the node to delete is now the successor
            node = successor;
        }

        // does the node have children on the left or right side
        auto subtree = std::move(node->_left);

        // if there is no left children, assume there are some on the right
        if (subtree == nullptr) {
            subtree = std::move(node->_right);
        }

        if (parent == nullptr) {
            // we are deleting the root node
            _root = std::move(subtree);
        } else if (node == parent->_left.get()) {
            // the node to delete is on the left side of parent
            parent->_left = std::move(subtree);
        } else if (node == parent->_right.get()) {
            // the node to delete is on the right side of parent
            parent->_right = std::move(subtree);
        }

        // node will be automatically deleted once the function exits
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

    // test 2
    std::cout << "Test 2: delete a node with no children" << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    bst.remove(2);

    std::cout << bst << std::endl;

    // test 3
    std::cout << "Test 3: delete a node with one child" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    bst.remove(3);

    std::cout << bst << std::endl;

    // test 4
    std::cout << "Test 4: delete a node with two children" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    bst.remove(7);

    std::cout << bst << std::endl;

    // test 5
    std::cout << "Test 5: delete the root node" << std::endl;
    std::cout << "----------------------------" << std::endl;

    bst.remove(5);

    std::cout << bst << std::endl;

    // test 6
    std::cout << "Test 6: delete remaining nodes" << std::endl;
    std::cout << "------------------------------" << std::endl;

    bst.remove(4);
    bst.remove(6);
    bst.remove(8);

    std::cout << bst << std::endl;

    return 0;
}
