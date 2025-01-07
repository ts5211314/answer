#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    std::weak_ptr<int> observer = shared;
    std::cout << "shared use_count: " << shared.use_count() << std::endl;
    std::cout << "observer use_count: " << observer.use_count() << std::endl;
    ASSERT(observer.use_count() == 4, "Initial use_count should be 3");

    ptrs[0].reset();
    std::cout << "After resetting ptrs[0], observer use_count: " << observer.use_count() << std::endl;
    ASSERT(observer.use_count() == 3, "After resetting ptrs[0], use_count should be 2");

    ptrs[1] = nullptr;
    std::cout << "After setting ptrs[1] to nullptr, observer use_count: " << observer.use_count() << std::endl;
    ASSERT(observer.use_count() == 2, "After setting ptrs[1] to nullptr, use_count should be 1");

    ptrs[2] = std::make_shared<int>(*shared);
    std::cout << "After creating new shared_ptr in ptrs[2], observer use_count: " << observer.use_count() << std::endl;
    ASSERT(observer.use_count() == 1, "After creating new shared_ptr in ptrs[2], use_count should be 2");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);
    std::cout << "After reassignment, observer use_count: " << observer.use_count() << std::endl;
    ASSERT(observer.use_count() == 3, "After reassignment, use_count should be 3");

    std::ignore = std::move(ptrs[0]);
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]);
    std::cout << "After move operations, observer use_count: " << observer.use_count() << std::endl;
    ASSERT(observer.use_count() == 2, "After move operations, use_count should be 1");


    shared = observer.lock();
    std::cout << "After locking weak_ptr, observer use_count: " << observer.use_count() << std::endl;
    ASSERT(observer.use_count() == 3, "After locking weak_ptr, use_count should be 2");


    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    std::cout << "After setting all ptrs to nullptr, observer use_count: " << observer.use_count() << std::endl;
    ASSERT(observer.use_count() == 0, "After setting all ptrs to nullptr, use_count should be 0");


    shared = observer.lock();
    std::cout << "After locking weak_ptr again, observer use_count: " << observer.use_count() << std::endl;
    ASSERT(observer.use_count() == 0, "After locking weak_ptr again, use_count should be 1");


    return 0;
}
