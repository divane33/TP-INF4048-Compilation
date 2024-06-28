#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include <string.h> 

#define MAX_EXPR_LENGTH 1024

// Structure de noeud pour la pile
typedef struct Node {
    int data;
    struct Node *suivant;
} Node;

// Fonction pour pousser un élément sur la pile
void push(Node **sommet, int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->suivant = *sommet;
    *sommet = new_node;
}

// Fonction pour retirer un élément de la pile
int pop(Node **sommet) {
    if (*sommet == NULL) {
        fprintf(stderr, "Il y a dépassement de la pile\n");
        exit(EXIT_FAILURE);
    }
    Node *temp = *sommet;
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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Utilisez: %s <nom_fichier>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fichier = fopen(argv[1], "r");
    if (!fichier) {
        fprintf(stderr, "Erreur: Impossible d'ouvrir le fichier %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    char ligne[MAX_EXPR_LENGTH];
    while (fgets(ligne, sizeof(ligne), fichier)) {
        ligne[strcspn(ligne, "\r\n")] = '\0';  // Supprimer les caractères de fin de ligne

       // printf("Ligne lue : %s\n", ligne);

        char *token = strtok(ligne, " ");
        while (token != NULL) {
            printf("Expression : %s\n", token);
            printf("Evaluation avec aucune priorité : %d\n", eval_no_priority(token));
            printf("Evaluation avec priorité : %d\n", eval_with_priority(token));
            token = strtok(NULL, " ");
        }
    }

    fclose(fichier);
    return 0;
}
