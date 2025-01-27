#include <iostream>
#include <memory>

struct Student {
    std::string _id;
    std::string _name;
    ~Student() { std::cout << "Student::~Student" << std::endl; }
};

class SmartPtr {
    Student* _student{nullptr};

public:
    SmartPtr() = default;

    explicit SmartPtr(Student* student) : _student(student) {
    }

    SmartPtr(SmartPtr&& other) {
        _student = other._student;
        other._student = nullptr;
    }

    ~SmartPtr() {
        if (_student) std::cout << "Student deleted" << std::endl;
        delete _student;
    }

    static SmartPtr make_smartptr() {
        std::cout << "allocating new student" << std::endl;
        return SmartPtr(new Student());
    }

    Student* get() { return _student; }
    Student* operator->() { return get(); }
    bool operator==(const Student* student) const { return _student == student; }
};

int main() {
    auto print = [](auto& desc, auto& s) {
        std::cout << desc << s->_name << " (" << s->_id << ")" << std::endl;
    };
    {
        // using regular pointers
        auto s = new Student();
        s->_id = "W111222";
        s->_name = "john";
        print("OLD PTR: ", s);
        // don't forget!
        delete s;
    }
    std::cout << "------------------" << std::endl;
    {
        // using custom smart pointer
        auto sp1 = SmartPtr::make_smartptr();
        sp1->_id = "W222333";
        sp1->_name = "jane";
        print("ORIGINAL: ", sp1);

        // borrow a reference to the data
        auto student = sp1.get();
        print("REFERENCED: ", student);

        // give ownership to another variable
        auto sp2 = std::move(sp1);
        print("MOVED: ", sp2);

        auto s = (sp1 == nullptr ? "EMPTY" : sp1->_name + "(" + sp1->_id + ")");
        std::cout << "ILLEGAL: " << s << std::endl;
    }
    std::cout << "------------------" << std::endl;
    {
        // STL version
        auto up1 = std::make_unique<Student>();
        up1->_id = "W333444";
        up1->_name = "jill";
        print("UNIQUE: ", up1);

        // reference the data
        auto student = up1.get();
        print("REFERENCED: ", student);

        // move ownership
        auto up2 = std::move(up1);
        print("MOVED: ", up2);

        auto s = (up1 == nullptr ? "EMPTY" : up1->_name + "(" + up1->_id + ")");
        std::cout << "ILLEGAL: " << s << std::endl;
    }


    return 0;
}
