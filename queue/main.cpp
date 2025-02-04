#include <iostream>
#include <memory>

struct Student {
    std::string _name {"uninitialized"};
    std::string _id {"W999999"};

    ~Student() {
        std::cout << "Student (" << _name << ") destroyed." << std::endl;
    }
};

std::ostream& operator<<(std::ostream& output, const Student& student) {
    output << "Name: " << student._name << ", ID: " << student._id;
    return output;
}

class Queue {
    struct Node {
        Student _data;
        std::unique_ptr<Node> _next {nullptr};
    };

    std::unique_ptr<Node> _front {nullptr}; // will be the owner
    Node* _back {nullptr}; // will just contain a reference
    size_t _size {0};

public:
    void push(const Student& student) {
        auto node = std::make_unique<Node>(student);

        // is this the first node?
        if (_front == nullptr) {
            // yes!
            _front = std::move(node);
            _back = _front.get();
        } else {
            // no, so just add to end of the queue
            _back->_next = std::move(node);
            _back = _back->_next.get(); // _back = node;
        }
        _size++;
    }

    [[nodiscard]] Student front() const {
        return _front != nullptr ? _front->_data : Student();
    }

    [[nodiscard]] bool empty() const { return _size == 0; }
    [[nodiscard]] size_t size() const { return _size; }

    void pop() {
        _front = std::move(_front->_next);

        // was that the last node?
        if (_front == nullptr) {
            // yes! It was!
            _back = nullptr;
        }
        _size--;
    }

    friend std::ostream& operator<<(std::ostream& output, const Queue& queue);
};

std::ostream& operator<<(std::ostream& output, const Queue& queue) {
    auto node = queue._front.get();
    while (node != nullptr) {
        output << node->_data << std::endl;
        node = node->_next.get();
    }
    return output;
}

int main() {
    Queue queue;

    // test 1 - add some nodes to the queue
    std::cout << "Test 1: add nodes" << std::endl;
    std::cout << "-----------------" << std::endl;

    queue.push({"John Smith", "W111111"});
    queue.push({"Jane Doe", "W222222"});
    queue.push({"Jill Hill", "W333333"});
    queue.push({"Jack Sprat", "W444444"});
    queue.push({"Bill Hill", "W555555"});

    std::cout << queue << std::endl;

    // test 2 - view data at the front of the queue
    std::cout << "Test 2: view data at front of queue" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    std::cout << queue.front() << std::endl;

    // test 3 - remove node from queue
    std::cout << "Test 3: remove node from queue" << std::endl;
    std::cout << "------------------------------" << std::endl;

    queue.pop();

    std::cout << queue << std::endl;

    // test 4 - remove all the nodes from the queue
    std::cout << "Test 4: remove all nodes from queue" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    while (!queue.empty()) {
        queue.pop();
    }

    std::cout << queue << std::endl;

    return 0;
}
