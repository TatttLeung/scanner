#include <iostream>

using namespace std;

int main() {
    int a = 10;
    int b = 5;

    // Arithmetic operators
    int sum = a + b;
    int difference = a - b;
    int product = a * b;
    int division = a / b;
    int modulus = a % b;

    // Compound assignment operators
    sum += 5;
    difference -= 2;
    product *= 3;
    division /= 2;

    // Increment and decrement operators
    int x = 7;
    x++;
    int y = 10;
    y--;

    // Relational operators
    bool isEqual = (a == b);
    bool isNotEqual = (a != b);
    bool isLess = (a < b);
    bool isLessOrEqual = (a <= b);
    bool isGreater = (a > b);
    bool isGreaterOrEqual = (a >= b);

    // Logical operators
    bool logicalAnd = (true && false);
    bool logicalOr = (true || false);
    bool logicalNot = !true;

    // Conditional operator (ternary)
    int max = (a > b) ? a : b;

    // Bitwise operators (not commonly used)
    int bitwiseAnd = a & b;
    int bitwiseOr = a | b;
    int bitwiseXor = a ^ b;
    int bitwiseNot = ~a;

    // Shift operators (left and right shift)
    int leftShift = a << 2;
    int rightShift = a >> 1;

    // Commenting examples
    // This is a single-line comment

    /*
    This is a
    multi-line comment
    */

    // Division by zero (causes a runtime error)
    // int result = a / 0;

    return 0;
}