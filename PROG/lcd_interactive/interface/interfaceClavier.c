//************************************************************************************
// Nom du fichier : interfaceClavier.c 
// Auteur : Harold Malbrouck 
//
// Date de création : 30 Mai 2025
//
// Description : Module qui gère l'interruption GPIO et la lecture I2C du clavier 4x4.
//               Ce clavier est connecté via un microcontrôleur (PIC16F88) sur I²C,
//               avec une ligne GPIO en interruption (INT) lorsque l’utilisateur appuie.
//************************************************************************************

#include "../include/interfaceClavier.h"
#include "../include/piloteI2C.h"
#include <gpiod.h>
#include <unistd.h>
#include <syslog.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>

// --- Variables internes ---
static int clavier_fd = -1;                     // File descriptor I2C du clavier
static struct gpiod_line *ligne_int = NULL;     // Ligne GPIO utilisée pour l'interruption
static struct gpiod_chip *puce_gpio = NULL;     // Puce GPIO

int interfaceClavier_init(const char *chipname, int ligne_gpio, const char *i2c_device, int i2c_addr) {
//*******************************************************************************************
// Initialise le clavier :
// 1. Initialise la communication I2C avec l'adresse donnée.
// 2. Configure l’interruption GPIO via libgpiod avec résistance pull-up.
//
// @param chipname     Exemple : "/dev/gpiochip3"
// @param ligne_gpio   Numéro de ligne GPIO à utiliser pour l’INT (ex: 10 pour GPIO3_B2)
// @param i2c_device   Exemple : "/dev/i2c-8"
// @param i2c_addr     Adresse I2C du PIC (ex: 0x14)
// @return 0 si succès, -1 si échec
//********************************************************************************************
    
	// Ouverture du bus I2C
    clavier_fd = piloteI2C_initialise(i2c_device, i2c_addr);
    if (clavier_fd < 0) {
        syslog(LOG_ERR, "Erreur ouverture clavier I2C");
        return -1;
    }

    // Ouverture de la puce GPIO
    puce_gpio = gpiod_chip_open(chipname);
    if (!puce_gpio) {
        syslog(LOG_ERR, "Erreur ouverture chip GPIO");
        return -1;
    }

    // Récupération de la ligne GPIO à utiliser
    ligne_int = gpiod_chip_get_line(puce_gpio, ligne_gpio);
    if (!ligne_int) {
        syslog(LOG_ERR, "Erreur récupération ligne GPIO");
        return -1;
    }

    // Configuration de la ligne pour recevoir les interruptions (front descendant, pull-up)
    if (gpiod_line_request_falling_edge_events_flags(
            ligne_int, "clavier", GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP) < 0) {
        syslog(LOG_ERR, "Erreur demande événement d'interruption");
        return -1;
    }

    return 0;
}

char interfaceClavier_attendreTouche() {
//*******************************************************************************************
// Attend une interruption, puis lit un code via I²C.
// Si la lecture est correcte, le code est traduit en caractère clavier.
// Le code 0x20 est ignoré (aucune touche valide).
//
// @return Caractère de la touche ('0'-'9', 'A'-'D', '*', '#') ou '?' si inconnu
//*******************************************************************************************
    struct gpiod_line_event event;

    // Attente d’un événement d’interruption
    int ret = gpiod_line_event_wait(ligne_int, NULL);
    if (ret <= 0) return 0;

    if (gpiod_line_event_read(ligne_int, &event) < 0) {
        syslog(LOG_ERR, "Erreur lecture événement INT");
        return 0;
    }

    // Lecture I2C du code de touche depuis le microcontrôleur
    unsigned char buffer = 0;
    if (read(clavier_fd, &buffer, 1) != 1) {
        syslog(LOG_ERR, "Erreur lecture I2C touche");
        return 0;
    }

    // Filtrage du code 0x20 (aucune touche active détectée)
    if (buffer == 0x20) {
        syslog(LOG_INFO, "Code 0x20 ignoré (aucune touche)");
        return 0;
    }

    // Décodage du code I²C en caractère humain lisible
    char touche = '?';
    switch (buffer) {
        case 0x00: touche = '1'; break;
        case 0x01: touche = '2'; break;
        case 0x02: touche = '3'; break;
        case 0x03: touche = 'A'; break;
        case 0x04: touche = '4'; break;
        case 0x05: touche = '5'; break;
        case 0x06: touche = '6'; break;
        case 0x07: touche = 'B'; break;
        case 0x08: touche = '7'; break;
        case 0x09: touche = '8'; break;
        case 0x0A: touche = '9'; break;
        case 0x0B: touche = 'C'; break;
        case 0x0C: touche = '*'; break;
        case 0x0D: touche = '0'; break;
        case 0x0E: touche = '#'; break;
        case 0x0F: touche = 'D'; break;
        default:
            syslog(LOG_WARNING, "Code touche inconnu: 0x%02X", buffer);
            touche = '?';
            break;
    }

    return touche;
}
