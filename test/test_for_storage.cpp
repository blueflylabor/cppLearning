// 文件名：test_storage_duration_scope_linkage.cpp
// 目的：演示第9章 存储持续性、作用域、链接性 的三种主要方式
// 使用普通 main() + cout 验证，不依赖任何测试框架

#include <iostream>
#include <string>

// ────────────────────────────────────────────────
// 1. 全局变量（文件作用域 + 外部链接）
//    - 存储持续性：静态（程序开始到结束）
//    - 作用域：整个文件可见
//    - 链接性：外部链接（其他 .cpp 可以 extern 访问）
int global_counter = 0;

// ────────────────────────────────────────────────
// 2. 内部链接的全局变量（文件作用域 + 内部链接）
//    - 只能在本文件使用，其他文件看不到同名变量
static int file_private_counter = 0;

// ────────────────────────────────────────────────
// 3. 函数：展示函数内 static 局部变量
//    - 存储持续性：静态（只初始化一次，函数结束不销毁）
//    - 作用域：块作用域（只在函数内可见）
//    - 链接性：无链接（完全本地）
void count_calls() {
    static int local_static_count = 0;  // 只初始化一次，记住上一次的值

    local_static_count++;
    global_counter++;
    file_private_counter++;

    std::cout << "第 " << local_static_count << " 次调用本函数\n";
    std::cout << "  global_counter     = " << global_counter << "\n";
    std::cout << "  file_private_counter = " << file_private_counter << "\n";
}

// ────────────────────────────────────────────────
// 4. 另一个函数：证明不同函数的 static 局部变量是独立的
void another_function() {
    static int another_static = 0;
    another_static++;

    std::cout << "another_function 调用次数: " << another_static << "\n";
}

// ────────────────────────────────────────────────
// 5. 动态存储示例（new/delete）
//    - 存储持续性：动态（程序员控制）
//    - 作用域：块作用域（指针变量本身）
//    - 链接性：无链接
void dynamic_demo() {
    int* dynamic_ptr = new int(100);  // 堆上分配

    std::cout << "动态分配的值: " << *dynamic_ptr << "\n";

    *dynamic_ptr = 200;
    std::cout << "修改后: " << *dynamic_ptr << "\n";

    delete dynamic_ptr;               // 必须释放
    dynamic_ptr = nullptr;            // 好习惯，避免野指针
}

// ────────────────────────────────────────────────
// main() 作为测试入口
int main() {
    std::cout << "=== 测试开始：存储持续性、作用域、链接性 ===\n\n";

    // 测试1：多次调用同一函数，观察 static 局部变量是否记住值
    std::cout << "测试1：函数内 static 局部变量\n";
    count_calls();   // 第1次
    count_calls();   // 第2次
    count_calls();   // 第3次
    std::cout << "\n";

    // 测试2：另一个函数的 static 独立计数
    std::cout << "测试2：不同函数的 static 局部变量是独立的\n";
    another_function();  // 1
    another_function();  // 2
    count_calls();       // 仍然是第4次（与上面不冲突）
    std::cout << "\n";

    // 测试3：全局变量 vs static 全局变量
    std::cout << "测试3：全局变量对比\n";
    std::cout << "global_counter     (外部链接) = " << global_counter << "\n";
    std::cout << "file_private_counter (内部链接) = " << file_private_counter << "\n";
    std::cout << "\n";

    // 测试4：动态存储（堆）
    std::cout << "测试4：动态存储 new/delete\n";
    dynamic_demo();
    // 注意：这里结束后，堆内存已释放，不会泄漏

    std::cout << "\n=== 所有测试完成 ===\n";
    std::cout << "OK" << std::endl;
    return 0;
}