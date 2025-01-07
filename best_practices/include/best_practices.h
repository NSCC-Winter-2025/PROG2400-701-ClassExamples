#ifndef _BEST_PRACTICES_H
#define _BEST_PRACTICES_H

#include <iostream>

class BestPractices {

    enum class ENUMS : int { ENUM_1 = 1, ENUM_2 = 2, ENUM_3 = 3, ENUM_4 = 4, ENUM_5 = 5 };
    const std::string CONSTANT_STRING = "Constant";
    std::string _member_variable = "Member variable";

public:
    BestPractices() = default;
    virtual ~BestPractices() = default;

    void member_function();
};


#endif