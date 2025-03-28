#include <iostream>
#include <memory>
#include <optional>
#include <vector>

struct Data {
    int _num {0};
    float _val {0.0f};

    ~Data() { std::cout << "Destroyed: num = " << _num << ", val = " << _val << std::endl; }
};

std::ostream& operator<<(std::ostream& os, const Data& data) {
    os << "num: " << data._num << ", val: " << data._val;
    return os;
}

class Stack {
    // struct Node {
    //     Data _data;
    //     std::unique_ptr<Node> _next {nullptr};
    // };
    //
    // std::unique_ptr<Node> _top {nullptr};
    std::vector<Data> _data;

public:
    void push(const Data& data) {
        // auto node = std::make_unique<Node>(data);
        // node->_next = std::move(_top);
        // _top = std::move(node);
        _data.push_back(data);
    }

    [[nodiscard]] std::optional<Data> top() const {
        // if (_top == nullptr) return std::nullopt;
        // return std::make_optional(_top->_data);
        if (_data.empty()) return std::nullopt;
        return _data.back();
    }

    void pop() {
        // if (_top == nullptr) return;
        // _top = std::move(_top->_next);
        _data.pop_back();
    }

    friend std::ostream& operator<<(std::ostream& os, const Stack& stack);
};

std::ostream& operator<<(std::ostream& os, const Stack& stack) {
    // auto node = stack._top.get();
    // while (node != nullptr) {
    //     os << node->_data << std::endl;
    //     node = node->_next.get();
    // }
    for (const auto& data : stack._data) {
        os << data << std::endl;
    }
    return os;
}

int main() {
    Stack stack;

    // test 1 - add some data
    std::cout << "Test 1 - add an item of data" << std::endl;
    std::cout << "----------------------------" << std::endl;

    stack.push({1, 6.67f});

    std::cout << stack << std::endl;

    // test 2 - add some more data
    std::cout << "Test 2 - add more items of data" << std::endl;
    std::cout << "-------------------------------" << std::endl;

    stack.push({2, 1.11f});
    stack.push({3, 2.22f});
    stack.push({4, 3.33f});
    stack.push({5, 4.44f});

    std::cout << stack << std::endl;

    // test 3 - get data from top of the stack
    std::cout << "Test 3 - view data on top of stack" << std::endl;
    std::cout << "----------------------------------" << std::endl;

    if (stack.top().has_value()) {
        std::cout << *stack.top() << std::endl;
    }
    std::cout << stack.top().or_else([]() {
        return std::optional<Data>({-1, -1.0f});
    }).value() << std::endl;

    // test 4 - remove data from top of the stack
    std::cout << "Test 4 - remove data from stack" << std::endl;
    std::cout << "-------------------------------" << std::endl;

    stack.pop();

    std::cout << stack << std::endl;

    // test 5 - remove all data from the stack
    std::cout << "Test 4 - remove all data from stack" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    while (stack.top().has_value()) {
        stack.pop();
        std::cout << stack << std::endl;
    }

    return 0;
}
