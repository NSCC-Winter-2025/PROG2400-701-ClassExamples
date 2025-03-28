#include <iomanip>
#include "binary_search_tree.h"

void BST::insert(const int num) {
    insert(num, _root);
}

void BST::insert(const int num, NodePtr& node) {
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

void BST::remove(const int num) {
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

void BST::save_array(std::span<int> array) {
    save_array(array, _root);
}

void BST::save_array(std::span<int> array, NodePtr& node) {
    static auto i = 0;

    if (node != nullptr) {
        save_array(array, node->_left);
        array[i++] = node->_data;
        save_array(array, node->_right);
    }
}


void BST::print_tree(std::ostream& output, const NodePtr& node, const int indent) {
    if (node != nullptr) {
        print_tree(output, node->_right, indent + 8);
        output << std::setw(indent) << node->_data << std::endl;
        print_tree(output, node->_left, indent + 8);
    }
}

std::ostream& operator<<(std::ostream& os, BST& tree) {
    tree.print_tree(os, tree._root, 0);
    return os;
}
