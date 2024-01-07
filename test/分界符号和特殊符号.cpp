#include <iostream>

using namespace std;

int main() {
    int num1 = 5;
    int num2 = 10;

    // If statement with comparison operators
    if (num1 != num2) {
        cout << "num1 is not equal to num2." << endl;
    }
    else {
        cout << "num1 is equal to num2." << endl;
    }

    // Block of code enclosed in curly braces
    {
        int x = 20;
        int y = 30;
        int result = x + y;
        cout << "Result inside the block: " << result << endl;
    }

    // Array declaration and usage with square brackets
    int numbers[3] = { 1, 2, 3 };
    cout << "First element of the array: " << numbers[0] << endl;

    // Function call with parentheses
    cout << "Hello, World!" << endl;

    // Comma operator in a single statement
    int sum = (num1 + num2, num1 - num2, num1 * num2); // Only the last value is assigned to 'sum'
    cout << "Sum: " << sum << endl;

    // Comma operator in a for loop
    for (int i = 0, j = 10; i < 5; i++, j -= 2) {
        cout << "i: " << i << ", j: " << j << endl;
    }

    // Semicolon as a statement terminator
    cout << "This is the end of the program." << endl;

    return 0;
}
