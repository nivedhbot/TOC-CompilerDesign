# Regular Expression to DFA Converter

This program converts the regular expression **(a|b)\*abb** into its equivalent Deterministic Finite Automaton (DFA) and generates both a transition table and a visual diagram.

## 📋 Overview

**Input**: Regular Expression `(a|b)*abb`

**Output**: 
1. DFA Transition Table
2. DFA Diagram (PNG format)

The regular expression `(a|b)*abb` accepts all strings over the alphabet {a, b} that end with the substring "abb".

## 🎯 Regular Expression Explanation

- `(a|b)*` - Zero or more occurrences of 'a' or 'b'
- `abb` - Must end with the exact sequence "abb"

### Examples:
- ✅ **Accepted**: `abb`, `aabb`, `babb`, `ababb`, `aababb`, `bbabb`
- ❌ **Rejected**: `ab`, `abba`, `ba`, `aab`, `aba`

## 🔧 System Requirements & Installation

### Step 1: Install C Compiler

**Windows:**
1. Download and install MinGW-w64 or TDM-GCC
   - MinGW-w64: https://www.mingw-w64.org/downloads/
   - TDM-GCC: https://jmeubank.github.io/tdm-gcc/
2. Add the compiler's `bin` directory to your system PATH
3. Verify installation: Open Command Prompt and run `gcc --version`

**Linux (Ubuntu/Debian):**
```bash
sudo apt update
sudo apt install build-essential
gcc --version
```

**Linux (Fedora/RHEL):**
```bash
sudo dnf install gcc
gcc --version
```

**macOS:**
```bash
xcode-select --install
gcc --version
```

### Step 2: Install Graphviz (Required for PNG Generation)

**Windows:**
1. Download Graphviz installer from https://graphviz.org/download/
2. Run the installer (e.g., `graphviz-x.x.x-win64.exe`)
3. During installation, check "Add Graphviz to system PATH"
4. Restart Command Prompt
5. Verify installation: `dot -V`

**Linux (Ubuntu/Debian):**
```bash
sudo apt update
sudo apt install graphviz
dot -V
```

**Linux (Fedora/RHEL):**
```bash
sudo dnf install graphviz
dot -V
```

**macOS:**
```bash
brew install graphviz
dot -V
```

### Step 3: Verify Installation

Open terminal/command prompt and verify both tools are installed:

```bash
gcc --version
dot -V
```

You should see version information for both commands.

## 🚀 How to Run the Program

### Step 1: Navigate to Project Directory

```bash
cd e:/TOC/CascadeProjects/windsurf-project/RE_to_DFA_Converter
```

Or on Linux/macOS:
```bash
cd /path/to/RE_to_DFA_Converter
```

### Step 2: Compile the Program

**Windows:**
```bash
gcc index.c -o index.exe
```

**Linux/macOS:**
```bash
gcc index.c -o index
```

**Expected Output:** No errors. If compilation succeeds, you'll see no output.

### Step 3: Run the Executable

**Windows:**
```bash
./index.exe
```

Or simply:
```bash
index.exe
```

**Linux/macOS:**
```bash
./index
```

### Step 4: View Output Files

After successful execution, check the directory for:
- `dfa_diagram.dot` - DOT format file
- `dfa_output.png` - DFA visualization (open with any image viewer)

**To view PNG on Windows:**
```bash
start dfa_output.png
```

**To view PNG on Linux:**
```bash
xdg-open dfa_output.png
```

**To view PNG on macOS:**
```bash
open dfa_output.png
```

## 📋 Complete Execution Steps (Quick Reference)

```bash
# 1. Navigate to directory
cd RE_to_DFA_Converter

# 2. Compile
gcc index.c -o index.exe

# 3. Run
./index.exe

# 4. View output image
start dfa_output.png
```

## 📊 DFA Structure

### States

The DFA has **4 states**:

- **q0**: Initial state (no pattern matched yet)
- **q1**: After reading 'a' (first character of 'abb')
- **q2**: After reading 'ab' (two characters of 'abb')
- **q3**: After reading 'abb' (ACCEPTING STATE - complete pattern)

### Transition Table

```
+-------+-------+-------+
| State |   a   |   b   |
+-------+-------+-------+
|  q0   |  q1   |  q0   |
|  q1   |  q1   |  q2   |
|  q2   |  q1   | *q3*  |
| *q3*  |  q1   |  q0   |
+-------+-------+-------+
(* denotes accepting state)
```

### Transition Logic

**From q0 (Initial State):**
- On 'a' → go to q1 (start of potential "abb")
- On 'b' → stay in q0 (reset, no pattern started)

**From q1 (After 'a'):**
- On 'a' → stay in q1 (new potential "abb" starts)
- On 'b' → go to q2 (now have "ab")

**From q2 (After 'ab'):**
- On 'a' → go to q1 (reset to just 'a')
- On 'b' → go to q3 (completed "abb", ACCEPT!)

**From q3 (After 'abb' - Accepting):**
- On 'a' → go to q1 (start new potential "abb")
- On 'b' → go to q0 (reset completely)

## 📝 Example Output

```
========================================
Regular Expression to DFA Converter
========================================

Input Regular Expression: (a|b)*abb

Description: Accepts all strings ending with 'abb'
             over alphabet {a, b}

========================================
DFA Construction
========================================

Number of States: 4
Alphabet: {a, b}
Start State: q0
Accepting States: {q3}

State Descriptions:
  q0: Initial state - no pattern matched yet
  q1: After reading 'a' - first character of 'abb'
  q2: After reading 'ab' - two characters of 'abb'
  q3: After reading 'abb' - ACCEPTING STATE (complete pattern)

========================================
Output: DFA Transition Table
========================================

DFA Transition Table:
  +-------+-------+-------+
  | State |   a   |   b   |
  +-------+-------+-------+
  |  q0   |  q1   |  q0   |
  |  q1   |  q1   |  q2   |
  |  q2   |  q1   | *q3*  |
  | *q3*  |  q1   |  q0   |
  +-------+-------+-------+
  (* denotes accepting state)

========================================
Testing Strings
========================================

[Test 1] String: 'abb'
----------------------------------------

  Initial state: q0
  Transitions:
    q0 --(a)--> q1
    q1 --(b)--> q2
    q2 --(b)--> q3 [accepting]
  Final state: q3
  Result: ACCEPTED

[Test 2] String: 'aabb'
----------------------------------------

  Initial state: q0
  Transitions:
    q0 --(a)--> q1
    q1 --(a)--> q1
    q1 --(b)--> q2
    q2 --(b)--> q3 [accepting]
  Final state: q3
  Result: ACCEPTED

[Test 3] String: 'babb'
----------------------------------------

  Initial state: q0
  Transitions:
    q0 --(b)--> q0
    q0 --(a)--> q1
    q1 --(b)--> q2
    q2 --(b)--> q3 [accepting]
  Final state: q3
  Result: ACCEPTED

[Test 4] String: 'ababb'
----------------------------------------

  Initial state: q0
  Transitions:
    q0 --(a)--> q1
    q1 --(b)--> q2
    q2 --(a)--> q1
    q1 --(b)--> q2
    q2 --(b)--> q3 [accepting]
  Final state: q3
  Result: ACCEPTED

[Test 5] String: 'abba'
----------------------------------------

  Initial state: q0
  Transitions:
    q0 --(a)--> q1
    q1 --(b)--> q2
    q2 --(b)--> q3 [accepting]
    q3 --(a)--> q1
  Final state: q1
  Result: REJECTED

[Test 6] String: 'aababb'
----------------------------------------

  Initial state: q0
  Transitions:
    q0 --(a)--> q1
    q1 --(a)--> q1
    q1 --(b)--> q2
    q2 --(a)--> q1
    q1 --(b)--> q2
    q2 --(b)--> q3 [accepting]
  Final state: q3
  Result: ACCEPTED

========================================
Summary
========================================
  'abb': ACCEPTED ✓
  'aabb': ACCEPTED ✓
  'babb': ACCEPTED ✓
  'ababb': ACCEPTED ✓
  'abba': REJECTED ✗
  'aababb': ACCEPTED ✓

========================================
Generating DFA Visualization
========================================
DFA DOT file 'dfa_diagram.dot' created.
Converting DOT file to PNG...
✓ DFA diagram saved as 'dfa_output.png'

========================================
Conversion Complete!
========================================

Output Files:
  1. DFA Transition Table (displayed above)
  2. DFA Diagram: dfa_output.png
  3. DOT File: dfa_diagram.dot
```

## 🎨 Visualization Features

The generated DFA diagram includes:

- **Color-coded states**:
  - Light blue for regular states (q0, q1, q2)
  - Light green for accepting state (q3)
- **Clear transition arrows** with labeled symbols
- **Start arrow** indicating the initial state
- **Double circle** for accepting state
- **High resolution** (300 DPI) for printing
- **Professional layout** with optimal spacing

## 📁 Output Files

After running the program, you'll get:

1. **dfa_diagram.dot** - Graphviz DOT format file
2. **dfa_output.png** - Visual DFA diagram (PNG image)

## 🔄 How It Works

### DFA Construction Process

1. **State Definition**: Create states to track pattern matching progress
   - q0: No pattern matched
   - q1: Matched 'a'
   - q2: Matched 'ab'
   - q3: Matched 'abb' (accepting)

2. **Transition Function**: Define transitions for each state-symbol pair
   - Carefully handle pattern continuation and reset scenarios

3. **Accepting State**: Mark q3 as accepting (pattern complete)

4. **Validation**: Test strings by simulating DFA execution

## 🐛 Troubleshooting

### Graphviz Not Found

If you see:
```
✗ Error: Could not generate PNG.
```

**Solution**:
1. Install Graphviz from [graphviz.org](https://graphviz.org/download/)
2. Add Graphviz bin directory to your system PATH
3. Verify: `dot -V`

### Manual PNG Generation

```bash
dot -Tpng dfa_diagram.dot -o dfa_output.png
```

## 📚 Theory Background

### Deterministic Finite Automaton (DFA)

A DFA is a 5-tuple (Q, Σ, δ, q0, F) where:
- **Q**: Finite set of states {q0, q1, q2, q3}
- **Σ**: Input alphabet {a, b}
- **δ**: Transition function Q × Σ → Q
- **q0**: Start state
- **F**: Set of accepting states {q3}

### Why This DFA Works

The DFA tracks the longest suffix of the input that matches a prefix of "abb":
- When we see 'a', we might be starting "abb"
- When we see 'ab', we're one character away
- When we see 'abb', we accept
- Any deviation resets to the appropriate state

## 📄 License

Educational project for Theory of Computation (TOC) coursework.

## 👨‍💻 Author

Created for learning automata theory and compiler design.

---

**Note**: This implementation demonstrates the systematic conversion of a regular expression to its equivalent DFA, including complete transition table and visual representation.
