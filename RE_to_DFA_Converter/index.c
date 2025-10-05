#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 10

// Structure to represent a DFA
typedef struct {
    int num_states;
    int num_symbols;
    char symbols[MAX_SYMBOLS];
    int transition_table[MAX_STATES][MAX_SYMBOLS];
    int start_state;
    bool accepting_states[MAX_STATES];
    char state_names[MAX_STATES][20];
    char regex[100];
} DFA;

// Initialize DFA for RE = (a|b)*abb
void initDFA_Pattern_abb(DFA* dfa) {
    strcpy(dfa->regex, "(a|b)*abb");
    dfa->num_states = 4;
    dfa->num_symbols = 2;
    dfa->symbols[0] = 'a';
    dfa->symbols[1] = 'b';
    dfa->start_state = 0;
    
    // State names
    strcpy(dfa->state_names[0], "q0");
    strcpy(dfa->state_names[1], "q1");
    strcpy(dfa->state_names[2], "q2");
    strcpy(dfa->state_names[3], "q3");
    
    // Accepting states
    dfa->accepting_states[0] = false;
    dfa->accepting_states[1] = false;
    dfa->accepting_states[2] = false;
    dfa->accepting_states[3] = true;  // q3 is accepting state
    
    // Transition table for (a|b)*abb
    // State 0: q0 (initial state)
    dfa->transition_table[0][0] = 1;  // q0 --a--> q1
    dfa->transition_table[0][1] = 0;  // q0 --b--> q0
    
    // State 1: q1 (after reading 'a')
    dfa->transition_table[1][0] = 1;  // q1 --a--> q1
    dfa->transition_table[1][1] = 2;  // q1 --b--> q2
    
    // State 2: q2 (after reading 'ab')
    dfa->transition_table[2][0] = 1;  // q2 --a--> q1
    dfa->transition_table[2][1] = 3;  // q2 --b--> q3
    
    // State 3: q3 (accepting state - after reading 'abb')
    dfa->transition_table[3][0] = 1;  // q3 --a--> q1
    dfa->transition_table[3][1] = 0;  // q3 --b--> q0
}

// Get symbol index
int getSymbolIndex(DFA* dfa, char symbol) {
    for (int i = 0; i < dfa->num_symbols; i++) {
        if (dfa->symbols[i] == symbol) {
            return i;
        }
    }
    return -1;
}

// Validate string with step-by-step output
bool validateString(DFA* dfa, const char* str) {
    int current_state = dfa->start_state;
    
    printf("\n  Initial state: %s\n", dfa->state_names[current_state]);
    printf("  Transitions:\n");
    
    for (int i = 0; str[i] != '\0'; i++) {
        int symbol_idx = getSymbolIndex(dfa, str[i]);
        if (symbol_idx == -1) {
            printf("  Invalid character '%c' in input\n", str[i]);
            return false;
        }
        
        int next_state = dfa->transition_table[current_state][symbol_idx];
        printf("    %s --(%c)--> %s", 
               dfa->state_names[current_state], 
               str[i], 
               dfa->state_names[next_state]);
        
        if (dfa->accepting_states[next_state]) {
            printf(" [accepting]");
        }
        printf("\n");
        
        current_state = next_state;
    }
    
    printf("  Final state: %s\n", dfa->state_names[current_state]);
    bool accepted = dfa->accepting_states[current_state];
    printf("  Result: %s\n", accepted ? "ACCEPTED" : "REJECTED");
    
    return accepted;
}

// Generate Graphviz DOT file
void generateDotFile(DFA* dfa, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Error creating DOT file");
        exit(EXIT_FAILURE);
    }
    
    fprintf(file, "digraph DFA {\n");
    fprintf(file, "    rankdir=LR;\n");
    fprintf(file, "    graph [pad=\"0.5\", nodesep=\"1.2\", ranksep=\"2.0\", bgcolor=\"white\"];\n");
    fprintf(file, "    node [fontname=\"Arial\", fontsize=14, style=filled, fillcolor=\"lightblue\"];\n");
    fprintf(file, "    edge [fontname=\"Arial\", fontsize=12, arrowsize=0.8];\n");
    fprintf(file, "    labelloc=\"t\";\n");
    fprintf(file, "    label=\"DFA for Regular Expression: %s\";\n", dfa->regex);
    fprintf(file, "    fontsize=18;\n");
    fprintf(file, "    fontname=\"Arial Bold\";\n\n");
    
    // Initial arrow
    fprintf(file, "    node [shape=point, width=0]; start;\n");
    fprintf(file, "    start -> %s [label=\"start\"];\n\n", dfa->state_names[dfa->start_state]);
    
    // Define all states
    for (int i = 0; i < dfa->num_states; i++) {
        if (dfa->accepting_states[i]) {
            fprintf(file, "    %s [shape=doublecircle, fixedsize=true, width=1.0, fillcolor=\"lightgreen\"];\n", 
                    dfa->state_names[i]);
        } else {
            fprintf(file, "    %s [shape=circle, fixedsize=true, width=1.0];\n", 
                    dfa->state_names[i]);
        }
    }
    fprintf(file, "\n");
    
    // Add transitions
    for (int i = 0; i < dfa->num_states; i++) {
        for (int j = 0; j < dfa->num_symbols; j++) {
            int next_state = dfa->transition_table[i][j];
            
            // Check if this is a self-loop
            if (i == next_state) {
                fprintf(file, "    %s -> %s [label=\"%c\", style=bold];\n",
                        dfa->state_names[i],
                        dfa->state_names[next_state],
                        dfa->symbols[j]);
            } else {
                fprintf(file, "    %s -> %s [label=\"%c\"];\n",
                        dfa->state_names[i],
                        dfa->state_names[next_state],
                        dfa->symbols[j]);
            }
        }
    }
    
    fprintf(file, "}\n");
    fclose(file);
}

// Print transition table
void printTransitionTable(DFA* dfa) {
    printf("DFA Transition Table:\n");
    printf("  +-------+");
    for (int i = 0; i < dfa->num_symbols; i++) {
        printf("-------+");
    }
    printf("\n");
    
    printf("  | State |");
    for (int i = 0; i < dfa->num_symbols; i++) {
        printf("   %c   |", dfa->symbols[i]);
    }
    printf("\n");
    
    printf("  +-------+");
    for (int i = 0; i < dfa->num_symbols; i++) {
        printf("-------+");
    }
    printf("\n");
    
    for (int i = 0; i < dfa->num_states; i++) {
        if (dfa->accepting_states[i]) {
            printf("  | *%-4s |", dfa->state_names[i]);
        } else {
            printf("  |  %-4s |", dfa->state_names[i]);
        }
        
        for (int j = 0; j < dfa->num_symbols; j++) {
            int next = dfa->transition_table[i][j];
            if (dfa->accepting_states[next]) {
                printf(" *%-4s|", dfa->state_names[next]);
            } else {
                printf("  %-4s|", dfa->state_names[next]);
            }
        }
        printf("\n");
    }
    
    printf("  +-------+");
    for (int i = 0; i < dfa->num_symbols; i++) {
        printf("-------+");
    }
    printf("\n");
    printf("  (* denotes accepting state)\n\n");
}

// Print state descriptions
void printStateDescriptions(DFA* dfa) {
    printf("\nState Descriptions:\n");
    printf("  q0: Initial state - no pattern matched yet\n");
    printf("  q1: After reading 'a' - first character of 'abb'\n");
    printf("  q2: After reading 'ab' - two characters of 'abb'\n");
    printf("  q3: After reading 'abb' - ACCEPTING STATE (complete pattern)\n\n");
}

int main() {
    DFA dfa;
    initDFA_Pattern_abb(&dfa);
    
    // Test strings
    const char* test_strings[] = {"abb", "aabb", "babb", "ababb", "abba", "aababb"};
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    printf("========================================\n");
    printf("Regular Expression to DFA Converter\n");
    printf("========================================\n");
    printf("\nInput Regular Expression: %s\n", dfa.regex);
    printf("\nDescription: Accepts all strings ending with 'abb'\n");
    printf("             over alphabet {a, b}\n");
    
    printf("\n========================================\n");
    printf("DFA Construction\n");
    printf("========================================\n");
    
    printf("\nNumber of States: %d\n", dfa.num_states);
    printf("Alphabet: {");
    for (int i = 0; i < dfa.num_symbols; i++) {
        printf("%c", dfa.symbols[i]);
        if (i < dfa.num_symbols - 1) printf(", ");
    }
    printf("}\n");
    printf("Start State: %s\n", dfa.state_names[dfa.start_state]);
    printf("Accepting States: {");
    bool first = true;
    for (int i = 0; i < dfa.num_states; i++) {
        if (dfa.accepting_states[i]) {
            if (!first) printf(", ");
            printf("%s", dfa.state_names[i]);
            first = false;
        }
    }
    printf("}\n");
    
    printStateDescriptions(&dfa);
    
    printf("========================================\n");
    printf("Output: DFA Transition Table\n");
    printf("========================================\n\n");
    
    printTransitionTable(&dfa);
    
    printf("========================================\n");
    printf("Testing Strings\n");
    printf("========================================\n");
    
    bool results[num_tests];
    for (int i = 0; i < num_tests; i++) {
        const char* str = test_strings[i];
        printf("\n[Test %d] String: '%s'\n", i+1, str);
        printf("----------------------------------------\n");
        results[i] = validateString(&dfa, str);
    }
    
    printf("\n========================================\n");
    printf("Summary\n");
    printf("========================================\n");
    for (int i = 0; i < num_tests; i++) {
        printf("  '%s': %s\n", test_strings[i], 
               results[i] ? "ACCEPTED ✓" : "REJECTED ✗");
    }
    
    // Generate DOT file
    printf("\n========================================\n");
    printf("Generating DFA Visualization\n");
    printf("========================================\n");
    const char* dot_filename = "dfa_diagram.dot";
    generateDotFile(&dfa, dot_filename);
    printf("DFA DOT file '%s' created.\n", dot_filename);
    
    // Convert DOT file to PNG using Graphviz
    printf("Converting DOT file to PNG...\n");
    char command[256];
    snprintf(command, sizeof(command), "dot -Tpng %s -o dfa_output.png -Gdpi=300", dot_filename);
    int result = system(command);
    
    if (result == 0) {
        printf("✓ DFA diagram saved as 'dfa_output.png'\n");
    } else {
        printf("✗ Error: Could not generate PNG.\n");
        printf("  Make sure Graphviz is installed and 'dot' is in your PATH.\n");
        printf("  Manual conversion: dot -Tpng %s -o dfa_output.png\n", dot_filename);
    }
    
    printf("\n========================================\n");
    printf("Conversion Complete!\n");
    printf("========================================\n");
    printf("\nOutput Files:\n");
    printf("  1. DFA Transition Table (displayed above)\n");
    printf("  2. DFA Diagram: dfa_output.png\n");
    printf("  3. DOT File: %s\n", dot_filename);
    
    return 0;
}
