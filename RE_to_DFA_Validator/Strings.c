#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 10
#define MAX_TRANSITIONS 100

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

// Initialize DFA for RE = (0|1)*01
void initDFA_Pattern01(DFA* dfa) {
    strcpy(dfa->regex, "(0|1)*01");
    dfa->num_states = 3;
    dfa->num_symbols = 2;
    dfa->symbols[0] = '0';
    dfa->symbols[1] = '1';
    dfa->start_state = 0;
    
    // State names
    strcpy(dfa->state_names[0], "q0");
    strcpy(dfa->state_names[1], "q1");
    strcpy(dfa->state_names[2], "q2");
    
    // Accepting states
    dfa->accepting_states[0] = false;
    dfa->accepting_states[1] = false;
    dfa->accepting_states[2] = true;
    
    // Transition table
    // State 0: q0
    dfa->transition_table[0][0] = 1;  // q0 --0--> q1
    dfa->transition_table[0][1] = 0;  // q0 --1--> q0
    
    // State 1: q1
    dfa->transition_table[1][0] = 1;  // q1 --0--> q1
    dfa->transition_table[1][1] = 2;  // q1 --1--> q2
    
    // State 2: q2
    dfa->transition_table[2][0] = 1;  // q2 --0--> q1
    dfa->transition_table[2][1] = 0;  // q2 --1--> q0
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
    printf("Transition Table:\n");
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

int main() {
    DFA dfa;
    initDFA_Pattern01(&dfa);
    
    const char* test_strings[] = {"1101", "111", "0001"};
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    printf("========================================\n");
    printf("DFA for Regular Expression: %s\n", dfa.regex);
    printf("========================================\n");
    
    printf("\nDFA States:\n");
    for (int i = 0; i < dfa.num_states; i++) {
        printf("  %s: ", dfa.state_names[i]);
        if (i == dfa.start_state) {
            printf("Initial state");
        }
        if (dfa.accepting_states[i]) {
            printf(" (Accepting)");
        }
        printf("\n");
    }
    printf("\n");
    
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
    printf("Generating Visualization\n");
    printf("========================================\n");
    const char* dot_filename = "dfa.dot";
    generateDotFile(&dfa, dot_filename);
    printf("DFA visualization file '%s' created.\n", dot_filename);
    
    // Convert DOT file to PNG using Graphviz
    printf("Converting DOT file to PNG...\n");
    char command[256];
    snprintf(command, sizeof(command), "dot -Tpng %s -o output.png -Gdpi=300", dot_filename);
    int result = system(command);
    
    if (result == 0) {
        printf("✓ DFA visualization saved as 'output.png'\n");
    } else {
        printf("✗ Error: Could not generate PNG.\n");
        printf("  Make sure Graphviz is installed and 'dot' is in your PATH.\n");
        printf("  Manual conversion: dot -Tpng %s -o output.png\n", dot_filename);
    }
    
    printf("\n========================================\n");
    printf("Done!\n");
    printf("========================================\n");
    
    return 0;
}
