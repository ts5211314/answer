#include "../exercise.h"
#include <string>
#include <type_traits> // 用于 std::is_same

int main(int argc, char **argv) {
    using namespace std::string_literals;

    auto hello = "Hello"s; // std::string
    auto world = "world";  // const char*
    
    // 检查类型
    ASSERT((std::is_same<decltype(hello), std::string>::value), "Fill in the missing type.");
    ASSERT((std::is_same<decltype(world), const char*>::value), "Fill in the missing type.");
    
    // 字符串拼接
    ASSERT(hello + ", " + world + '!' == "Hello, world!", "Fill in the missing string.");
    
    return 0;
}
