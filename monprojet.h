#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
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

void gestionClasses();

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
        printf("** 3. Gestion des classes **\n");
        printf("** 4. Marquer les presences **\n");
        printf("** 5. Envoyer un message **\n");
        printf("** 6. Parametres **\n");
        printf("** 7. Quitter **\n");
        scanf("%d", &choix);
        if (choix < 1 || choix > 7) {
            printf("Choix invalide\n");
        }
        if (choix == 7) {
            while (getchar() != '\n'); 
            interfaceConnexion();
        }
        if (choix == 3) {
            gestionClasses();
        }
        
    } while (choix != 7);
}

void gestionClasses() {
    int choixClasse;
    printf("\n");
    printf("***********Gestion des classes***********\n");
    printf("** 1. Classe L1 **\n");
    printf("** 2. Classe L2 **\n");
    printf("** 3. Classe L3 **\n");
    scanf("%d", &choixClasse);

    switch (choixClasse) {
        case 1:
            printf("\n");
            printf("***********Gestion de la classe L1***********\n");
            printf("** 1. Presence **\n");
            printf("** 2. Absence **\n");
            printf("** 3. Retard **\n");
            int choixAction;
            scanf("%d", &choixAction);
            if (choixAction == 1) {
                FILE *fichierListeL1 = fopen("listeL1.txt", "r");
                if (fichierListeL1 != NULL) {
                    char ligne[MAX_BUFFER];
                    while (fgets(ligne, MAX_BUFFER, fichierListeL1) != NULL) {
                        printf("%s", ligne);
                    }
                    fclose(fichierListeL1);
                } else {
                    printf("Erreur lors de l'ouverture du fichier listeL1.txt.\n");
                }
            }
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        default:
            printf("Choix invalide\n");
            break;
    }
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
        
        if (ch == 1) {
            // Marquer la présence
            FILE *fichierPresence = fopen("presence.txt", "a");
            if (fichierPresence != NULL) {
                time_t temps = time(NULL);
                struct tm *tm_info = localtime(&temps);
                char timeStr[26];
                strftime(timeStr, 26, "%Y-%m-%d %H:%M:%S", tm_info);
                fprintf(fichierPresence, "Etudiant present le %s\n", timeStr);
                fclose(fichierPresence);
                printf("Votre présence a été enregistrée.\n");
            } else {
                printf("Erreur lors de l'ouverture du fichier de présence.\n");
            }
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

