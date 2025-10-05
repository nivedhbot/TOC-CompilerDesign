# Code Generator for Stack Machine

This program translates arithmetic expressions into assembly code for a stack-based machine. It converts infix expressions to postfix notation and generates corresponding stack machine instructions.

## 📋 Overview

**Input:** `(a+b)*c`

**Output:**
```
PUSH a
PUSH b
ADD
PUSH c
MUL
```

## 🎯 Features

- ✅ **Infix to Postfix Conversion**: Converts standard arithmetic notation to Reverse Polish Notation (RPN)
- ✅ **Assembly Code Generation**: Generates stack machine instructions
- ✅ **Stack Machine Simulation**: Shows step-by-step execution trace
- ✅ **Multiple Test Cases**: Demonstrates various expression types
- ✅ **Operator Support**: Handles +, -, *, / with proper precedence

## 🔧 System Requirements & Installation

### Step 1: Install C++ Compiler

**Windows:**
1. Download and install MinGW-w64 or Visual Studio
   - MinGW-w64: https://www.mingw-w64.org/downloads/
   - Visual Studio: https://visualstudio.microsoft.com/downloads/
2. For MinGW: Add the compiler's `bin` directory to system PATH
3. Verify installation: `g++ --version`

**Linux (Ubuntu/Debian):**
```bash
sudo apt update
sudo apt install g++
g++ --version
```

**Linux (Fedora/RHEL):**
```bash
sudo dnf install gcc-c++
g++ --version
```

**macOS:**
```bash
xcode-select --install
g++ --version
```

### Step 2: Verify Installation

Open terminal/command prompt and verify:

```bash
g++ --version
```

You should see version information for the C++ compiler.

## 🚀 How to Run the Program

### Step 1: Navigate to Project Directory

**Windows:**
```bash
cd e:/TOC/CascadeProjects/windsurf-project/Code_Generator
```

**Linux/macOS:**
```bash
cd /path/to/Code_Generator
```

### Step 2: Compile the Program

**Windows:**
```bash
g++ code_generator.cpp -o code_generator.exe
```

**Linux/macOS:**
```bash
g++ code_generator.cpp -o code_generator
```

**Expected Output:** No errors. Successful compilation produces no output.

### Step 3: Run the Executable

**Windows:**
```bash
./code_generator.exe
```

Or simply:
```bash
code_generator.exe
```

**Linux/macOS:**
```bash
./code_generator
```

## 📋 Complete Execution Steps (Quick Reference)

**Windows:**
```bash
# 1. Navigate to directory
cd Code_Generator

# 2. Compile
g++ code_generator.cpp -o code_generator.exe

# 3. Run
./code_generator.exe
```

**Linux/macOS:**
```bash
# 1. Navigate to directory
cd Code_Generator

# 2. Compile
g++ code_generator.cpp -o code_generator

# 3. Run
./code_generator
```

## 📝 Example Output

```
========================================
Code Generator for Stack Machine
========================================

Translates arithmetic expressions into
assembly code for a stack-based machine.

========================================
Input Expression
========================================
(a+b)*c

========================================
Code Generation Process
========================================

Step 1: Parse Infix Expression
Input: (a+b)*c

Step 2: Convert to Postfix (RPN)
Postfix: a b + c *

Step 3: Generate Assembly Code
Assembly instructions generated: 5

========================================
Generated Assembly Code
========================================
PUSH a
PUSH b
ADD
PUSH c
MUL

========================================
Stack Machine Simulation
========================================

Execution trace:
Instruction         Stack (top->bottom)
----------------    --------------------
PUSH a              a
PUSH b              b a
ADD                 (a+b)
PUSH c              c (a+b)
MUL                 ((a+b)*c)

Final result on stack: ((a+b)*c)

========================================
Code Generation Complete!
========================================

========================================
How Stack Machine Works
========================================
1. PUSH operand - Pushes value onto stack
2. ADD - Pops two values, adds them, pushes result
3. SUB - Pops two values, subtracts, pushes result
4. MUL - Pops two values, multiplies, pushes result
5. DIV - Pops two values, divides, pushes result

========================================
Additional Test Cases
========================================

Expression: a+b
Assembly:
  PUSH a
  PUSH b
  ADD

Expression: a*b+c
Assembly:
  PUSH a
  PUSH b
  MUL
  PUSH c
  ADD

Expression: (a+b)*(c+d)
Assembly:
  PUSH a
  PUSH b
  ADD
  PUSH c
  PUSH d
  ADD
  MUL

Expression: a+b*c
Assembly:
  PUSH a
  PUSH b
  PUSH c
  MUL
  ADD
```

## 🔍 How It Works

### Code Generation Pipeline

```
Infix Expression
    ↓
Parse & Tokenize
    ↓
Convert to Postfix (RPN)
    ↓
Generate Assembly Instructions
    ↓
Stack Machine Code
```

### Detailed Process

**Step 1: Infix to Postfix Conversion**
- Uses the Shunting Yard algorithm
- Handles operator precedence (* and / before + and -)
- Processes parentheses correctly
- Example: `(a+b)*c` → `a b + c *`

**Step 2: Assembly Code Generation**
- Scans postfix expression left to right
- For operands: Generate `PUSH operand`
- For operators: Generate operation instruction (ADD, SUB, MUL, DIV)
- Maintains proper evaluation order

**Step 3: Stack Machine Execution**
- PUSH: Places operand on top of stack
- Operations: Pop two operands, perform operation, push result
- Final result remains on stack top

## 📚 Stack Machine Concepts

### What is a Stack Machine?

A stack machine is a computer architecture that uses a stack as the primary data structure for computation. All operations work with values on the stack.

### Stack Operations

1. **PUSH value**: Add value to top of stack
2. **POP**: Remove and return top value
3. **Binary Operations**: Pop two values, perform operation, push result

### Example Execution: (a+b)*c

```
Instruction    Stack State
-----------    -----------
PUSH a         [a]
PUSH b         [b, a]
ADD            [a+b]
PUSH c         [c, a+b]
MUL            [(a+b)*c]
```

## 🎨 Supported Features

### Operators
- **Addition**: `+`
- **Subtraction**: `-`
- **Multiplication**: `*`
- **Division**: `/`

### Operator Precedence
- Higher: `*`, `/`
- Lower: `+`, `-`
- Parentheses: `(`, `)`

### Operands
- Variables: `a`, `b`, `c`, etc.
- Numbers: `1`, `2`, `3`, etc.

## 🔄 Modifying Input Expression

To test with different expressions, modify the `expression` variable in `main()`:

```cpp
string expression = "(a+b)*c";  // Change this
```

### Example Expressions

```cpp
// Simple addition
string expression = "a+b";

// With precedence
string expression = "a+b*c";  // Evaluates as a+(b*c)

// Complex nested
string expression = "((a+b)*(c-d))/e";

// Multiple operations
string expression = "a*b+c*d";
```

## 🐛 Troubleshooting

### Compilation Errors

**Error: `g++: command not found`**
- **Solution**: Install C++ compiler (see installation steps above)

**Error: `No such file or directory`**
- **Solution**: Ensure you're in the correct directory with `code_generator.cpp`

### Runtime Issues

**Issue: Incorrect output**
- Check expression syntax (balanced parentheses)
- Ensure operators are supported (+, -, *, /)
- Variables should be single characters

## 📚 Theory Background

### Reverse Polish Notation (RPN)

Also called postfix notation, RPN places operators after their operands:
- Infix: `(a + b) * c`
- Postfix: `a b + c *`

**Advantages:**
- No need for parentheses
- Easy to evaluate using a stack
- Unambiguous operator precedence

### Shunting Yard Algorithm

Developed by Edsger Dijkstra, this algorithm converts infix to postfix:
1. Read tokens left to right
2. Operands go directly to output
3. Operators go to stack based on precedence
4. Pop operators when lower precedence found
5. Handle parentheses specially

### Stack-Based Evaluation

Postfix expressions are evaluated using a stack:
1. Scan expression left to right
2. Push operands onto stack
3. For operators: pop operands, compute, push result
4. Final result is top of stack

## 📄 Code Structure

```
code_generator.cpp
├── CodeGenerator class
│   ├── isOperator()           - Check if character is operator
│   ├── getPrecedence()        - Get operator precedence
│   ├── infixToPostfix()       - Convert infix to postfix
│   ├── getOperatorInstruction() - Map operator to assembly
│   ├── generateFromPostfix()  - Generate assembly code
│   ├── generate()             - Main generation function
│   ├── printAssembly()        - Display generated code
│   └── simulate()             - Simulate stack execution
└── main()                     - Entry point and test cases
```

## 🎓 Educational Value

This tool demonstrates:
- **Compiler Design**: Code generation phase
- **Data Structures**: Stack operations
- **Algorithms**: Shunting yard algorithm
- **Expression Evaluation**: Postfix notation
- **Assembly Programming**: Low-level instruction generation

## 💡 Use Cases

- **Compiler Construction**: Backend code generation
- **Expression Evaluation**: Calculator implementations
- **Virtual Machines**: Stack-based VM instruction sets
- **Educational**: Understanding compilation process

## 📄 License

Educational project for Compiler Design and Code Generation coursework.

## 👨‍💻 Author

Created for learning compiler design and code generation techniques.

---

**Note**: This is a simplified code generator for educational purposes. Production compilers use more sophisticated techniques including register allocation, optimization, and target-specific code generation.
