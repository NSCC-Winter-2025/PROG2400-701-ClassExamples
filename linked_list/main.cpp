#include <iostream>

class LinkedList {
    struct Node {
        int _data{-1};
        Node* _next{nullptr};
    };

    Node* _start{nullptr};

public:
    virtual ~LinkedList() {
        auto node = _start;

        while (node != nullptr) {
            auto temp = node;
            std::cout << "Deleting: " << temp->_data << std::endl;
            node = node->_next;
            delete temp;
        }
    }

    void add(int value) {
        auto new_node = new Node({value});

        // is this the first node?
        if (_start == nullptr) {
            // yes! we are the first node!
            _start = new_node;
        }
        else {
            // no, we have to find the end...
            auto prev = (Node*)nullptr;
            auto node = _start;

            // now move the pointers through the chain
            while (node != nullptr) {
                prev = node;
                node = node->_next;
            }

            // did we find the end of the chain?
            if (prev != nullptr) {
                // yes! attach new node to the end of the chain
                prev->_next = new_node;
            }
        }
    }

    void remove(int value) {
        auto prev = (Node*)nullptr;
        auto node = _start;

        // find the node to delete
        while (node != nullptr) {
            // find the node based on its value
            if (node->_data == value) {
                // we found the node we want to delete
                break;
            }
            prev = node;
            node = node->_next;
        }

        // if the node was found, delete it
        if (node != nullptr) {
            // are we deleting the first node?
            if (prev == nullptr) {
                // yes!
                _start = node->_next;
            }
            else {
                // no, just another node
                prev->_next = node->_next;
            }

            delete node;
        }
    }

    friend std::ostream& operator<<(std::ostream& output, const LinkedList& list);
};

std::ostream& operator<<(std::ostream& output, const LinkedList& list) {
    auto node = list._start;

    while (node != nullptr) {
        output << node->_data << " ";
        node = node->_next;
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
    }

    std::cout << "All the nodes should now be deleted." << std::endl;

    return 0;
}
