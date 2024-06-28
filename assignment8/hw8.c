// name: Kaustubha Eluri
// email: eluri.k@northeastern.edu

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAXSTRING 200
#define TABLE_SIZE 400

// finite state machine states
#define STARTSTATE 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define ACCEPTSTATE 10
#define ERRORSTATE 11

// check if a character c is a digit
bool isDigit(char c) {
    return ('0' <= c && c <= '9');
}

// append character c to string s
void appendChar(char* s, char c) {
    char charToStr[2];           // convert char to string
    charToStr[0] = c;
    charToStr[1] = '\0';         // put NUL to terminate string of one character
    strcat(s, charToStr);
}

// Hash table node
typedef struct Node {
    char city_state[MAXSTRING];
    int population;
    struct Node* next;
} Node;

// Initialize hash tables
Node* hashTable1[TABLE_SIZE];
Node* hashTable2[TABLE_SIZE];
Node* hashTable3[TABLE_SIZE];

unsigned int hash_function_1(const char* key) {
    return strlen(key) % TABLE_SIZE;
}

unsigned int hash_function_2(const char* key) {
    unsigned int sum = 0;
    while (*key) {
        sum += (unsigned char)(*key);
        key++;
    }
    return sum % TABLE_SIZE;
}

unsigned int hash_function_3(const char* key) {
    if (strlen(key) < 2) return 0;
    return ((unsigned char)key[0] * (unsigned char)key[1]) % TABLE_SIZE;
}

void insert(Node* hashTable[], const char* city_state, int population, unsigned int (*hash_function)(const char*)) {
    unsigned int hashIndex = hash_function(city_state);
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->city_state, city_state);
    newNode->population = population;
    newNode->next = hashTable[hashIndex];
    hashTable[hashIndex] = newNode;
}

void print_hash_table(Node* hashTable[], const char* name) {
    printf("\n%s:\n", name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        if (current) {
            printf("Index %d:\n", i);
            while (current) {
                printf("\t%s: %d\n", current->city_state, current->population);
                current = current->next;
            }
        }
    }
}

void free_hash_table(Node* hashTable[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

int main() {
    char inputLine[MAXSTRING];   // temporary string to hold input line
    char cityStr[MAXSTRING];     // city name
    int lineNum;                 // line number (city rank)
    int popInt;                  // population
    int state;                   // FSM state
    int nextChar;                // index of next character in input string
    char temp[MAXSTRING];        // temp string to build up extracted strings from input characters

    FILE* fp;
    fp = fopen("pop.csv", "r");

    if (fp != NULL) {
        fgets(inputLine, MAXSTRING, fp); // prime the pump for the first line

        // ***** BEGIN FINTITE STATE MACHINE *****
        while (feof(fp) == 0) {
            nextChar = 0;
            state = STARTSTATE;
            strcpy(temp, "");       // temp = ""
            strcpy(cityStr, "");    // clear cityStr

            if (nextChar >= strlen(inputLine)) {
                // if no input string then go to ERRORSTATE
                state = ERRORSTATE;
            }

            while ((state != ERRORSTATE) && (state != ACCEPTSTATE)) {
                switch (state) {
                    case STARTSTATE:
                        // look a digit to confirm a valid line
                        if (isDigit(inputLine[nextChar])) {
                            state = S1;
                            appendChar(temp, inputLine[nextChar]);
                        } else {
                            state = ERRORSTATE;
                        }
                        break;
                    case S1:
                        if (isDigit(inputLine[nextChar])) {
                            appendChar(temp, inputLine[nextChar]);
                        } else if (inputLine[nextChar] == ',') {
                            state = S2;
                            lineNum = atoi(temp); // convert line number to integer
                            strcpy(temp, ""); // reset temp
                        } else {
                            state = ERRORSTATE;
                        }
                        break;
                    case S2:
                        if (inputLine[nextChar] == '"') {
                            state = S3;
                        } else {
                            state = ERRORSTATE;
                        }
                        break;
                    case S3:
                        if (inputLine[nextChar] != '"') {
                            appendChar(cityStr, inputLine[nextChar]);
                        } else {
                            state = S4;
                        }
                        break;
                    case S4:
                        if (inputLine[nextChar] == ',') {
                            state = S5;
                        } else {
                            state = ERRORSTATE;
                        }
                        break;
                    case S5:
                        if (inputLine[nextChar] == '"') {
                            state = S6;
                        } else if (inputLine[nextChar] == '(') {
                            state = ACCEPTSTATE;
                            popInt = 0; // population is zero
                        } else {
                            state = ERRORSTATE;
                        }
                        break;
                    case S6:
                        if (isDigit(inputLine[nextChar])) {
                            appendChar(temp, inputLine[nextChar]);
                        } else if (inputLine[nextChar] == ',' || inputLine[nextChar] == '"') {
                            // handle commas in the population number
                            // if we encounter a comma, we continue appending digits
                            // if we encounter a double quote, we finalize the population
                            if (inputLine[nextChar] == '"') {
                                state = ACCEPTSTATE;
                                // remove commas from temp and convert to integer
                                char popStr[MAXSTRING];
                                int popStrIndex = 0;
                                for (int i = 0; i < strlen(temp); i++) {
                                    if (temp[i] != ',') {
                                        popStr[popStrIndex++] = temp[i];
                                    }
                                }
                                popStr[popStrIndex] = '\0';
                                popInt = atoi(popStr);
                            }
                        } else {
                            state = ERRORSTATE;
                        }
                        break;
                    case ACCEPTSTATE:
                        // nothing to do - we are done!
                        break;
                    default:
                        state = ERRORSTATE;
                        break;
                } // end switch

                // advance input
                nextChar++;

            } // end while state machine loop

            // ***** END FINITE STATE MACHINE *****

            // insert into hash tables
            insert(hashTable1, cityStr, popInt, hash_function_1);
            insert(hashTable2, cityStr, popInt, hash_function_2);
            insert(hashTable3, cityStr, popInt, hash_function_3);

            // get next line
            fgets(inputLine, MAXSTRING, fp);

        } // end while file input loop

        fclose(fp);

        // Print hash tables
        print_hash_table(hashTable1, "Hash Table 1");
        print_hash_table(hashTable2, "Hash Table 2");
        print_hash_table(hashTable3, "Hash Table 3");

        // Free hash tables
        free_hash_table(hashTable1);
        free_hash_table(hashTable2);
        free_hash_table(hashTable3);

    } else {
        printf("File not found!\n");
    }

    return 0;
}
