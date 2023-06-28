#pragma once

#include <cmath>

namespace mtrn2500 {
    class Complex {
    private:
        double mReal {};
        double mImaginary {};

    public:
    Complex();
    Complex(double const& real) : mReal{real} {}; 
    Complex(double const& real, double const& imaginary) : mReal{real}, mImaginary{imaginary} {};
    Complex conjugate() const {
        return Complex(mReal, -mImaginary);
    }
    double modulus() const {
        return std::sqrt(std::pow(mReal, 2) + std::pow(mImaginary, 2));
    }
    double argument() const {
        return std::atan2(mImaginary, mReal);
    }
    ~Complex() = default;
    Complex(Complex const& z)
        : mReal{z.mReal}, mImaginary{z.mImaginary} {};

    Complex(Complex&& z)
        : mReal{std::exchange(z.mReal, 0)}, mImaginary{std::exchange(z.mImaginary, 0)} {};

    Complex& operator=(Complex const& z) {
        if (this != &z) {
            mReal = z.mReal;
            mImaginary = z.mImaginary;
        }
        return *this;
    }

    Complex& operator=(Complex&& z) {
        if (this != &z) {
            mReal = std::exchange(z.mReal, 0);
            mImaginary = std::exchange(z.mImaginary, 0);
        }
        return *this;
        
    }
    
    static Complex make_conjugate(Complex const& z) {
        return z.conjugate();
    }

    friend Complex operator+(Complex const& lhs, Complex const& rhs) {
        return Complex{lhs.mReal + rhs.mReal, lhs.mImaginary + rhs.mImaginary};
    }

    friend Complex operator-(Complex const& lhs, Complex const& rhs) {
        return Complex{lhs.mReal - rhs.mReal, lhs.mImaginary - rhs.mImaginary};
    }

    friend Complex operator*(Complex const& lhs, Complex const& rhs) {
        return Complex{lhs.mReal*rhs.mReal - lhs.mImaginary*rhs.mImaginary, lhs.mReal*rhs.mImaginary + lhs.mImaginary*rhs.mReal};
    }

    friend bool operator==(Complex const& lhs, Complex const& rhs) {
        return (lhs.mReal == rhs.mReal && lhs.mImaginary == rhs.mImaginary);
    }

    friend bool operator!=(Complex const& lhs, Complex const& rhs) {
        return !operator==(lhs, rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, Complex const& z) {
        os << z.mReal << "+" << "(" << z.mImaginary << "i)\n";
    }

    };

    




}  // namespace mtrn2500
