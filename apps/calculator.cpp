#include "../edora.h"

#include <iostream>
#include <iomanip>

using namespace std;

void calculatorApp()
{
    cout << "\n";
    cout << "============================================\n";
    cout << "               EDORA CALCULATOR\n";
    cout << "============================================\n";
    cout << "Operations: +, -, *, /\n";
    cout << "Type 'exit' to leave.\n";

    while (true) {
        cout << "Expression: ";
        string expr;
        getline(cin, expr);

        if (expr == "exit" || expr == "EXIT") {
            cout << "Calculator closed.\n";
            return;
        }

        size_t pos = expr.find_first_of("+-*/");
        if (pos == string::npos) {
            cout << "Invalid expression.\n";
            continue;
        }

        double a = stod(expr.substr(0, pos));
        char op = expr[pos];
        double b = stod(expr.substr(pos + 1));

        double result = 0.0;
        switch (op) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/':
                if (b == 0.0) {
                    cout << "Division by zero is not allowed.\n";
                    continue;
                }
                result = a / b;
                break;
            default:
                cout << "Unsupported operator.\n";
                continue;
        }

        cout << fixed << setprecision(2) << "Result: " << result << "\n";
    }
}
