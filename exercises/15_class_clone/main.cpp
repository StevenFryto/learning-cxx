#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>


class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // 动态分配缓存并初始化
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(0) {}

    // 复制构造，深拷贝已计算的缓存
    DynFibonacci(DynFibonacci const &other) {
        // 分配足够空间以保存已缓存的项
        int cap = other.cached > 0 ? other.cached : 2;
        cache = new size_t[cap];
        cached = other.cached;
        for (int i = 0; i < cached; ++i) cache[i] = other.cache[i];
    }

    // 析构器，释放缓存空间
    ~DynFibonacci() { delete[] cache; }

    // 缓存优化的计算
    size_t get(int i) {
        if (cached < 2) {
            cache[0] = 0;
            cache[1] = 1;
            cached = 2;
        }
        if (i < cached) return cache[i];
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    // NOTICE: 名字相同参数也相同，但 const 修饰不同的方法是一对重载方法，可以同时存在
    //         本质上，方法是隐藏了 this 参数的函数
    //         const 修饰作用在 this 上，因此它们实际上参数不同
    size_t get(int i) const {
        if (i <= cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}
