#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

// Structure to represent a statement
struct Statement {
    string variable;
    string operand1;
    string op;
    string operand2;
    bool isConstant;
    int constantValue;
    bool isDead;
    
    Statement() : isConstant(false), constantValue(0), isDead(false) {}
};

class CodeOptimizer {
private:
    vector<Statement> statements;
    map<string, int> constantValues;
    map<string, bool> variableUsed;
    
    // Helper function to check if a string is a number
    bool isNumber(const string& s) {
        if (s.empty()) return false;
        for (size_t i = 0; i < s.length(); i++) {
            if (i == 0 && s[i] == '-') continue;
            if (!isdigit(s[i])) return false;
        }
        return true;
    }
    
    // Helper function to convert string to integer
    int toInt(const string& s) {
        return stoi(s);
    }
    
    // Parse a statement like "x = 2 * 8"
    Statement parseStatement(const string& line) {
        Statement stmt;
        stringstream ss(line);
        string equals;
        
        ss >> stmt.variable >> equals;
        
        // Check if it's a simple assignment (x = 5) or expression (x = 2 * 8)
        string first, oper, second;
        ss >> first;
        
        if (ss >> oper >> second) {
            // It's an expression
            stmt.operand1 = first;
            stmt.op = oper;
            stmt.operand2 = second;
        } else {
            // Simple assignment
            stmt.operand1 = first;
            stmt.op = "";
            stmt.operand2 = "";
        }
        
        return stmt;
    }
    
    // Perform constant folding (only when BOTH operands are constants)
    void constantFolding() {
        cout << "\n--- Step 1: Constant Folding ---\n";
        
        for (auto& stmt : statements) {
            if (stmt.op.empty()) {
                // Simple assignment - don't fold here, let strength reduction handle it
                continue;
            } else {
                // Expression with operator - only fold if BOTH operands are numeric constants
                int val1 = 0, val2 = 0;
                bool bothConstants = false;
                
                // Check if BOTH operands are numeric constants
                if (isNumber(stmt.operand1) && isNumber(stmt.operand2)) {
                    val1 = toInt(stmt.operand1);
                    val2 = toInt(stmt.operand2);
                    bothConstants = true;
                }
                
                // Perform constant folding only when both are constants
                if (bothConstants) {
                    int result = 0;
                    if (stmt.op == "+") result = val1 + val2;
                    else if (stmt.op == "-") result = val1 - val2;
                    else if (stmt.op == "*") result = val1 * val2;
                    else if (stmt.op == "/") result = val1 / val2;
                    
                    stmt.isConstant = true;
                    stmt.constantValue = result;
                    constantValues[stmt.variable] = result;
                    cout << "Computed: " << stmt.variable << " = " << val1 << " " << stmt.op 
                         << " " << val2 << " = " << result << "\n";
                }
            }
        }
    }
    
    // Perform algebraic simplification (strength reduction)
    void strengthReduction() {
        cout << "\n--- Step 2: Strength Reduction & Algebraic Simplification ---\n";
        
        for (auto& stmt : statements) {
            if (stmt.op.empty() || stmt.isConstant) continue;
            
            // x * 1 = x or 1 * x = x
            if (stmt.op == "*") {
                if (stmt.operand2 == "1") {
                    cout << "Simplified: " << stmt.variable << " = " << stmt.operand1 
                         << " * 1 => " << stmt.variable << " = " << stmt.operand1 << "\n";
                    stmt.op = "";
                    stmt.operand2 = "";
                } else if (stmt.operand1 == "1") {
                    cout << "Simplified: " << stmt.variable << " = 1 * " << stmt.operand2 
                         << " => " << stmt.variable << " = " << stmt.operand2 << "\n";
                    stmt.operand1 = stmt.operand2;
                    stmt.op = "";
                    stmt.operand2 = "";
                }
                // x * 0 = 0 or 0 * x = 0
                else if (stmt.operand2 == "0" || stmt.operand1 == "0") {
                    cout << "Simplified: " << stmt.variable << " = ... * 0 => " 
                         << stmt.variable << " = 0\n";
                    stmt.operand1 = "0";
                    stmt.op = "";
                    stmt.operand2 = "";
                    stmt.isConstant = true;
                    stmt.constantValue = 0;
                    constantValues[stmt.variable] = 0;
                }
            }
            // x + 0 = x or 0 + x = x
            else if (stmt.op == "+") {
                if (stmt.operand2 == "0") {
                    cout << "Simplified: " << stmt.variable << " = " << stmt.operand1 
                         << " + 0 => " << stmt.variable << " = " << stmt.operand1 << "\n";
                    stmt.op = "";
                    stmt.operand2 = "";
                } else if (stmt.operand1 == "0") {
                    cout << "Simplified: " << stmt.variable << " = 0 + " << stmt.operand2 
                         << " => " << stmt.variable << " = " << stmt.operand2 << "\n";
                    stmt.operand1 = stmt.operand2;
                    stmt.op = "";
                    stmt.operand2 = "";
                }
            }
            // x - 0 = x
            else if (stmt.op == "-") {
                if (stmt.operand2 == "0") {
                    cout << "Simplified: " << stmt.variable << " = " << stmt.operand1 
                         << " - 0 => " << stmt.variable << " = " << stmt.operand1 << "\n";
                    stmt.op = "";
                    stmt.operand2 = "";
                }
            }
            // x / 1 = x
            else if (stmt.op == "/") {
                if (stmt.operand2 == "1") {
                    cout << "Simplified: " << stmt.variable << " = " << stmt.operand1 
                         << " / 1 => " << stmt.variable << " = " << stmt.operand1 << "\n";
                    stmt.op = "";
                    stmt.operand2 = "";
                }
            }
        }
    }
    
    // Variable substitution and copy propagation
    void copyPropagation() {
        cout << "\n--- Step 3: Copy Propagation ---\n";
        map<string, string> aliases;  // Maps variable to its alias
        
        // First pass: identify simple copies (y = x)
        for (auto& stmt : statements) {
            if (stmt.op.empty() && !stmt.isConstant && !isNumber(stmt.operand1)) {
                aliases[stmt.variable] = stmt.operand1;
                cout << "Copy detected: " << stmt.variable << " = " << stmt.operand1 << "\n";
            }
        }
        
        // Second pass: substitute aliases in subsequent statements
        for (auto& stmt : statements) {
            // Substitute in operand1
            if (!stmt.op.empty() && aliases.find(stmt.operand1) != aliases.end()) {
                string original = stmt.operand1;
                stmt.operand1 = aliases[original];
                cout << "Substituted: " << original << " -> " << stmt.operand1 
                     << " in " << stmt.variable << "\n";
            }
            // Also substitute in simple assignments
            if (stmt.op.empty() && !stmt.isConstant && aliases.find(stmt.operand1) != aliases.end()) {
                string original = stmt.operand1;
                stmt.operand1 = aliases[original];
                cout << "Substituted: " << original << " -> " << stmt.operand1 
                     << " in " << stmt.variable << "\n";
            }
        }
    }
    
    // Detect dead code
    void deadCodeElimination() {
        cout << "\n--- Step 4: Dead Code Elimination ---\n";
        
        // Mark all variables as unused initially
        for (const auto& stmt : statements) {
            variableUsed[stmt.variable] = false;
        }
        
        // Mark variables that are used in expressions
        for (const auto& stmt : statements) {
            if (!stmt.op.empty()) {
                if (!isNumber(stmt.operand1)) {
                    variableUsed[stmt.operand1] = true;
                }
                if (!isNumber(stmt.operand2)) {
                    variableUsed[stmt.operand2] = true;
                }
            } else if (!stmt.operand1.empty() && !isNumber(stmt.operand1)) {
                variableUsed[stmt.operand1] = true;
            }
        }
        
        // Assume the last variable or certain variables are used (output)
        // In this case, we'll mark 'z' as used (final output)
        if (!statements.empty()) {
            variableUsed[statements.back().variable] = true;
        }
        
        // Mark statements as dead if their variable is never used
        for (auto& stmt : statements) {
            if (!variableUsed[stmt.variable]) {
                stmt.isDead = true;
                cout << "Dead code detected: " << stmt.variable << " is never used\n";
            }
        }
    }
    
public:
    void addStatement(const string& line) {
        Statement stmt = parseStatement(line);
        statements.push_back(stmt);
    }
    
    void optimize() {
        cout << "\n========================================\n";
        cout << "Code Optimization Process\n";
        cout << "========================================\n";
        cout << flush;
        
        constantFolding();
        cout << flush;
        strengthReduction();
        cout << flush;
        copyPropagation();
        cout << flush;
        deadCodeElimination();
        cout << flush;
    }
    
    void printOriginalCode() {
        cout << "\n========================================\n";
        cout << "Original Code:\n";
        cout << "========================================\n";
        cout << flush;
        for (const auto& stmt : statements) {
            cout << stmt.variable << " = ";
            if (stmt.op.empty()) {
                cout << stmt.operand1;
            } else {
                cout << stmt.operand1 << " " << stmt.op << " " << stmt.operand2;
            }
            cout << "\n";
            cout << flush;
        }
    }
    
    void printOptimizedCode() {
        cout << "\n========================================\n";
        cout << "Optimized Code:\n";
        cout << "========================================\n";
        cout << flush;
        
        for (const auto& stmt : statements) {
            if (stmt.isDead) {
                continue; // Skip dead code
            }
            
            cout << stmt.variable << " = ";
            
            if (stmt.isConstant) {
                cout << stmt.constantValue;
            } else if (stmt.op.empty()) {
                // Check if operand1 is a variable that was constant folded
                if (!isNumber(stmt.operand1) && constantValues.find(stmt.operand1) != constantValues.end()) {
                    cout << stmt.operand1;  // Keep variable name for readability
                } else {
                    cout << stmt.operand1;
                }
            } else {
                cout << stmt.operand1 << " " << stmt.op << " " << stmt.operand2;
            }
            cout << "\n";
            cout << flush;
        }
    }
    
    void printOptimizationSummary() {
        cout << "\n========================================\n";
        cout << "Optimization Summary\n";
        cout << "========================================\n";
        cout << flush;
        
        int totalStatements = statements.size();
        int deadStatements = 0;
        int constantFolded = 0;
        
        for (const auto& stmt : statements) {
            if (stmt.isDead) deadStatements++;
            if (stmt.isConstant) constantFolded++;
        }
        
        cout << "Total statements: " << totalStatements << "\n";
        cout << "Constants folded: " << constantFolded << "\n";
        cout << "Dead code removed: " << deadStatements << "\n";
        cout << "Final statements: " << (totalStatements - deadStatements) << "\n";
        cout << flush;
        
        if (constantFolded > 0) {
            cout << "\nOptimizations Applied:\n";
            cout << "  ✓ Redundant computations eliminated\n";
        }
        if (deadStatements > 0) {
            cout << "  ✓ Dead code detected and removed\n";
        }
        cout << "  ✓ Strength reduction applied\n";
        cout << "  ✓ Copy propagation performed\n";
        cout << flush;
    }
};

int main() {
    CodeOptimizer optimizer;
    
    cout << "========================================\n";
    cout << "Code Optimization Tool\n";
    cout << "========================================\n";
    cout << "\nOptimization Techniques:\n";
    cout << "1. Constant Folding (Redundant Computation)\n";
    cout << "2. Strength Reduction (Algebraic Simplification)\n";
    cout << "3. Dead Code Elimination\n";
    
    // Input code
    cout << "\n========================================\n";
    cout << "Input Code:\n";
    cout << "========================================\n";
    
    vector<string> inputCode = {
        "x = 2 * 8",
        "y = x * 1",
        "z = y + 0"
    };
    
    for (const auto& line : inputCode) {
        cout << line << "\n";
        optimizer.addStatement(line);
    }
    
    // Print original code
    optimizer.printOriginalCode();
    
    // Perform optimization
    optimizer.optimize();
    
    // Print optimized code
    optimizer.printOptimizedCode();
    
    // Print summary
    optimizer.printOptimizationSummary();
    
    cout << "\n========================================\n";
    cout << "Optimization Complete!\n";
    cout << "========================================\n";
    
    return 0;
}
