#include <iostream>
#include <algorithm>
#include <memory>

class LinkedList {
    struct Node {
        int _data {-1};
        std::unique_ptr<Node> _next {nullptr};

        ~Node() {
            std::cout << "deleting: " << _data << std::endl;
        }
    };

    std::unique_ptr<Node> _start {nullptr};

public:
    class iterator {
        Node* _node {nullptr};
        int _index {-1};

    public:
        explicit iterator(Node* node) : _node(node) {
        }

        int operator*() const { return _node->_data; }

        iterator& operator++() {
            _node = _node->_next.get();
            _index++;
            return *this;
        }

        bool operator!=(const iterator it) const { return _node != it._node; }
    };

    [[nodiscard]] iterator begin() const { return iterator(_start.get()); }
    [[nodiscard]] iterator end() { return iterator(nullptr); }

    void add(int value) {
        //auto new_node = new Node({value});
        auto new_node = std::make_unique<Node>(value);

        // is this the first node?
        if (_start == nullptr) {
            // yes! we are the first node!
            _start = std::move(new_node);
        } else {
            // no, we have to find the end...
            auto prev = static_cast<Node*>(nullptr);
            auto node = _start.get();

            // now move the pointers through the chain
            while (node != nullptr) {
                prev = node;
                node = node->_next.get();
            }

            // did we find the end of the chain?
            if (prev != nullptr) {
                // yes! attach new node to the end of the chain
                prev->_next = std::move(new_node);
            }
        }
    }

    ///
    /// @param value the data to be inserted
    /// @param after_value the value of the node to insert before
    void insert(int value, const int after_value) {
        auto new_node = std::make_unique<Node>(value);

        auto node = _start.get();
        auto prev = static_cast<Node*>(nullptr);

        // find the node to insert before
        while (node != nullptr) {
            // look for the desired node
            if (node->_data == after_value) {
                // found the node!
                break;
            }
            prev = node;
            node = node->_next.get();
        }

        // did we find the node we were looking for?
        if (node != nullptr) {
            // is this the first node?
            if (prev == nullptr) {
                // yes, inserting at the start
                new_node->_next = std::move(_start);
                _start = std::move(new_node);
            } else {
                // no, inserting in the middle
                new_node->_next = std::move(prev->_next);
                prev->_next = std::move(new_node);
            }
        }
    }

    void remove(const int value) {
        auto prev = static_cast<Node*>(nullptr);
        auto node = _start.get();

        // find the node to delete
        while (node != nullptr) {
            // find the node based on its value
            if (node->_data == value) {
                // we found the node we want to delete
                break;
            }
            prev = node;
            node = node->_next.get();
        }

        // if the node was found, delete it
        if (node != nullptr) {
            // are we deleting the first node?
            if (prev == nullptr) {
                // yes!
                _start = std::move(node->_next);
            } else {
                // no, just another node
                prev->_next = std::move(node->_next);
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& output, const LinkedList& list);
};

std::ostream& operator<<(std::ostream& output, const LinkedList& list) {
    auto node = list._start.get();

    while (node != nullptr) {
        output << node->_data << " ";
        node = node->_next.get();
    }
    return output;
}

int main() {
    {
        LinkedList list;

        list.add(1);
        list.add(2);
        list.add(3);
        list.add(4);
        list.add(5);

        std::cout << "Test 1: add some data" << std::endl;
        std::cout << "---------------------" << std::endl;

        std::cout << list << std::endl;

        std::cout << "Test 2: delete a node" << std::endl;
        std::cout << "---------------------" << std::endl;

        // delete the node that contains the value 5
        list.remove(5);

        std::cout << list << std::endl;

        std::cout << "Test 3: delete a node in the middle" << std::endl;
        std::cout << "-----------------------------------" << std::endl;

        // delete the node that contains the value 3
        list.remove(3);

        std::cout << list << std::endl;

        std::cout << "Test 4: delete the first node" << std::endl;
        std::cout << "-----------------------------" << std::endl;

        // delete the node that contains the value 1
        list.remove(1);

        std::cout << list << std::endl;

        std::cout << "Test 5: insert a node in the middle" << std::endl;
        std::cout << "-----------------------------------" << std::endl;

        // insert the value 99 before a node that contains the value 4
        list.insert(99, 4);

        std::cout << list << std::endl;

        std::cout << "Test 6: insert a node at the start" << std::endl;
        std::cout << "----------------------------------" << std::endl;

        // insert the value 0 before a node that contains the value 2
        list.insert(0, 2);

        std::cout << list << std::endl;

        std::cout << "Test 7: use an iterator to list the nodes" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;

        for (auto i = list.begin(); i != list.end(); ++i) {
            std::cout << *i << " ";
        }
        std::cout << std::endl;

        std::cout << "Test 8: use a for..each to list the nodes" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;

        std::for_each(list.begin(), list.end(), [](int n) {
            std::cout << n << " ";
        });
        std::cout << std::endl;

        std::cout << "Test 9: use the ranged for loop to list the nodes" << std::endl;
        std::cout << "-------------------------------------------------" << std::endl;

        for (const auto n : list) {
            std::cout << n << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "All the nodes should now be deleted." << std::endl;

    return 0;
}
