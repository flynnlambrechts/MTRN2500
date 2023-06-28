#include "SmallMatrix.hpp"
#include <iostream>

double dot(std::vector<double *> lhs, std::vector<double *> rhs) {
    double result {0};

    for (int i {0}; i < lhs.size(); i++) {
        result += (*lhs.at(i))*(*rhs.at(i));
    }
    return result;
}

void test_constructors() {
    auto m1 = mtrn2500::SmallMatrix();
    std::cout << "M1: \n";
    std::cout << m1 << std::endl;

    auto m2 = mtrn2500::SmallMatrix(1, 1);
    std::cout << "M2: \n";
    std::cout << m2 << std::endl;

    auto m3 = mtrn2500::SmallMatrix(2, 2, 69);
    std::cout << "M3: \n";
    std::cout << m3 << std::endl;

    auto m3_1 = mtrn2500::SmallMatrix(12, 12, 69);
    std::cout << "M3_1: \n";
    std::cout << m3_1 << std::endl;
    auto m4 = mtrn2500::SmallMatrix({
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
        });
    std::cout << "M4: \n";
    std::cout << m4 << std::endl;


    auto m5 = mtrn2500::SmallMatrix({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    });

    auto m6 = std::move(m5);
    std::cout << m1 << std::endl;
}

void test_dot() {
    auto m3 = mtrn2500::SmallMatrix(2, 2, 69);
    std::cout << "M3: \n";
    std::cout << dot(m3.row(1), m3.row(0)) << std::endl;
}

void test_times() {
    auto m1 = mtrn2500::SmallMatrix();
    auto m2 = mtrn2500::SmallMatrix();
    auto e = mtrn2500::SmallMatrix();

    m1 = mtrn2500::SmallMatrix(12, 12, 3);
    m2 = mtrn2500::SmallMatrix(12, 12, 2);

    std::cout << m1 * m2 << std::endl
              << std::endl;

    m1 = mtrn2500::SmallMatrix(12, 11, 3);
    m2 = mtrn2500::SmallMatrix(11, 12, 2);
    e = mtrn2500::SmallMatrix(11, 11, 72);

    std::cout << m1 * m2 << std::endl
              << std::endl
              << e << std::endl;

    m1 = mtrn2500::SmallMatrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    m2 = mtrn2500::SmallMatrix({{2, 3}, {4, 5}, {6, 7}});
    e = mtrn2500::SmallMatrix({{28, 34}, {64, 79}, {100, 124}});

    std::cout << m1 * m2 << std::endl
              << std::endl
              << e << std::endl;

    m1 = mtrn2500::SmallMatrix(3, 0);
    m2 = mtrn2500::SmallMatrix(0, 3);
    e = mtrn2500::SmallMatrix(3, 3);
    // std::cout << m1 << std::endl;
    // std::cout << m2 << std::endl;
    std::cout << e << std::endl;
    std::cout << m1 * m2 << std::endl;
}

void test_scalar_times() {
    auto m1 = mtrn2500::SmallMatrix();
    m1 = mtrn2500::SmallMatrix(10, 10, 3);

    std::cout << m1 << std::endl;
    std::cout << 2*m1 << std::endl;
    std::cout << m1*2 << std::endl;

    m1 *= 5;
   std::cout << m1 << std::endl;
}

void test_resize() {
    auto m1 = mtrn2500::SmallMatrix();
    auto m2 = mtrn2500::SmallMatrix();
    auto m3 = mtrn2500::SmallMatrix();

    m1 = mtrn2500::SmallMatrix(10, 10, 3);

    std::cout << m1 << std::endl;
    m1.resize(5, 5);
    std::cout << m1 << std::endl;
    m1.resize(7, 7);
    std::cout << m1 << std::endl;
    m1.resize(13, 13);
    std::cout << m1 << std::endl;


    m2 = mtrn2500::SmallMatrix(20, 20, 3);
    std::cout << m2 << std::endl;
    m2.resize(15, 15);
    std::cout << m2 << std::endl;
    m2.resize(17, 17);
    std::cout << m2 << std::endl;


    m3 = mtrn2500::SmallMatrix(3, 3, 1);
    std::cout << m3 << std::endl;
    m3.resize(15, 15);
    std::cout << m3 << std::endl;
    std::cout << m3.isSmall() << std::endl;

}

void test_transpose() {
    auto m = mtrn2500::SmallMatrix();
    m = {
        {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
        {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
        {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
        {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
        {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
        {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
        {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
        {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
        {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
        {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
        {0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2, 13.2, 14.2, 15.2},
    };
    std::cout << mtrn2500::transpose(m) << std::endl;
}

void test_insert_row() {
    auto m = mtrn2500::SmallMatrix();
    m = mtrn2500::SmallMatrix(12, 12, 1);
    std::cout << m << std::endl;
    m.insertRow(4, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2});
    std::cout << m << std::endl;

    m = mtrn2500::SmallMatrix(3, 3, 1);
    std::cout << m << std::endl;
    m.insertRow(2, {0, 0, 0});
    std::cout << m << std::endl;


}

void test_destroy_after_move() {
    auto m1 = mtrn2500::SmallMatrix(13, 13, 1);
    mtrn2500::SmallMatrix m2 {std::move(m1)};
    // m1 = mtrn2500::SmallMatrix(13, 13, 1);

    std::cout << m1 << std::endl;
    // m2 = std::move(m1);s
    std::cout << m2 << std::endl;
    // std::cout << m1 << std::endl;
    
    // double d1 = 5;
    // std::cout << d1 << std::endl;
    // double d2 = std::exchange(d1, 0);
    // std::cout << d2 << std::endl;
    // std::cout << d1 << std::endl;
}


int main() {
    // test_constructors();
    // test_times();
    // test_scalar_times();
    // test_resize();
    // test_transpose();
    // test_insert_row();
    test_destroy_after_move();
    return 0;


}