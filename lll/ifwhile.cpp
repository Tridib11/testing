#include <iostream>
#include <string>

using namespace std;

// Example C++ function containing if and while constructs
void exampleFunction(int x, int y) {
    int a = 0;
    if (x > y) {
        while (a < x) {
            cout << "a is less than x" << endl;
            a++;
        }
    } else {
        cout << "x is not greater than y" << endl;
    }
}

// Intermediate code generation for if statement
void generateIf(const string& condition, const string& trueLabel, const string& falseLabel) {
    cout << "if (" << condition << ") goto " << trueLabel << ";" << endl;
    cout << "goto " << falseLabel << ";" << endl;
    cout << trueLabel << ":" << endl;
}

// Intermediate code generation for while loop
void generateWhile(const string& condition, const string& loopStartLabel, const string& loopEndLabel) {
    cout << loopStartLabel << ":" << endl;
    cout << "if (" << condition << ") goto " << loopEndLabel << ";" << endl;
}

int main() {
    // Generating intermediate code for the example function
    generateIf("x > y", "trueLabel1", "falseLabel1");
    generateWhile("a < x", "loopStartLabel1", "loopEndLabel1");
    cout << "cout << \"a is less than x\" << endl;" << endl;
    cout << "a++;" << endl;
    cout << "goto loopStartLabel1;" << endl;
    cout << "loopEndLabel1:" << endl;
    cout << "falseLabel1:" << endl;
    cout << "cout << \"x is not greater than y\" << endl;" << endl;

    return 0;
}