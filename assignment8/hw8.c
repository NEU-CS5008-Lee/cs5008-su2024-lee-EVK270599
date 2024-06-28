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

typedef struct Node {
    char city[MAXSTRING];
    int population;
    struct Node* next;
} Node;

Node* hashTable1[TABLE_SIZE];
Node* hashTable2[TABLE_SIZE];
Node* hashTable3[TABLE_SIZE];

// check if a character c is a digit
bool isDigit(char c) {
    return ('0' <= c && c <= '9');
}

// append character c to string s
void appendChar(char* s, char c) {
    char charToStr[2];           // convert char to string
    charToStr[0] = c;
    charToStr[1] = '\0';          // put NUL to terminate string of one character
    strcat(s, charToStr);
}

// hash function 1: length of the city/state string (modulo size of table)
int hashFunction1(char* str) {
    return strlen(str) % TABLE_SIZE;
}

// hash function 2: sum of the character codes of the city/state string (modulo size of table)
int hashFunction2(char* str) {
    int sum = 0;
    while (*str) {
        sum += *str++;
    }
    return sum % TABLE_SIZE;
}

// hash function 3: product of the first 2 character codes in city/state string (modulo size of table)
int hashFunction3(char* str) {
    if (strlen(str) < 2) return 0; // handle short strings
    return (str[0] * str[1]) % TABLE_SIZE;
}

void insert(Node* table[], int index, char* city, int population) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->city, city);
    newNode->population = population;
    newNode->next = table[index];
    table[index] = newNode;
}

void printHashTable(Node* table[], char* tableName) {
    printf("\n***** %s *****\n", tableName);
    printf("==========================\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i]) {
            printf("TABLE[%d]:\n", i);
            Node* current = table[i];
            while (current) {
                printf("key/value: [%s] / [%d]\n", current->city, current->population);
                current = current->next;
            }
        }
    }
}

int main () {
    char inputLine[MAXSTRING];   // temporary string to hold input line
    char cityStr[MAXSTRING];     // city name
    int lineNum;                 // line number (city rank)
    int popInt;                  // population
    int state;                   // FSM state
    int nextChar;                // index of next character in input string
    char temp[MAXSTRING];        // temp string to build up extracted strings from input characters
    
    FILE* fp;
    fp = fopen("pop.csv","r");

    if (fp != NULL) {
        fgets(inputLine, MAXSTRING, fp); // prime the pump for the first line

        // Initialize hash tables
        memset(hashTable1, 0, sizeof(hashTable1));
        memset(hashTable2, 0, sizeof(hashTable2));
        memset(hashTable3, 0, sizeof(hashTable3));

        while (feof(fp) == 0) {
            nextChar = 0;
            state = STARTSTATE; 
            strcpy(temp,"");       // temp = ""
            strcpy(cityStr,"");    // clear cityStr

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

            if (state == ACCEPTSTATE) {
                int index1 = hashFunction1(cityStr);
                int index2 = hashFunction2(cityStr);
                int index3 = hashFunction3(cityStr);

                insert(hashTable1, index1, cityStr, popInt);
                insert(hashTable2, index2, cityStr, popInt);
                insert(hashTable3, index3, cityStr, popInt);
            }

            // get next line
            fgets(inputLine, MAXSTRING, fp);
        } // end while file input loop

        fclose(fp);

        // Print out the contents of the hash tables
        printHashTable(hashTable1, "HASH TABLE 1");
        printHashTable(hashTable2, "HASH TABLE 2");
        printHashTable(hashTable3, "HASH TABLE 3");

    } else {
        printf("File not found!\n");
    }

    return 0;
}
