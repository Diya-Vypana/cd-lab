#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
int nfa[MAX][MAX][MAX]; // nfa[state][symbol][next_state]
int nfa_states, input_symbols;
int is_final[MAX];
int dfa[MAX][MAX]; // dfa[state][symbol] = next_state_index
int dfa_sets[MAX][MAX]; // dfa_sets[state][nfa_state] = 0 or 1
int dfa_state_count = 0;
char state_names[MAX][100]; // to store names like q0q1
// Check if a subset already exists in DFA states
int get_dfa_state_index(int subset[]) {
	for (int i = 0; i < dfa_state_count; i++) {
		int match = 1;
		for (int j = 0; j < nfa_states; j++) {
			if (dfa_sets[i][j] != subset[j]) {
				match = 0;
				break;
			}
		}
		if (match)
			return i;
	}
	return -1;
}
// Create string like "q0q1q2" from subset
void get_state_name(int subset[], char *name) {
	strcpy(name, "");
	for (int i = 0; i < nfa_states; i++) {
		if (subset[i]) {
			char part[10];
			sprintf(part, "q%d", i);
			strcat(name, part);
		}
	}
}
// Add a new DFA state and return its index
int add_dfa_state(int subset[]) {
	for (int i = 0; i < nfa_states; i++)
		dfa_sets[dfa_state_count][i] = subset[i];
	get_state_name(subset, state_names[dfa_state_count]);
	return dfa_state_count++;
}

void convert_nfa_to_dfa() {
	int queue[MAX], front = 0, rear = 0;
	int start[MAX] = {0};
	start[0] = 1; // starting from q0
	int start_index = add_dfa_state(start);
	queue[rear++] = start_index;
	while (front < rear) {
		int current = queue[front++];
		for (int sym = 0; sym < input_symbols; sym++) {
			int new_subset[MAX] = {0};
			for (int i = 0; i < nfa_states; i++) {
				if (dfa_sets[current][i]) {
					for (int j = 0; j < nfa_states; j++) {
						if (nfa[i][sym][j])
							new_subset[j] = 1;
					}
				}
			}
			int index = get_dfa_state_index(new_subset);
			if (index == -1) {
				index = add_dfa_state(new_subset);
				queue[rear++] = index;
			}
			dfa[current][sym] = index;
		}
	}
}
int main() {
	printf("Enter no. of states: ");
	scanf("%d", &nfa_states);
	printf("Enter no. of input symbols: ");
	scanf("%d", &input_symbols);
	for (int sym = 0; sym < input_symbols; sym++) {
		printf("Enter NFA matrix for input %d:\n", sym + 1);
		for (int i = 0; i < nfa_states; i++) {
			for (int j = 0; j < nfa_states; j++) {
				scanf("%d", &nfa[i][sym][j]);
			}
		}
	}

	convert_nfa_to_dfa();
// Print DFA transition table
	printf("\nDFA:\n");
	printf(" ");
	for (int sym = 0; sym < input_symbols; sym++) {
		printf("| Input %d ", sym + 1);
	}
	printf("|\n");
	printf("=====================================\n");
	for (int i = 0; i < dfa_state_count; i++) {
		printf("%-8s", state_names[i]);
		for (int sym = 0; sym < input_symbols; sym++) {
			printf("| %-8s", state_names[dfa[i][sym]]);
		}
		printf("|\n");
	}
	return 0;
}
