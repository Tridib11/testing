#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n;
string s;
vector<char> st;
vector<char> a;
vector<string> grammar;

void StackAndInput() { // print stack and input vector elements
    cout << "\n$";
    for (auto x : st)
        cout << x;
    cout << "\t";
    for (auto x : a)
        cout << x;
}

void check() { // check if there any reduction possible for stack elements
    for (int i = st.size() - 1; i >= 0; i--) {
        if (st[i] == 'a') {
            st[i] = 'E';
            StackAndInput();
            cout << "$\t" << "REDUCE E->a";
            check(); // we again do checking because here we may need to reduce continuously
        }
        if (i + 2 < st.size() && st[i] == 'E' && (st[i + 1] == '+' || st[i + 1] == '*') && st[i + 2] == 'E') {
            st.erase(st.begin() + i, st.begin() + i + 3);
            StackAndInput();
            if (st[i + 1] == '+')
                cout << "$\t" << "REDUCE E->E+E";
            else if (st[i + 1] == '*')
                cout << "$\t" << "REDUCE E->E*E";
        }
    }
}

int main() {
    cout << "Enter the number of productions: ";
    int num_productions;
    cin >> num_productions;

    cout << "Enter the grammar rules:" << endl;
    for (int i = 0; i < num_productions; ++i) {
        string rule;
        cin >> rule;
        grammar.push_back(rule);
    }

    cout << "\nEnter the expression: ";
    cin >> s;
    n = s.length();
    for (int i = 0; i < n; i++)
        a.push_back(s[i]);

    cout << "\nstack\t input\taction";
    for (int i = 0; i < n; i++) {
        st.push_back(a[i]);
        a[i] = ' '; // replace element with space so that it not visible in output
        StackAndInput();
        cout << "$\t" << "SHIFT->" << st.back();
        check();
    }
    if (st.size() == 1 && st[0] == 'E')
        cout << "\n\nString accepted";
    else
        cout << "\n\nString rejected";
    return 0;
}




// Enter the number of productions: 3
// Enter the grammar rules:
// E->A
// E->E+E
// E->E*E*E

// Enter the expression: A+A*A

// stack	 input	action
// $A	 +A*A$	SHIFT->A
// $A+	  A*A$	SHIFT->+
// $A+A	   *A$	SHIFT->A
// $A+A*	    A$	SHIFT->*
// $A+A*A	     $	SHIFT->A

// String rekldjfkjd