//************************************************************************************
// Nom du fichier : interfaceLCD.h 
// Auteur : Harold Malbrouck 
//
// Date de création : 30 Mai 2025
// Rev : 1.0
//       2.0 01 Juin 2025 
//
// Interface du module de gestion de l'écran LCD via PCF8574
//************************************************************************************
#ifndef INTERFACE_LCD_H
#define INTERFACE_LCD_H

// Initialise le LCD via I2C avec l'adresse et le chemin du bus
int interfaceLCD_init(const char *i2c_device, int i2c_address);

// Efface l'écran
void interfaceLCD_clear(void);

// Positionne le curseur à la ligne et colonne donnée
void interfaceLCD_setCursor(int ligne, int colonne);

// Affiche une chaîne de caractères
void interfaceLCD_print(const char *texte);

#endif