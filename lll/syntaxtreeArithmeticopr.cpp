#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

struct Node {
    char value;
    Node* left;
    Node* right;
};

Node* newNode(char value) {
    Node* node = new Node;
    node->value = value;
    node->left = node->right = nullptr;
    return node;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else
        return 0;
}

string infixToPostfix(const string& expression) {
    string postfix;
    stack<char> stack;

    for (char c : expression) {
        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.empty() && stack.top() != '(') {
                postfix += stack.top();
                stack.pop();
            }
            stack.pop(); // Pop '('
        } else {
            while (!stack.empty() && precedence(stack.top()) >= precedence(c)) {
                postfix += stack.top();
                stack.pop();
            }
            stack.push(c);
        }
    }

    while (!stack.empty()) {
        postfix += stack.top();
        stack.pop();
    }

    return postfix;
}

Node* constructTree(const string& postfix) {
    stack<Node*> stack;

    for (char c : postfix) {
        if (isalnum(c)) {
            stack.push(newNode(c));
        } else {
            Node* right = stack.top();
            stack.pop();
            Node* left = stack.top();
            stack.pop();

            Node* node = newNode(c);
            node->right = right;
            node->left = left;
            stack.push(node);
        }
    }

    return stack.top();
}

int evaluate(Node* root) {
    if (!root)
        return 0;
    if (!root->left && !root->right)
        return root->value - '0';

    int leftValue = evaluate(root->left);
    int rightValue = evaluate(root->right);

    switch (root->value) {
        case '+': return leftValue + rightValue;
        case '-': return leftValue - rightValue;
        case '*': return leftValue * rightValue;
        case '/': return leftValue / rightValue;
        default: return 0;
    }
}

void printSyntaxTree(Node* root, int depth) {
    if (!root)
        return;

    const int SPACING = 4;

    printSyntaxTree(root->right, depth + 1);

    cout << string(depth * SPACING, ' ') << root->value << endl;

    printSyntaxTree(root->left, depth + 1);
}

int main() {
    string infix_expression;
    cout << "Enter the infix expression: ";
    getline(cin, infix_expression);

    string postfix_expression = infixToPostfix(infix_expression);
    cout << "Postfix expression: " << postfix_expression << endl;

    Node* root = constructTree(postfix_expression);

    cout << "Syntax tree:" << endl;
    printSyntaxTree(root, 0);

    int result = evaluate(root);
    cout << "Result: " << result << endl;

    return 0;
}








Set of Inputs:-

Input: (5*3)+4-2
Input: 3+4*2/(1-5)
Input: 2*3/(4+5)-6
Input: 9-5*2+(7/2)
Input: (3+5)/(2-1)*4
Input: 8/2+(9-3)*6
Input: 4*(6-2)+8/2
Input: (2+3)*4-8/2
Input: 7+3*2-(6/3)
Input: 1+2+3+4+5-6-7-8-9-10