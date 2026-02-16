//
// Created by Jeff Whynot on 2026/1/31.
//

#include <iostream>
#include "case_for_func_var_and_return.h"
#include <cassert>

int main() {
    Widget w1, w2, w3;
    w1.name = "test1";
    w2.name = "test2";
    w3.name = "test3";

    by_value(w1);
    std::cout << w1.name << std::endl;
    by_const_ref(w2);
    by_ref(w3);
    by_rvalue_ref(std::move(Widget()));

    assert(w3.name == "changed by_ref");
    assert(some_container.data.size() == 1);
    std::cout << "OK" << std::endl;
    return 0;
}