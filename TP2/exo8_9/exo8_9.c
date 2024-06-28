#include <stdio.h> // Bibliothèque standard du C utilisée pour les opérations d'entrée/sortie
#include <stdlib.h> // Bibliothèque standard du C utilisée pour la gestion de la mémoire dynamique, le contrôle des processus, la conversion de types et diverses autres fonctions utilitaires
#include <ctype.h> // Cette bibliothèque standard du C est utilisée pour la classification et la transformation des caractères
#include <string.h> // Cette bibliothèque standard du C est utilisée pour manipuler des chaînes de caractères et des blocs de mémoire

#define MAX_EXPR_LENGTH 1024

// Ici, on défini la structure que aura la pile
typedef struct Node {
    int data;
    struct Node *suivant;
} Node;

// Fonction pour pousser un élément sur la pile
void push(Node **sommet, int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire \n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->suivant = *sommet;
    *sommet = new_node;
}

// Fonction pour retirer un élément de la pile
int pop(Node **sommet) {
    if (*sommet == NULL) {
        fprintf(stderr, "Il y'a dépassement de la pile\n");
        exit(EXIT_FAILURE);
    }
    Node *temp = *sommet; // temp est une variable de type Node * qui pointe vers la même valeur que celle pointée par *sommet
    int data = temp->data;
    *sommet = (*sommet)->suivant;
    free(temp);
    return data;
}

// Fonction pour vérifier si un caractère est un opérateur
int is_operator(char ch) {
    return ch == '+' || ch == '*';
}

// Fonction pour évaluer une expression sans priorité des opérateurs
int eval_no_priority(const char *expr) {
    int resultat = 0;
    int num = 0;
    char last_op = '+';

    for (int i = 0; i < strlen(expr); i++) {
        if (isdigit(expr[i])) {
            num = num * 10 + (expr[i] - '0');
        } else if (is_operator(expr[i])) {
            if (last_op == '+') {
                resultat += num;
            } else if (last_op == '*') {
                resultat *= num;
            }
            last_op = expr[i];
            num = 0;
        }
    }
    // Appliquer la dernière opération
    if (last_op == '+') {
        resultat += num;
    } else if (last_op == '*') {
        resultat *= num;
    }
    return resultat;
}

// Fonction pour évaluer une expression avec la priorité des opérateurs
int eval_with_priority(const char *expr) {
    Node *values = NULL;  // Pile pour les valeurs
    Node *ops = NULL;     // Pile pour les opérateurs

    for (int i = 0; i < strlen(expr); i++) {
        if (isdigit(expr[i])) {
            int num = 0;
            while (i < strlen(expr) && isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            i--;
            push(&values, num);
        } else if (expr[i] == '+') {
            while (ops != NULL && ops->data == '*') {
                int val2 = pop(&values);
                int val1 = pop(&values);
                push(&values, val1 * val2);
                pop(&ops);
            }
            push(&ops, expr[i]);
        } else if (expr[i] == '*') {
            push(&ops, expr[i]);
        }
    }

    while (ops != NULL) {
        int val2 = pop(&values);
        int val1 = pop(&values);
        char op = pop(&ops);
        if (op == '+') {
            push(&values, val1 + val2);
        } else if (op == '*') {
            push(&values, val1 * val2);
        }
    }

    return pop(&values);
}

int main() {
    char expr[MAX_EXPR_LENGTH];

    printf("Veuillez entrer une expression arithmétique s'il vous plaît: ");
    scanf("%s", expr);

    printf("Evaluation avec aucune priorité: %d\n", eval_no_priority(expr));
    printf("Evaluation avec priorité: %d\n", eval_with_priority(expr));

    return 0;
}


/*
    Commandes pour l'exécution de notre code
    gcc -o exo8_9 exo8_9.c
    ./exo8_9
*/