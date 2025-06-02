//************************************************************************************
// Nom du fichier : interfaceLCD.c 
// Auteur : Harold Malbrouck 
//
// Date de création : 30 Mai 2025
// Révision :
//    - 1.0 : Structure de base
//    - 2.0 (01 Juin 2025) : Ajout de commentaires, nettoyage du code
//
// Description : Interface haut niveau pour afficher sur un écran LCD via I²C,
//               contrôlé en mode 4 bits par un PCF8574. Fait appel au pilote bas niveau.
//************************************************************************************

#include "../include/interfaceLCD.h"
#include "../include/piloteLCD.h"
#include "../include/piloteI2C.h"
#include <string.h>
#include <unistd.h>
#include <syslog.h>

// --- Descripteur de fichier I2C du LCD (privé au module) ---
static int lcd_fd = -1;

int interfaceLCD_init(const char *i2c_device, int i2c_address) {
//************************************************************************************
// Initialise l’interface LCD :
// - Initialise la connexion I²C (via piloteI2C).
// - Configure le LCD via piloteLCD.
//
// @param i2c_device Chemin du bus I2C (ex: "/dev/i2c-8")
// @param i2c_address Adresse I²C du LCD (ex: 0x27)
// @return 0 si succès, -1 si échec
//************************************************************************************
    lcd_fd = piloteI2C_initialise(i2c_device, i2c_address);
    if (lcd_fd < 0) {
        syslog(LOG_ERR, "Erreur pilote I2C LCD");
        return -1;
    }

    // Configuration du LCD en mode 4 bits
    piloteLCD_init(lcd_fd, i2c_address);
    return 0;
}

void interfaceLCD_clear() {
//************************************************************************************
// Efface complètement l’écran LCD
//************************************************************************************
    piloteLCD_envoyerCommande(0x01);  // Commande LCD : Clear display
    usleep(2000);                     // Délai requis pour terminer l'effacement
}

void interfaceLCD_setCursor(int ligne, int colonne) {
//************************************************************************************
// Positionne le curseur à une position donnée (ligne/colonne).
//
// @param ligne 0 à 3 (selon écran LCD 4 lignes)
// @param colonne 0 à 19
//************************************************************************************
    int offset[] = {0x00, 0x40, 0x14, 0x54};  // Adresse de base de chaque ligne
    piloteLCD_envoyerCommande(0x80 | (offset[ligne % 4] + colonne));  // Commande Set DDRAM Address
}

void interfaceLCD_print(const char *texte) {
//************************************************************************************
// Affiche une chaîne de caractères à la position courante du curseur.
//
// @param texte Chaîne à afficher (null-terminated)
//************************************************************************************
    for (int i = 0; texte[i]; i++) {
        piloteLCD_envoyerData(texte[i]);  // Envoie chaque caractère individuellement
    }
}
