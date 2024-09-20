#include<bits/stdc++.h>
using namespace std;

template <typename T>
class Stack {
private:
    T* data;
    int topIndex;
    int length;

    void resize() {
        length *= 2;
        T* newData = new T[length];
        for (int i = 0; i <= topIndex; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    Stack(int size = 10) {
        data = new T[size];
        topIndex = -1;
        length = size;
    }

    ~Stack() {
        delete[] data;
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == length - 1;
    }

    void push(T value) {
        if (isFull()) {
            resize();
        }
        data[++topIndex] = value;
    }

    T pop() {
        if (isEmpty()) {
            throw out_of_range("Stack is Empty");
        }
        return data[topIndex--];
    }

    T top() const {
        if (isEmpty()) {
            throw out_of_range("Stack is Empty");
        }
        return data[topIndex];
    }

    void print() const {
        for (int i = 0; i <= topIndex; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    int getTopIndex() const {
        return topIndex;
    }

    int getLength() const {
        return length;
    }

    T getElementAt(int index) const {
        return data[index];
    }

    void reverse() {
        Stack<T> tempStack;
        while (!isEmpty()) {
            tempStack.push(pop());
        }
        *this = tempStack;
    }
};

bool areParenthesesBalanced(const string& expression) {
    Stack<char> stack;
    for (char ch : expression) {
        if (ch == '(' || ch == '[' || ch == '{') {
            stack.push(ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (stack.isEmpty()) return false;
            char open = stack.pop();
            if ((ch == ')' && open != '(') || 
                (ch == ']' && open != '[') ||
                (ch == '}' && open != '{')) {
                return false;
            }
        }
    }
    return stack.isEmpty();
}

string reverseString(const string& str) {
    string reversed = str;
    reverse(reversed.begin(), reversed.end());
    return reversed;
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

string infixToPostfix(const string& infix) {
    Stack<char> stack;
    string postfix;

    for (char ch : infix) {
        if (isalnum(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                postfix += stack.pop();
            }
            stack.pop();  // Pop the '('
        } else {
            while (!stack.isEmpty() && precedence(ch) <= precedence(stack.top())) {
                postfix += stack.pop();
            }
            stack.push(ch);
        }
    }

    while (!stack.isEmpty()) {
        postfix += stack.pop();
    }

    return postfix;
}

string infixToPrefix(const string& infix) {
    string reversedInfix = reverseString(infix);
    string reversedPostfix = infixToPostfix(reversedInfix);
    return reverseString(reversedPostfix);
}

int evaluatePostfix(const string& postfix) {
    Stack<int> stack;
    for (char ch : postfix) {
        if (isdigit(ch)) {
            stack.push(ch - '0');
        } else {
            int val2 = stack.pop();
            int val1 = stack.pop();
            switch (ch) {
                case '+': stack.push(val1 + val2); break;
                case '-': stack.push(val1 - val2); break;
                case '*': stack.push(val1 * val2); break;
                case '/': 
                    if (val2 == 0) throw runtime_error("Division by zero");
                    stack.push(val1 / val2); 
                    break;
            }
        }
    }
    return stack.pop();
}

int evaluatePrefix(const string& prefix) {
    Stack<int> stack;
    for (int i = prefix.length() - 1; i >= 0; --i) {
        char ch = prefix[i];
        if (isdigit(ch)) {
            stack.push(ch - '0');
        } else {
            int val1 = stack.pop();
            int val2 = stack.pop();
            switch (ch) {
                case '+': stack.push(val1 + val2); break;
                case '-': stack.push(val1 - val2); break;
                case '*': stack.push(val1 * val2); break;
                case '/': stack.push(val1 / val2); break;
            }
        }
    }
    return stack.pop();
}

Stack<int> mergeStacks(const Stack<int>& s1, const Stack<int>& s2) {
    Stack<int> result(s1.getLength() + s2.getLength());
    for (int i = 0; i <= s1.getTopIndex(); i++) {
        result.push(s1.getElementAt(i));
    }
    for (int i = 0; i <= s2.getTopIndex(); i++) {
        result.push(s2.getElementAt(i));
    }
    return result;
}

int main() {
    // Testing Stack Operations
    Stack<int> stack1;
    stack1.push(10);
    stack1.push(20);
    stack1.push(30);
    cout << "Stack 1 contents: ";
    stack1.print();

    // Reverse the stack
    stack1.reverse();
    cout << "Reversed Stack 1: ";
    stack1.print();

    // Parentheses Balanced Test
    string expr1 = "{[()]}";
    cout << "Are parentheses balanced in '" << expr1 << "'? " << (areParenthesesBalanced(expr1) ? "Yes" : "No") << endl;

    // Infix to Postfix and Evaluation Test
    string infix = "3+(4*5)-7";
    string postfix = infixToPostfix(infix);
    cout << "Infix: " << infix << endl;
    cout << "Postfix: " << postfix << endl;
    cout << "Postfix Evaluation: " << evaluatePostfix(postfix) << endl;

    // Infix to Prefix and Evaluation Test
    string prefix = infixToPrefix(infix);
    cout << "Prefix: " << prefix << endl;
    cout << "Prefix Evaluation: " << evaluatePrefix(prefix) << endl;

    // Merging Two Stacks
    Stack<int> stack2;
    stack2.push(40);
    stack2.push(50);
    cout << "Stack 2 contents: ";
    stack2.print();

    Stack<int> mergedStack = mergeStacks(stack1, stack2);
    cout << "Merged Stack contents: ";
    mergedStack.print();

    return 0;
}
