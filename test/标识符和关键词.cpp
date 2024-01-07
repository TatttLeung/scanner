#include <iostream>

using namespace std;

int main() {
    int x = 5;
    int y = 10;
    int abc123 = 15;
    int xy = x + y;
    int _xy = x - y;
    int xy_xy23 = xy * _xy;

    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "abc123: " << abc123 << endl;
    cout << "xy: " << xy << endl;
    cout << "_xy: " << _xy << endl;
    cout << "xy_xy23: " << xy_xy23 << endl;

    if (x < y) {
        cout << "x is less than y." << endl;
    }
    else {
        cout << "x is not less than y." << endl;
    }

    int i = 0;
    while (i < 5) {
        cout << "Iteration " << i + 1 << endl;
        i++;
    }

    for (int j = 0; j < 5; j++) {
        if (j == 3) {
            break;
        }
        if (j == 4) {
            continue;
        }
        cout << "Inside the for loop, j: " << j << endl;
    }

    do {
        cout << "This will be executed at least once." << endl;
    } while (false);

    switch (x) {
    case 5:
        cout << "x is 5." << endl;
        break;
    case 10:
        cout << "x is 10." << endl;
        break;
    default:
        cout << "x is neither 5 nor 10." << endl;
        break;
    }

    return 0;
}
