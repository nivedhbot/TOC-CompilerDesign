# Code Optimization Tool

This program implements a code optimizer that detects and eliminates redundant computations, dead code, and performs strength reduction on simple arithmetic expressions.

## 📋 Overview

**Input Code:**
```
x = 2 * 8
y = x * 1
z = y + 0
```

**Output (After Optimization):**
```
x = 16
z = x
```

## 🎯 Optimization Techniques Implemented

### 1. Constant Folding (Redundant Computation Elimination)
- Evaluates constant expressions at compile time
- Only folds when **both operands are numeric constants**
- Example: `x = 2 * 8` → `x = 16`
- Does not propagate variables to preserve relationships

### 2. Strength Reduction (Algebraic Simplification)
- Replaces expensive operations with cheaper equivalents
- **Identity Operations:**
  - `x * 1` → `x`
  - `x + 0` → `x`
  - `x - 0` → `x`
  - `x / 1` → `x`
- **Zero Operations:**
  - `x * 0` → `0`
  - `0 * x` → `0`

### 3. Copy Propagation
- Identifies simple copy assignments (e.g., `y = x`)
- Substitutes variable copies in subsequent statements
- Preserves variable relationships
- Example: `y = x`, `z = y` → `z = x`

### 4. Dead Code Elimination
- Identifies and removes variables that are never used
- Analyzes variable usage throughout the program
- Removes assignments to unused variables
- Example: If `y` is assigned but never used, it's removed

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
cd e:/TOC/CascadeProjects/windsurf-project/Code_Optimization
```

**Linux/macOS:**
```bash
cd /path/to/Code_Optimization
```

### Step 2: Compile the Program

**Windows:**
```bash
g++ optimizer.cpp -o optimizer.exe
```

**Linux/macOS:**
```bash
g++ optimizer.cpp -o optimizer
```

**Expected Output:** No errors. Successful compilation produces no output.

### Step 3: Run the Executable

**Windows:**
```bash
./optimizer.exe
```

Or simply:
```bash
optimizer.exe
```

**Linux/macOS:**
```bash
./optimizer
```

## 📋 Complete Execution Steps (Quick Reference)

**Windows:**
```bash
# 1. Navigate to directory
cd Code_Optimization

# 2. Compile
g++ optimizer.cpp -o optimizer.exe

# 3. Run
./optimizer.exe
```

**Linux/macOS:**
```bash
# 1. Navigate to directory
cd Code_Optimization

# 2. Compile
g++ optimizer.cpp -o optimizer

# 3. Run
./optimizer
```

## 📝 Example Output

```
========================================
Code Optimization Tool
========================================

Optimization Techniques:
1. Constant Folding (Redundant Computation)
2. Strength Reduction (Algebraic Simplification)
3. Copy Propagation
4. Dead Code Elimination

========================================
Input Code:
========================================
x = 2 * 8
y = x * 1
z = y + 0

========================================
Original Code:
========================================
x = 2 * 8
y = x * 1
z = y + 0

========================================
Code Optimization Process
========================================

--- Step 1: Constant Folding ---
Computed: x = 2 * 8 = 16

--- Step 2: Strength Reduction & Algebraic Simplification ---
Simplified: y = x * 1 => y = x
Simplified: z = y + 0 => z = y

--- Step 3: Copy Propagation ---
Copy detected: y = x
Copy detected: z = y
Substituted: y -> x in z

--- Step 4: Dead Code Elimination ---
Dead code detected: y is never used

========================================
Optimized Code:
========================================
x = 16
z = x

========================================
Optimization Summary
========================================
Total statements: 3
Constants folded: 1
Dead code removed: 1
Final statements: 2

Optimizations Applied:
  ✓ Redundant computations eliminated
  ✓ Dead code detected and removed
  ✓ Strength reduction applied
  ✓ Copy propagation performed

========================================
Optimization Complete!
========================================
```

## 🔍 How It Works

### Optimization Pipeline

```
Input Code
    ↓
Step 1: Constant Folding
    ↓
Step 2: Strength Reduction
    ↓
Step 3: Copy Propagation
    ↓
Step 4: Dead Code Elimination
    ↓
Optimized Code
```

### Detailed Process

**Step 1: Constant Folding**
- Identifies constant expressions where **both operands are numeric constants**
- Example: `2 * 8` (both are constants)
- Evaluates them at compile time
- Result: `x = 16`
- Does NOT fold `x * 1` because `x` is a variable

**Step 2: Strength Reduction**
- Applies algebraic identities to simplify expressions
- Simplifies `y = x * 1` to `y = x` (multiplication by 1)
- Simplifies `z = y + 0` to `z = y` (addition of 0)
- Reduces computational complexity

**Step 3: Copy Propagation**
- Identifies simple copy assignments: `y = x` and `z = y`
- Substitutes variable copies in subsequent statements
- Replaces `z = y` with `z = x` (propagating through the chain)
- Preserves variable relationships

**Step 4: Dead Code Elimination**
- Analyzes variable usage throughout the program
- Identifies that `y` is assigned but never used in final output
- Marks `y` as dead code
- Removes the assignment to `y`

**Final Result:**
- `x = 16` (constant folded from `2 * 8`)
- `z = x` (simplified, propagated, with dead code removed)

## 🎨 Features

- ✅ **Constant Folding**: Eliminates redundant computations
- ✅ **Strength Reduction**: Optimizes algebraic expressions
- ✅ **Dead Code Detection**: Identifies unused variables
- ✅ **Step-by-Step Output**: Shows optimization process
- ✅ **Optimization Summary**: Displays statistics

## 🔄 Modifying Input Code

To test with different code, modify the `inputCode` vector in `main()`:

```cpp
vector<string> inputCode = {
    "x = 2 * 8",      // Your code here
    "y = x * 1",      // Add more statements
    "z = y + 0"       // As needed
};
```

### Supported Operations

- **Arithmetic**: `+`, `-`, `*`, `/`
- **Constants**: Integer values
- **Variables**: Single character or multi-character names

### Example Inputs

**Example 1: Multiple Optimizations**
```cpp
vector<string> inputCode = {
    "a = 5 * 4",
    "b = a + 0",
    "c = b * 1",
    "d = c - 0"
};
```

**Example 2: Zero Optimizations**
```cpp
vector<string> inputCode = {
    "x = 10 * 0",
    "y = x + 5",
    "z = y * 1"
};
```

## 🐛 Troubleshooting

### Compilation Errors

**Error: `g++: command not found`**
- **Solution**: Install C++ compiler (see Step 1 above)

**Error: `No such file or directory`**
- **Solution**: Ensure you're in the correct directory with `optimizer.cpp`

### Runtime Issues

**Issue: Program doesn't show expected optimizations**
- Check input format: `variable = operand1 operator operand2`
- Ensure proper spacing in statements
- Variables should be single tokens

## 📚 Theory Background

### Compiler Optimization

Code optimization is a crucial phase in compilation that improves program performance without changing its behavior.

**Types of Optimizations:**

1. **Constant Folding**
   - Compile-time evaluation of constant expressions
   - Reduces runtime computation overhead
   - Example: `3 + 5` → `8`

2. **Strength Reduction**
   - Replaces expensive operations with cheaper ones
   - Multiplication by 1 → No operation
   - Addition of 0 → No operation

3. **Dead Code Elimination**
   - Removes code that doesn't affect program output
   - Reduces code size and execution time
   - Improves cache performance

### Benefits

- ⚡ **Faster Execution**: Fewer operations at runtime
- 💾 **Smaller Code**: Removed unnecessary statements
- 🎯 **Better Performance**: Optimized instruction sequences
- 📊 **Reduced Complexity**: Simplified expressions

## 📄 Code Structure

```
optimizer.cpp
├── Statement struct         - Represents a code statement
├── CodeOptimizer class      - Main optimization engine
│   ├── parseStatement()     - Parses input statements
│   ├── constantFolding()    - Performs constant folding
│   ├── strengthReduction()  - Applies algebraic simplification
│   ├── deadCodeElimination()- Removes unused code
│   └── optimize()           - Orchestrates optimization
└── main()                   - Entry point and demo
```

## 🎓 Educational Value

This tool demonstrates:
- **Compiler Design**: Optimization phase implementation
- **Data Structures**: Symbol tables, statement representation
- **Algorithms**: Dead code analysis, constant propagation
- **Software Engineering**: Modular design, clean code

## 📄 License

Educational project for Compiler Design and Code Optimization coursework.

## 👨‍💻 Author

Created for learning compiler optimization techniques.

---

**Note**: This is a simplified optimizer for educational purposes. Production compilers use more sophisticated techniques including data flow analysis, loop optimization, and register allocation.
