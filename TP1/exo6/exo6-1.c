#include <stdio.h> // Bibliothèque standard du C utilisée pour les opérations d'entrée/sortie
#include <stdlib.h> // Bibliothèque standard du C utilisée pour la gestion de la mémoire dynamique, le contrôle des processus, la conversion de types et diverses autres fonctions utilitaires
#include <string.h> // Cette bibliothèque standard du C est utilisée pour manipuler des chaînes de caractères et des blocs de mémoire

#define MAX_LINE_LENGTH 1024

// Fonction vérifiant si une ligne correspond à la regex ^if.*n$
int verifier_regex(const char *ligne) {
    int longueur_chaine = strlen(ligne);

    // Vérifie si la ligne commence par "if"
    if (longueur_chaine < 2 || ligne[0] != 'i' || ligne[1] != 'f') {
        return 0;
    }

    // Vérifie si la ligne se termine par 'n' (en ignorant le '\n' final)
    if (longueur_chaine < 3 || ligne[longueur_chaine - 2] != 'n') {
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char ligne[MAX_LINE_LENGTH];
    int count = 0;

    // Lit le fichier ligne par ligne
    while (fgets(ligne, sizeof(ligne), file)) {
        // Vérifie si la ligne correspond à la regex
        if (verifier_regex(ligne)) {
            count++;
        }
    }

    fclose(file);

    printf("Nombre de lignes correspondantes au regex ˆif.*n$ : %d\n", count);
    return 0;
}

/*
    Commandes pour l'exécution

    gcc -o exo6-1 exo6-1.c
    ./exo6-1 /etc/bash.bashrc

    Pour l'exécuter avec un fichier texte sur notre ordinateur
    ./exo6-1 /home/broly/Bureau/source/Fichiers/sample.txt

*/