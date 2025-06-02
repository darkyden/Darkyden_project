//************************************************************************************
// Nom du fichier : piloteLCD.c  
// Auteur : Harold Malbrouck 
//
// Date de création : 30 Mai 2025
// Rev : 1.0
//       2.0 01 Juin 2025
// Communication avec LCD via PCF8574 en 4 bits
//************************************************************************************
#include "../include/piloteLCD.h"
#include "../include/piloteI2C.h"
#include <unistd.h>

// Variables statiques pour stocker le descripteur I2C et l'adresse de l'écran
static int lcd_fd = -1;
static int lcd_addr = 0;

void piloteLCD_init(int fd, int addr) {
//************************************************************************************
// Initialise le LCD avec une séquence standard pour l'utiliser en 4 bits via PCF8574 
//************************************************************************************
    lcd_fd = fd;
    lcd_addr = addr;
    usleep(50000);
	
	// Séquence d'initialisation 4 bits
    piloteLCD_envoyerCommande(0x33);
    piloteLCD_envoyerCommande(0x32);
    piloteLCD_envoyerCommande(0x28);
    piloteLCD_envoyerCommande(0x0C);
    piloteLCD_envoyerCommande(0x06);
    piloteLCD_envoyerCommande(0x01);
    usleep(5000);
}

void piloteLCD_envoyerCommande(uint8_t cmd) {
//************************************************************************************
// Envoie une commande au LCD
//************************************************************************************
    piloteLCD_envoyerByte(cmd, 0);
}

void piloteLCD_envoyerData(uint8_t data) {
//************************************************************************************
// Envoie une donnée à afficher au LCD
//************************************************************************************
    piloteLCD_envoyerByte(data, 1);
}

void piloteLCD_envoyerByte(uint8_t val, int mode) {
//************************************************************************************
// Envoie un octet en deux nibbles (4 bits)
//************************************************************************************
	// Préparation des nibbles haut et bas
    unsigned char high = mode | (val & 0xF0) | 0x08;
    unsigned char low = mode | ((val << 4) & 0xF0) | 0x08;
    
	// Séquence pour activer le E (Enable) à chaque demi-octet
    unsigned char seq[] = {
        high | 0x04, high,
        low | 0x04, low
    };
	
	// Envoie de la séquence via I2C
    piloteI2C_ecrire(lcd_fd, seq, 4);
}