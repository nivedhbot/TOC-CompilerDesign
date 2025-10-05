#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cctype>
#include <sstream>

using namespace std;

class CodeGenerator {
private:
    vector<string> assemblyCode;
    
    // Check if character is an operator
    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/');
    }
    
    // Get operator precedence
    int getPrecedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }
    
    // Convert infix expression to postfix (Reverse Polish Notation)
    string infixToPostfix(const string& infix) {
        stack<char> operators;
        string postfix = "";
        
        for (size_t i = 0; i < infix.length(); i++) {
            char c = infix[i];
            
            // Skip whitespace
            if (isspace(c)) continue;
            
            // If operand (variable or number), add to postfix
            if (isalnum(c)) {
                postfix += c;
                postfix += ' ';
            }
            // If opening parenthesis, push to stack
            else if (c == '(') {
                operators.push(c);
            }
            // If closing parenthesis, pop until opening parenthesis
            else if (c == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    postfix += operators.top();
                    postfix += ' ';
                    operators.pop();
                }
                if (!operators.empty()) operators.pop(); // Remove '('
            }
            // If operator
            else if (isOperator(c)) {
                while (!operators.empty() && operators.top() != '(' &&
                       getPrecedence(operators.top()) >= getPrecedence(c)) {
                    postfix += operators.top();
                    postfix += ' ';
                    operators.pop();
                }
                operators.push(c);
            }
        }
        
        // Pop remaining operators
        while (!operators.empty()) {
            if (operators.top() != '(') {
                postfix += operators.top();
                postfix += ' ';
            }
            operators.pop();
        }
        
        return postfix;
    }
    
    // Get assembly instruction for operator
    string getOperatorInstruction(char op) {
        switch(op) {
            case '+': return "ADD";
            case '-': return "SUB";
            case '*': return "MUL";
            case '/': return "DIV";
            default: return "";
        }
    }
    
    // Generate assembly code from postfix expression
    void generateFromPostfix(const string& postfix) {
        stringstream ss(postfix);
        string token;
        
        while (ss >> token) {
            if (token.length() == 1 && isOperator(token[0])) {
                // It's an operator
                string instruction = getOperatorInstruction(token[0]);
                assemblyCode.push_back(instruction);
            } else {
                // It's an operand (variable or number)
                assemblyCode.push_back("PUSH " + token);
            }
        }
    }
    
public:
    // Main function to generate code from infix expression
    void generate(const string& expression) {
        assemblyCode.clear();
        
        cout << "\n========================================\n";
        cout << "Code Generation Process\n";
        cout << "========================================\n";
        
        cout << "\nStep 1: Parse Infix Expression\n";
        cout << "Input: " << expression << "\n";
        
        cout << "\nStep 2: Convert to Postfix (RPN)\n";
        string postfix = infixToPostfix(expression);
        cout << "Postfix: " << postfix << "\n";
        
        cout << "\nStep 3: Generate Assembly Code\n";
        generateFromPostfix(postfix);
        
        cout << "Assembly instructions generated: " << assemblyCode.size() << "\n";
    }
    
    // Print generated assembly code
    void printAssembly() {
        cout << "\n========================================\n";
        cout << "Generated Assembly Code\n";
        cout << "========================================\n";
        
        for (const auto& instruction : assemblyCode) {
            cout << instruction << "\n";
        }
    }
    
    // Get assembly code as vector
    vector<string> getAssemblyCode() {
        return assemblyCode;
    }
    
    // Simulate stack machine execution
    void simulate() {
        cout << "\n========================================\n";
        cout << "Stack Machine Simulation\n";
        cout << "========================================\n";
        
        stack<string> evalStack;
        
        cout << "\nExecution trace:\n";
        cout << "Instruction         Stack (top->bottom)\n";
        cout << "----------------    --------------------\n";
        
        for (const auto& instruction : assemblyCode) {
            cout << instruction;
            
            // Pad instruction for alignment
            for (int i = instruction.length(); i < 20; i++) {
                cout << " ";
            }
            
            if (instruction.substr(0, 4) == "PUSH") {
                string operand = instruction.substr(5);
                evalStack.push(operand);
            } else {
                // It's an operation
                if (evalStack.size() >= 2) {
                    string op2 = evalStack.top(); evalStack.pop();
                    string op1 = evalStack.top(); evalStack.pop();
                    string result = "(" + op1 + instruction.substr(0, 3) + op2 + ")";
                    evalStack.push(result);
                }
            }
            
            // Print stack contents
            stack<string> temp = evalStack;
            vector<string> stackContents;
            while (!temp.empty()) {
                stackContents.push_back(temp.top());
                temp.pop();
            }
            
            for (const auto& item : stackContents) {
                cout << item << " ";
            }
            cout << "\n";
        }
        
        cout << "\nFinal result on stack: ";
        if (!evalStack.empty()) {
            cout << evalStack.top() << "\n";
        }
    }
};

int main() {
    CodeGenerator generator;
    
    cout << "========================================\n";
    cout << "Code Generator for Stack Machine\n";
    cout << "========================================\n";
    cout << "\nTranslates arithmetic expressions into\n";
    cout << "assembly code for a stack-based machine.\n";
    
    // Test expression
    string expression = "(a+b)*c";
    
    cout << "\n========================================\n";
    cout << "Input Expression\n";
    cout << "========================================\n";
    cout << expression << "\n";
    
    // Generate code
    generator.generate(expression);
    
    // Print assembly
    generator.printAssembly();
    
    // Simulate execution
    generator.simulate();
    
    cout << "\n========================================\n";
    cout << "Code Generation Complete!\n";
    cout << "========================================\n";
    
    cout << "\n========================================\n";
    cout << "How Stack Machine Works\n";
    cout << "========================================\n";
    cout << "1. PUSH operand - Pushes value onto stack\n";
    cout << "2. ADD - Pops two values, adds them, pushes result\n";
    cout << "3. SUB - Pops two values, subtracts, pushes result\n";
    cout << "4. MUL - Pops two values, multiplies, pushes result\n";
    cout << "5. DIV - Pops two values, divides, pushes result\n";
    
    cout << "\n========================================\n";
    cout << "Additional Test Cases\n";
    cout << "========================================\n";
    
    // Additional test cases
    vector<string> testCases = {
        "a+b",
        "a*b+c",
        "(a+b)*(c+d)",
        "a+b*c"
    };
    
    for (const auto& expr : testCases) {
        cout << "\nExpression: " << expr << "\n";
        CodeGenerator gen;
        gen.generate(expr);
        cout << "Assembly:\n";
        for (const auto& instr : gen.getAssemblyCode()) {
            cout << "  " << instr << "\n";
        }
    }
    
    return 0;
}
