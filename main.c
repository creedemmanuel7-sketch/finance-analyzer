#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * PROJET #2 VERSION FINALE : ANALYSEUR DE TRANSACTIONS ROBUSTE
 * -------------------------------------------------------------
 * Améliorations : Gestion des espaces, protection contre la corruption,
 * et menu interactif sécurisé.
 */

typedef struct {
    char categorie[50];
    float montant;
    char date[12];
} Transaction;

// Fonction pour vider le tampon d'entrée (évite les bugs de scanf)
void viderTampon() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ajouterTransaction() {
    FILE *fichier = fopen("transactions.txt", "a");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier !\n");
        return;
    }

    Transaction t;
    printf("\n--- Ajouter une depense ---\n");
    
    printf("Categorie (ex: Dejeuner) : ");
    viderTampon(); // Nettoie avant de lire du texte
    fgets(t.categorie, 50, stdin);
    t.categorie[strcspn(t.categorie, "\n")] = 0; // Enlever le \n de la fin

    printf("Montant (FCFA) : ");
    scanf("%f", &t.montant);

    printf("Date (AAAA-MM-JJ) : ");
    scanf("%s", t.date);

    // Écriture sécurisée avec un \n à la fin
    fprintf(fichier, "%s;%.2f;%s\n", t.categorie, t.montant, t.date);
    fclose(fichier);

    printf("✔️ Depense enregistree avec succes !\n");
}

void analyserDonnees() {
    FILE *fichier = fopen("transactions.txt", "r");
    if (fichier == NULL) {
        printf("Aucune donnee trouvee. Ajoute d'abord une depense !\n");
        return;
    }

    Transaction t;
    float total = 0, max_montant = 0;
    char max_cat[50], ligne[150];
    int count = 0;

    printf("\n--- Analyse des Finances ---\n");
    printf("%-12s | %-15s | %s\n", "Date", "Categorie", "Montant");
    printf("-------------------------------------------\n");

    while (fgets(ligne, sizeof(ligne), fichier)) {
        // Nettoyage de la ligne (enlever le \n s'il existe)
        ligne[strcspn(ligne, "\n")] = 0;
        if (strlen(ligne) < 5) continue; // Ignore les lignes vides ou trop courtes

        // Parsing robuste avec %[^;] pour la catégorie et %11s pour la date
        if (sscanf(ligne, "%[^;];%f;%11s", t.categorie, &t.montant, t.date) == 3) {
            total += t.montant;
            if (t.montant > max_montant) {
                max_montant = t.montant;
                strcpy(max_cat, t.categorie);
            }
            count++;
            printf("%-12s | %-15s | %.2f FCFA\n", t.date, t.categorie, t.montant);
        } else {
            printf("⚠️ Ligne malformee ignoree : %s\n", ligne);
        }
    }

    if (count > 0) {
        printf("\n--- RESULTATS ---\n");
        printf("Transactions total : %d\n", count);
        printf("Total depense      : %.2f FCFA\n", total);
        printf("Moyenne            : %.2f FCFA\n", total / count);
        printf("Plus gros achat    : %.2f FCFA (%s)\n", max_montant, max_cat);
        
        if (total > 60000) printf("\n🚩 BUDGET DEPASSE ! (Seuil 60,000)\n");
    }
    fclose(fichier);
}

int main() {
    int choix = 0;
    while (choix != 3) {
        printf("\n--- MENU FINANCE INTERACTIF ---\n");
        printf("1. Ajouter une depense\n");
        printf("2. Analyser mes depenses\n");
        printf("3. Quitter\n");
        printf("Choix : ");
        
        if (scanf("%d", &choix) != 1) {
            printf("Entree invalide, tape un chiffre.\n");
            viderTampon();
            continue;
        }

        if (choix == 1) ajouterTransaction();
        else if (choix == 2) analyserDonnees();
        else if (choix == 3) printf("Au revoir !\n");
    }
    return 0;
}
