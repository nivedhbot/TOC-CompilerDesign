# Regular Expression to DFA Converter

This program converts regular expressions into Deterministic Finite Automata (DFA) and validates input strings against them. It provides step-by-step validation traces and generates visual representations using Graphviz.

## 📋 Overview

The program implements a DFA for the regular expression `(0|1)*01`, which accepts all binary strings ending with "01".

### Features

- ✅ **DFA Construction**: Converts RE `(0|1)*01` into a complete DFA
- ✅ **String Validation**: Tests input strings and shows acceptance/rejection
- ✅ **Step-by-Step Tracing**: Displays state transitions for each input symbol
- ✅ **Transition Table**: Shows complete DFA transition table
- ✅ **Visual Representation**: Generates high-quality PNG diagram using Graphviz
- ✅ **Extensible Design**: Structure supports adding new regular expressions

## 🔧 Prerequisites

- **C Compiler**: gcc, clang, or any C99-compatible compiler
- **Graphviz**: Required for generating DFA visualizations
  - Windows: Download from [graphviz.org](https://graphviz.org/download/)
  - Linux: `sudo apt-get install graphviz`
  - macOS: `brew install graphviz`

## 📦 Files

- `Strings.c` - Main program with general DFA framework
- `README.md` - This documentation file
- `dfa.dot` - Generated Graphviz DOT file (created at runtime)
- `output.png` - DFA visualization diagram (created at runtime)

## 🚀 Compilation

To compile the program, run:

```bash
gcc Strings.c -o String.exe
```

Or on Linux/macOS:

```bash
gcc Strings.c -o String
```

## 💻 Usage

Run the compiled program:

```bash
./String.exe
```

Or on Linux/macOS:

```bash
./String
```

## 📊 Program Output

The program performs the following operations:

### 1. DFA Information Display

- Shows the regular expression being tested
- Lists all DFA states and their roles
- Displays complete transition table

### 2. String Validation with Step-by-Step Tracing

Tests three strings: `1101`, `111`, `0001`

For each string, the program shows:

- Initial state
- Each state transition with input symbol
- Final state
- Acceptance/rejection result

### 3. Summary

- Quick overview of all test results

### 4. Visualization Generation

- Creates `dfa.dot` file in DOT format
- Converts to `output.png` using Graphviz (300 DPI)

## 🎯 DFA Details

### States

- **q0**: Initial state (start state)
- **q1**: State after reading '0' (waiting for '1' to complete "01")
- **q2**: Accepting state (string ends with "01")

### Transition Table

```
+-------+-------+-------+
| State |   0   |   1   |
+-------+-------+-------+
|  q0   |  q1   |  q0   |
|  q1   |  q1   | *q2*  |
| *q2*  |  q1   |  q0   |
+-------+-------+-------+
(* denotes accepting state)
```

### Transition Logic

- **From q0**:

  - On '0' → go to q1 (potential start of "01")
  - On '1' → stay in q0 (reset, waiting for '0')

- **From q1**:

  - On '0' → stay in q1 (still waiting for '1')
  - On '1' → go to q2 (completed "01", accept)

- **From q2**:
  - On '0' → go to q1 (new potential "01" sequence)
  - On '1' → go to q0 (reset)

## 📝 Example Output

```
========================================
DFA for Regular Expression: (0|1)*01
========================================

DFA States:
  q0: Initial state
  q1:
  q2:  (Accepting)

Transition Table:
  +-------+-------+-------+
  | State |   0   |   1   |
  +-------+-------+-------+
  |  q0   |  q1  |  q0  |
  |  q1   |  q1  | *q2  |
  | *q2   |  q1  |  q0  |
  +-------+-------+-------+
  (* denotes accepting state)

========================================
Testing Strings
========================================

[Test 1] String: '1101'
----------------------------------------

  Initial state: q0
  Transitions:
    q0 --(1)--> q0
    q0 --(1)--> q0
    q0 --(0)--> q1
    q1 --(1)--> q2 [accepting]
  Final state: q2
  Result: ACCEPTED

[Test 2] String: '111'
----------------------------------------

  Initial state: q0
  Transitions:
    q0 --(1)--> q0
    q0 --(1)--> q0
    q0 --(1)--> q0
  Final state: q0
  Result: REJECTED

[Test 3] String: '0001'
----------------------------------------

  Initial state: q0
  Transitions:
    q0 --(0)--> q1
    q1 --(0)--> q1
    q1 --(0)--> q1
    q1 --(1)--> q2 [accepting]
  Final state: q2
  Result: ACCEPTED

========================================
Summary
========================================
  '1101': ACCEPTED ✓
  '111': REJECTED ✗
  '0001': ACCEPTED ✓

========================================
Generating Visualization
========================================
DFA visualization file 'dfa.dot' created.
Converting DOT file to PNG...
✓ DFA visualization saved as 'output.png'

========================================
Done!
========================================
```

## 🎨 Visualization

The program generates a professional DFA diagram with:

- **Color-coded states**:
  - Light blue for regular states
  - Light green for accepting states
- **Clear labels**: State names and transition symbols
- **Title**: Shows the regular expression
- **High resolution**: 300 DPI for clear printing
- **Proper spacing**: Optimized layout for readability

## 🔄 Extending the Program

To add support for different regular expressions:

1. Create a new initialization function (e.g., `initDFA_YourPattern`)
2. Define the number of states and symbols
3. Set up the transition table
4. Mark accepting states
5. Call your initialization function in `main()`

Example structure:

```c
void initDFA_YourPattern(DFA* dfa) {
    strcpy(dfa->regex, "your_regex_here");
    dfa->num_states = X;
    dfa->num_symbols = Y;
    // ... set up transitions ...
}
```

## 🐛 Troubleshooting

### Graphviz Not Found

If you see an error about Graphviz:

```
✗ Error: Could not generate PNG.
```

**Solution**:

1. Install Graphviz from [graphviz.org](https://graphviz.org/download/)
2. Add Graphviz to your system PATH
3. Verify installation: `dot -V`

### Manual PNG Generation

If automatic conversion fails, manually convert the DOT file:

```bash
dot -Tpng dfa.dot -o output.png
```

## 📚 Theory Background

### What is a DFA?

A Deterministic Finite Automaton is a theoretical model of computation consisting of:

- A finite set of states
- An input alphabet
- A transition function
- A start state
- A set of accepting states

### Regular Expression: (0|1)\*01

- `(0|1)*` - Zero or more occurrences of 0 or 1
- `01` - Must end with the sequence "01"

### Test Cases Explained

- **1101**: ✓ Ends with "01"
- **111**: ✗ Does not end with "01"
- **0001**: ✓ Ends with "01"

## 📄 License

This is an educational project for learning automata theory and compiler design.

---

**Note**: This program demonstrates the conversion of a specific regular expression to DFA. The framework is designed to be extensible for other regular expressions with similar complexity.
