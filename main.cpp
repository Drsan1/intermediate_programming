#include <iostream>

struct Vector5 {
    double x;
    double y;
    double z;
    double w;
    double v;
};

Vector5 sum(Vector5 a, Vector5 b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w, a.v + b.v};
}

Vector5 diff(Vector5 a, Vector5 b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w, a.v - b.v};
}

Vector5 hamming(Vector5 a, Vector5 b) {
    double x_sum = abs(a.x - b.x);
    double y_sum = abs(a.y - b.y);
    double z_sum = abs(a.z - b.z);
    double w_sum = abs(a.w - b.w);
    double v_sum = abs(a.v - b.v);

    return {x_sum + y_sum + z_sum + w_sum + v_sum};
}

void  fibonacci(int& a, int& b) {
    int c = a + b;
    a = b;
    b = c;
}

int main() {
    // int a = 1;
    // int b = 1;
    // for (int i = 0; i < 20; i++) {
    //     std::cout << a << "," << b << std::endl;
    //     fibonacci(a, b);
    // }


    Vector5 vec1(5, 6, 7, 1, 2);
    Vector5 vec2(3, 4, 5, 6, 1);
    Vector5 _sum = sum(vec1, vec2);
    Vector5 _diff = diff(vec1, vec2);
    Vector5 _hamming = hamming(vec1, vec2);


    std::cout << "vec1: (" << vec1.x << "," << vec1.y << "," << vec1.z << "," << vec1.w << "," << vec1.v << ")" << std::endl;
    std::cout << "vec2: (" << vec2.x << "," << vec2.y << "," << vec2.z << "," << vec2.w << "," << vec2.v << ")" << std::endl;
    std::cout << std::endl;
    std::cout<<  "Sum: (" << _sum.x << "," << _sum.y << "," << _sum.z << "," << _sum.w << "," << _sum.v << ")" << std::endl;
    std::cout<<  "Diff: (" << _diff.x << "," << _diff.y << "," << _diff.z << "," << _diff.w << "," << _diff.v << ")" << std::endl;
    std::cout << "Hamming: " << _hamming.x << std::endl;
}