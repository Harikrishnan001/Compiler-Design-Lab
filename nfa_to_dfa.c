// NFA to DFA conversion
// Input: Transition table of NFA (without epsilon transition)
// Output: Transition table of DFA
//
// A state is represented in form of an array.
// If q2={q3,q4,q5} then array representation is
//[3,3,4,5] with first element of the array as array length
// and the rest of the elements representing the component states

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _OUT_ // out parameter
#define STATE_QUEUE_SIZE 16
#define STATE_SEQ_LEN 21
#define STATES 10
#define MAX_SYMBOL_COUNT 5
#define MAX_STATES 10

// A queue for storing the states which are represented as mentioned above
int queue[STATE_QUEUE_SIZE][STATES];
int front = -1, rear = -1;

typedef struct TransitionTable
{
    int table[MAX_STATES][MAX_SYMBOL_COUNT][MAX_STATES+1];
    int state_count, symbol_count, final_state_count;
    int initial_state,  final_states[MAX_STATES];
    char symbols[MAX_SYMBOL_COUNT];
} TransitionTable_t;

int comp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

// Returns 0 if two states are equal e.g. {q0,q1,q2}=={q0,q1,q2}
int _equals(int* s1, int* s2)
{
    if (s1[0] != s2[0])
        return 0;
    for (int i = 1; i <= s1[0]; i++)
        if (s1[i] != s2[i])
            return 0;
    return 1;
}

void _enQueue(int* state)
{
    if (rear == STATE_QUEUE_SIZE)
    {
        printf("ERROR:State queue capacity full!\n");
        return;
    }
    for (int i = front; i <= rear; i++)
        if (i != -1 && _equals(queue[i], state))
            return;
    if (front == -1)
        front++;
    memcpy(queue[++rear], state, sizeof(int) * (state[0] + 1));
}

int* _deQueue()
{
    if (front == -1)
    {
        printf("ERROR:State queue empty!\n");
        return NULL;
    }
    int* state = (int*)malloc(sizeof(int) * (queue[rear][0] + 1));
    memcpy(state, queue[rear], sizeof(int) * (queue[rear][0] + 1));
    rear--;
    if (rear == -1)
        front = -1;
    return state;
}

int _symbol_index(const TransitionTable_t* automata, char input_symbol)
{
    for (int i = 0; i < automata->symbol_count; i++)
        if (automata->symbols[i] == input_symbol)
            return i;
    return -1;
}

int _state_contains(int* state, int elem)
{
    for (int i = 1; i <= state[0]; i++)
        if (state[i] == elem)
            return i;
    return 0;
}

// Transition function
int* delta(const TransitionTable_t* nfa, int* state, char input_symbol)
{
    int* result = (int*)malloc(sizeof(int) * (nfa->state_count + 1));
    result[0] = 0;
    for (int i = 1; i <= state[0]; i++)
    {
        int* s = nfa->table[state[i]][_symbol_index(nfa, input_symbol)];
        for (int j = 1; j <= s[0]; j++)
            if (!_state_contains(result, s[j]))
            {
                result[++result[0]] = s[j];
            }
    }
    qsort(result + 1, result[0], sizeof(int), comp);
    return result;
}

int _map_contains(int** map, int map_size, int* vec)
{
    for (int i = 0; i < map_size; i++)
    {
        if (map[i][0] == vec[0])
        {
            int size = 0;
            for (int j = 1; j <= map[i][0]; j++)
                if (map[i][j] != vec[j])
                    break;
                else
                    size++;
            if (size == vec[0])
                return 1;
        }
    }
    return 0;
}

int** make_dfa_transitiontable(const TransitionTable_t* nfa, TransitionTable_t _OUT_* dfa)
{
    dfa->initial_state = nfa->initial_state;
    dfa->symbol_count = nfa->symbol_count;
    memcpy(dfa->symbols, nfa->symbols, nfa->symbol_count);
    dfa->state_count = 0;

    int** map = (int**)malloc(sizeof(int*) * MAX_STATES);
    int* initial_state = (int*)malloc(sizeof(int) * 2);
    initial_state[0] = 1, initial_state[1] = nfa->initial_state;
    _enQueue(initial_state);

    while (front != -1) // Queue not empty
    {
        int* state = _deQueue();
        map[dfa->state_count] = (int*)malloc(sizeof(int) * (state[0] + 1));
        memcpy(map[dfa->state_count], state, sizeof(int) * (state[0] + 1));
        for (int i = 0; i < dfa->symbol_count; i++)
        {
            int* vec = delta(nfa, state, dfa->symbols[i]);
            memcpy(dfa->table[dfa->state_count][i], vec, sizeof(int) * (vec[0] + 1));
            if (!_map_contains(map, dfa->state_count + 1, vec))
            {
                _enQueue(vec);
            }
        }
        dfa->state_count++;
    }
    return map;
}

char* _format_state(const int* s)
{
    char* state = (char*)calloc(STATE_SEQ_LEN, sizeof(char));
    char temp[10];
    strcpy(state, "[");
    for (int j = 1; s != NULL && j <= s[0]; j++)
    {
        sprintf(temp, "q%d%c", s[j], j == s[0] ? ' ' : ',');
        strcat(state, temp);
    }
    strcat(state, "]");
    return state;
}

void print_dfa(const TransitionTable_t* dfa, int** map)
{
    printf("\n------------------------------------------------------------\n");
    printf("%-20s", "State");
    for (int i = 0; i < dfa->symbol_count; i++)
        printf("%-20c", dfa->symbols[i]);
    putchar('\n');
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < dfa->state_count; i++)
    {
        printf("%-20s", _format_state(map[i]));
        for (int j = 0; j < dfa->symbol_count; j++)
            printf("%-20s", _format_state(dfa->table[i][j])); // Something wrong?
        putchar('\n');
    }
    printf("------------------------------------------------------------\n");
}

int main()
{
    int c;
    TransitionTable_t nfa, dfa;

    // Read the transition table for nfa
    printf("Enter the number of states:");
    scanf("%d", &nfa.state_count);
    printf("Enter the starting state:");
    scanf("%d", &nfa.initial_state);
    printf("Enter the number of final states:");
    scanf("%d", &nfa.final_state_count);
    printf("Enter the final states:");
    for (int i = 0; i < nfa.final_state_count; i++)
        scanf("%d", &nfa.final_states[i]);
    printf("Enter the number of input symbols:");
    scanf("%d", &nfa.symbol_count);
    while ((getchar()) != '\n')
        ;
    printf("Enter the input symbols:");
    for (int i = 0; i < nfa.symbol_count; i++)
    {
        scanf("%c", &nfa.symbols[i]);
        getchar();
    }

    // Input transition table of nfa
    // Enter all elements in ascending order
    for (int i = 0; i < nfa.state_count; i++)
    {
        printf("\nEnter the transitions of q%d\n", i);
        for (int j = 0; j < nfa.symbol_count; j++)
        {
            printf("Number of transitions for %c:", nfa.symbols[j]);
            scanf("%d", &c);
            nfa.table[i][j][0] = c;
            if (c != 0)
            {
                printf("States:");
                for (int k = 1; k <= c; k++)
                    scanf("%d", &nfa.table[i][j][k]);
            }
        }
    }

    int** state_map = make_dfa_transitiontable(&nfa, &dfa);
    print_dfa(&dfa, state_map);
}
