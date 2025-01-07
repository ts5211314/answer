#include "../exercise.h"
#include <cmath>

enum class DataType {
    Float,
    Double,
};

struct TaggedUnion {
    DataType type;
    union {
        float f;
        double d;
    };
};

template <typename T>
T sigmoid(T x) {
    return 1 / (1 + std::exp(-x));
}

TaggedUnion sigmoid_dyn(TaggedUnion x) {
    TaggedUnion ans{x.type};
    switch (x.type) {
        case DataType::Float:
            ans.f = sigmoid(x.f);
            break;
        case DataType::Double:
            ans.d = sigmoid(x.d);
            break;
    }
    return ans;
}

int main(int argc, char **argv) {
    TaggedUnion xf{DataType::Float};
    xf.f = 5.f;
    auto yf = sigmoid_dyn(xf);
    ASSERT(yf.type == DataType::Float, "type mismatch");
    ASSERT(yf.f == 1 / (1 + std::exp(-5.f)), "sigmoid float");

    TaggedUnion xd{DataType::Double};
    xd.d = 5.0;
    auto yd = sigmoid_dyn(xd);
    ASSERT(yd.type == DataType::Double, "type mismatch");
    ASSERT(yd.d == 1 / (1 + std::exp(-5.0)), "sigmoid double");
    return 0;
}
