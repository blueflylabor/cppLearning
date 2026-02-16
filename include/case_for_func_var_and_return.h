#ifndef CASE_FOR_FUNC_VAR_AND_RETURN_H
#define CASE_FOR_FUNC_VAR_AND_RETURN_H

#include <vector>
#include <string>
#include <utility>

class Widget {
public:
    std::string name;
    std::vector<int> data;
};

struct Container {
    std::vector<Widget> data;
};

Container some_container;

void by_value(Widget w) {
    w.name = "changed by_value";
    std::vector<int> data;
    data.push_back(1);
    w.data = data;
}

void by_const_ref(const Widget& w) {
    std::cout << w.name << std::endl;
}

void by_ref(Widget& w) {
    w.name = "changed by_ref";
    std::vector<int> data;
    data.push_back(1);
    w.data = data;
}

void by_rvalue_ref(Widget&& w) {
    some_container.data.emplace_back(std::move(w));
}

Widget& get_widget_bad() {
    Widget local{"temp"};
    return local;
}

const Widget& get_widget_const_ref_bad(int id) {
    if (id == 1) {
        static Widget cache1{"cached1"};
        return cache1;
    }
    Widget temp{"temp"};
    return temp;
}

Widget create_widget() {
    Widget w;
    w.name = "create_widget";
    w.data = {1, 2, 3};
    return w;
}

const Widget& get_widget_const() {
    static const Widget single_instance{"single_instance"};
    return single_instance;
}

std::unique_ptr<Widget> make_widget() {
    return std::make_unique<Widget>();
}

Widget make_another_widget() {
    Widget w;
    return std::move(w);
}

#endif