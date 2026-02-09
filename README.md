# Analyseur de Finances en C 💳

Un outil interactif développé en Langage C pour analyser et suivre mes dépenses quotidiennes.

## 📝 Description
Ce programme permet de :
1. **Ajouter interactivement** des dépenses (catégorie, montant, date).
2. **Lire un fichier historique** (`transactions.txt`).
3. **Calculer des statistiques** : Total des dépenses, moyenne par achat.
4. **Détection d'anomalies** : Alerte automatique si le budget dépasse 60 000 FCFA.

## 🧠 Concepts techniques
- **Structures (`struct`)** : Pour regrouper les données d'une transaction.
- **File I/O (`fopen`, `fprintf`, `fgets`)** : Pour manipuler les fichiers texte.
- **Tampon d'entrée** : Gestion propre de la mémoire clavier pour les entrées utilisateur.

## 🚀 Lancement
```bash
gcc main.c -o analyzer
./analyzer
```

---
*Projet #2 du défi "Un Projet par Jour"*
Créer par ADJIGNON Crédo