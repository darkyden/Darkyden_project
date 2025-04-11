
# 💻 Diagrammes de cas d'utilisation – Laptop CM3588 Plus

## 🎯 1. Cas d'utilisation – Point de vue de l’utilisateur

```
[État initial : OFF]
    |
    | Appui bouton power (debounce 50 ms)
    v
[BOOTLOADER]
    |
    | Chargement du bootloader (delay: 1-3 sec)
    v
[OS Linux chargé]
    |
    | - Interface graphique active
    | - Réseau détecté?
    |       |-- Oui --> Connexion automatique (delay: 3-5 sec)
    |       |-- Non --> Affichage de l'outil de sélection réseau
    v
[Écran d’accueil / Bureau]
    |
    | Actions possibles :
    | - Lancer terminal
    | - Ouvrir navigateur
    | - Lancer analyse réseau (Nmap, Tshark)
    | - Gérer fichiers
    | - Mise en veille automatique après 10 min inactivité
    |
    | Mise en veille : Appui touche ou pad → Retour bureau (delay: <1 sec)
    |
    | Appui long power (2 sec) → Demande de confirmation d’arrêt
    | → Oui → Arrêt propre du système (3-6 sec)
```

---

## 🧰 2. Cas d'utilisation – Point de vue du technicien

```
[État initial : OFF ou ON]
    |
    | Connexion série UART ou SSH (si actif)
    v
[Console ou TTY active]
    |
    | Tâches possibles :
    | - Flash du bootloader
    | - Modification du fstab, réseau, kernel, uboot
    | - Lecture des logs : dmesg, journalctl
    | - Diagnostic I²C / SPI / USB / PCIe
    | - Interaction GPIO (avec debounce logiciel : 10-100 ms)
    |
    | Commandes système :
    | - reboot → redémarrage (delay: ~5 sec)
    | - halt → arrêt immédiat
    |
    | Monitoring ressources :
    | - top, htop, iotop, powertop
    |
    | Maintenance :
    | - Mise à jour via apt, emerge ou pacman selon distro
    | - Scripts de test de modules (ping module Wi-Fi, test audio I2S)
```

---

## 🔁 Transitions entre états (simplifiées)

```
OFF --> [Appui bouton power] --> BOOTLOADER --> [OS Linux]
OS Linux --> [Inactivité 10 min] --> VEILLE
VEILLE --> [Mouvement souris/clavier] --> OS Linux
OS Linux --> [Appui long 2s + validation] --> SHUTDOWN
```

---

## ⏱ Détails sur les délais

| Action                          | Délai approximatif     |
|---------------------------------|-------------------------|
| Debounce bouton                 | 50 ms                  |
| Bootloader                      | 1 – 3 sec              |
| Démarrage complet Linux         | 5 – 10 sec             |
| Connexion Wi-Fi                 | 3 – 5 sec              |
| Mise en veille automatique      | 10 min (paramétrable)  |
| Réveil de veille                | < 1 sec                |
| Arrêt complet                   | 3 – 6 sec              |
| Temps de réponse CLI (console)  | instantané (<100 ms)   |
