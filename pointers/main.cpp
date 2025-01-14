#include <iostream>
#include <cstdint>

typedef int* BIGNUM;

void pass_by_pointer(int* ptr) {
    std::cout << *ptr << std::endl;
}

void pass_by_reference(int& ref) {
    std::cout << ref << std::endl;
}

void pass_by_double_pointer(int** ptr) {
    std::cout << *ptr << std::endl;
    std::cout << **ptr << std::endl;
}

int main() {
    // basic integer
    auto byte = (uint8_t)0xFF;
    int word = 0x1234;
    auto dword = 0x1234'5678ul;
    auto qword = 0x1122'3344'5566'7788ull;

    std::cout << std::hex << std::showbase;
    std::cout << (int)byte << std::endl;
    std::cout << word << std::endl;
    std::cout << dword << std::endl;
    std::cout << qword << std::endl;

    // basic pointer
    auto byte_ptr = (int*)0x5ffe4f;
    auto word_ptr = (void*)0x1234;
    auto dword_ptr = (void*)0x1234'5678ul;
    auto qword_ptr = (void*)0x1122'3344'5566'7788ull;

    std::cout << byte_ptr << std::endl;
    std::cout << word_ptr << std::endl;
    std::cout << dword_ptr << std::endl;
    std::cout << qword_ptr << std::endl;

    // accessing memory via pointer
    //std::cout << (int)(*byte_ptr) << std::endl;
    pass_by_pointer((int*)&word);
    pass_by_reference(word);
    pass_by_double_pointer(&byte_ptr);

    // simple pointer manipulation

    int val = 0x1234;
    int* ptr = &val;

    // to read a pointer
    std::cout << *ptr << std::endl;

    // to modify a pointer
    *ptr = 0x1234;
    std::cout << *ptr << std::endl;

    // to obtain a memory address
    // (which is what a pointer normally contains)
    int* p = &val; // use the ampersand

    // you can get pointers to ANYTHING (except references)
    void* pv = (void*)main;

    // you can get references to anything that has a data type
    // and references are only used as parameters of functions
    // void my_func( int& ref )

    return 0;
}
