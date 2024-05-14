#include <iostream>
#include <string>
#include <stack>

using namespace std;

// Class to represent a token in the expression
class Token {
public:
    enum Type { OPERAND, OPERATOR };
    Type type;
    string value;

    Token(Type t, const string& v) : type(t), value(v) {}
};

// Function to generate intermediate code for a boolean expression
string generateIntermediateCode(const string& expression) {
    string intermediateCode;

    stack<Token> stack;

    for (size_t i = 0; i < expression.size(); ++i) {
        if (expression[i] == ' ') {
            continue; // Ignore whitespace
        } else if (expression[i] == '(') {
            stack.push(Token(Token::OPERATOR, "("));
        } else if (expression[i] == ')') {
            while (!stack.empty() && stack.top().value != "(") {
                intermediateCode += stack.top().value + " ";
                stack.pop();
            }
            stack.pop(); // Pop the '('
        } else if (expression[i] == '&' || expression[i] == '|') {
            while (!stack.empty() && stack.top().value != "(") {
                intermediateCode += stack.top().value + " ";
                stack.pop();
            }
            stack.push(Token(Token::OPERATOR, string(1, expression[i])));
        } else {
            string operand;
            while (i < expression.size() && isalnum(expression[i])) {
                operand += expression[i];
                ++i;
            }
            --i;
            intermediateCode += operand + " ";
        }
    }

    while (!stack.empty()) {
        intermediateCode += stack.top().value + " ";
        stack.pop();
    }

    return intermediateCode;
}

int main() {
    string expression;
    cout << "Enter a boolean expression: ";
    getline(cin, expression);

    string intermediateCode = generateIntermediateCode(expression);
    cout << "Intermediate code: " << intermediateCode << endl;

    return 0;
}






Sample i/ps and o/ps

Input: (A & B) | (C & D) Output: A B & C D & |

Input: A & B | C Output: A B & C |

Input: A | (B & C) Output: A B C & |

Input: (A & B) | (C | D) Output: A B & C D | |

Input: A & B | C | D Output: A B & C | D |