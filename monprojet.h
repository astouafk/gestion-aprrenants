#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUFFER 50

typedef struct {
    char identifiant[MAX_BUFFER];
    char motdepasse[MAX_BUFFER];
    int typeUtilisateur; 
    int etatUtilisateur; 
} Utilisateur;

void interfaceConnexion();
int verifierIdentifiants(const char *identifiant, const char *motdepasse, int *typeUtilisateur, int *etatUtilisateur);
void creerFichierAdminEtudiant();
void afficherBienvenueAdmin();
void afficherBienvenueEtudiant();
int verifierIdentifiants(const char *identifiant, const char *motdepasse, int *typeUtilisateur, int *etatUtilisateur);


void creerFichierAdminEtudiant() {
    FILE *fichier;
    fichier = fopen("logadminetu.txt", "w+"); 

    if (fichier != NULL) {
        fprintf(fichier, "admin passer123 1 1\n");
        fprintf(fichier, "admin2 passer456 1 1\n");
        for (int i = 1; i <= 3; i++) {
            for (int j = 1; j <= 10; j++) {
                fprintf(fichier, "etudiant%dL%d pass%dl%d 2 1\n", j, i, j, i);
            }
        }
        fclose(fichier);
    } else {
        printf("Impossible de créer le fichier logadminetu.txt.\n");
    }
}

void afficherBienvenueAdmin() {
    int choix;
    printf("\n");
    printf("***********Bienvenue dans l'interface Admin.***********\n");
    
    do {
        printf("** 1. Gestion des etudiants **\n");
        printf("** 2. Generation de fichier **\n");
        printf("** 3. Marquer les presences **\n");
        printf("** 4. Envoyer un message **\n");
        printf("** 5. Parametres **\n");
        printf("** 6. Quitter **\n");
        scanf("%d", &choix);
        if (choix < 1 || choix > 6) {
            printf("Choix invalide\n");
        }
        if (choix == 6) {
            while (getchar() != '\n'); 
            interfaceConnexion();
        }
        
    } while (choix != 6);
}

void afficherBienvenueEtudiant() {
    int ch;
    printf("\n");
    printf("***********Bienvenue dans votre Espace ETUDIANT.***********\n");
    printf("\n");
      do {
        printf("** 1. Marquer ma presence **\n");
        printf("** 2. Nombre de minutes d'absence **\n");
        printf("** 3. Mes Messages **\n");
        printf("** 4. Quitter **\n");
        scanf("%d", &ch);
        if (ch < 1 || ch > 4) {
            printf("Choix invalide\n");
        }
         if (ch == 4) {
            while (getchar() != '\n'); 
            interfaceConnexion();
        }
        
    } while (ch != 4);
    
}

int verifierIdentifiants(const char *identifiant, const char *motdepasse, int *typeUtilisateur, int *etatUtilisateur) {
    FILE *fichier;
    fichier = fopen("logadminetu.txt", "r");

    if (fichier != NULL) {
        Utilisateur utilisateur;
        while (fscanf(fichier, "%s %s %d %d", utilisateur.identifiant, utilisateur.motdepasse, &utilisateur.typeUtilisateur, &utilisateur.etatUtilisateur) == 4) {
            if (strcmp(utilisateur.identifiant, identifiant) == 0 && strcmp(utilisateur.motdepasse, motdepasse) == 0) {
                *typeUtilisateur = utilisateur.typeUtilisateur;
                *etatUtilisateur = utilisateur.etatUtilisateur;
                fclose(fichier);
                return 1; 
            }
        }
        fclose(fichier);
    }

    return 0; 
}

void interfaceConnexion() {
    char identifiant[MAX_BUFFER];
    char *motdepasse;
    int typeUtilisateur, etatUtilisateur;
    int identifiantsCorrects = 0;

    while (!identifiantsCorrects) {
        printf("\n");
        printf("******************** INTERFACE DE CONNECTION ****************\n");
        printf("\n");
        printf("Identifiant : ");
        if (fgets(identifiant, MAX_BUFFER, stdin) != NULL) {
            identifiant[strcspn(identifiant, "\n")] = '\0'; 
        }

        
        if (strlen(identifiant) == 0) {
            printf("L'identifiant est obligatoire. Veuillez saisir un identifiant.\n");
            continue; // je reviens à ma boucle ci dessus pour new identifiant
        }

        motdepasse = getpass("Mot de passe : ");

        if (verifierIdentifiants(identifiant, motdepasse, &typeUtilisateur, &etatUtilisateur)) {
            if (etatUtilisateur == 1) { 
                identifiantsCorrects = 1;
                if (typeUtilisateur == 1) {
                    afficherBienvenueAdmin();
                } else if (typeUtilisateur == 2) {
                    afficherBienvenueEtudiant();
                }
            } else {
                printf("Votre compte est bloqué. Veuillez contacter l'administrateur.\n");
            }
        } else {
            printf("Identifiants incorrects. Veuillez réessayer.\n");
        }
    }
}



