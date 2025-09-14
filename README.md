# OpenSailingRC Anemometer v2

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Platform](https://img.shields.io/badge/Platform-ESP32--S3-orange.svg)](https://www.espressif.com/en/products/socs/esp32-s3)
[![Hardware](https://img.shields.io/badge/Hardware-M5Stack%20Atom%20S3-red.svg)](https://shop.m5stack.com/products/atoms3-dev-kit-w-0-85-inch-screen)

Un anémomètre intelligent basé sur M5Stack Atom S3 pour la mesure et transmission sans fil de la vitesse du vent, conçu pour les applications de voile radiocommandée.

## 🌟 Fonctionnalités

- **Mesure en temps réel** : Lecture continue de la vitesse du vent
- **Affichage visuel** : Interface utilisateur sur écran M5Stack Atom S3
- **Communication sans fil** : Transmission des données via ESP-NOW
- **Logging avancé** : Enregistrement sur port série, carte SD et écran
- **Architecture modulaire** : Code organisé en classes réutilisables
- **Identification unique** : Chaque dispositif a un ID unique pour le réseau

## 🛠 Matériel requis

- **M5Stack Atom S3** - Microcontrôleur principal
- **M5Stack Voltmeter Unit** - Interface de mesure (ADS1115)
- **Anémomètre analogique** - Capteur de vitesse du vent
- **Carte microSD** (optionnelle) - Pour l'enregistrement des données

## 📋 Spécifications techniques

- **Processeur** : ESP32-S3 (dual-core, 240MHz)
- **Connectivité** : WiFi 802.11 b/g/n, ESP-NOW
- **Résolution ADC** : 16 bits (ADS1115)
- **Plage de mesure** : 0-100+ m/s (configurable)
- **Fréquence d'échantillonnage** : 0.5 Hz (2 secondes)
- **Précision tension** : ±0.1% avec calibration

## 🏗 Architecture du code

### Classes principales

#### `Anemometer`
Gère la lecture et conversion des mesures de vitesse du vent
- Interfaçage avec l'ADC ADS1115
- Calibration et conversion tension → vitesse
- Filtrage et lissage des mesures

#### `Communication`
Gère la communication sans fil ESP-NOW
- Configuration du réseau WiFi
- Diffusion des données d'anémomètre
- Gestion des erreurs de transmission

#### `Logger`
Système de logging multi-canal
- Sortie série pour débogage
- Affichage sur écran LCD
- Enregistrement sur carte SD

### Structure des données

```cpp
typedef struct {
    uint32_t anemometerId;   // ID unique de l'anémomètre
    uint8_t macAddress[6];   // Adresse MAC du dispositif
    float windSpeed;         // Vitesse du vent (m/s)
} AnemometerData;
```

## ⚙️ Installation

### Prérequis

1. **PlatformIO** installé dans VS Code
2. **Pilotes USB** pour M5Stack Atom S3
3. **Git** pour cloner le dépôt

### Étapes d'installation

```bash
# Cloner le dépôt
git clone https://github.com/FRA-222/OpenSailingRC-Anemometer-v2.git
cd OpenSailingRC-Anemometer-v2

# Ouvrir avec PlatformIO
code .

# Compiler et télécharger
pio run -t upload
```

### Dépendances

Les bibliothèques suivantes sont automatiquement installées via PlatformIO :

```ini
lib_deps = 
    m5stack/M5Unified@^0.1.14
    wnatth3/WiFiManager@^2.0.16-rc.2
    fastled/FastLED@^3.9.0
    m5stack/M5AtomS3@^1.0.2
    m5stack/M5-ADS1115@^1.0.0
```

## 🔧 Configuration

### Calibration de l'anémomètre

La calibration se fait via les tableaux dans `Anemometer.cpp` :

```cpp
// Courbe de calibration : Tension (mV) → Vitesse (m/s)
static float INPUT_WIND_SPEED_VS_VOLTAGE[] = {
    2000., 3000., 3500., 3659., 3765., 3800., 
    3829., 3851., 3875., 3900., 3930., 3988., 
    4090., 4200., 4500.
};

static float OUTPUT_WIND_SPEED_VS_VOLTAGE[] = {
    0., 0., 5., 10., 20., 30., 
    40., 50., 60., 70., 80., 90., 
    97., 100., 100.
};
```

### Configuration du logging

Dans `main.cpp`, ajustez les paramètres du logger :

```cpp
// Logger(SD, Série, Écran)
Logger logger(false, true, true);
```

### ID de l'anémomètre

Modifiez l'ID unique dans la boucle principale :

```cpp
data.anemometerId = 1; // Changez cette valeur pour chaque dispositif
```

## 📊 Utilisation

### Démarrage

1. Alimenter le M5Stack Atom S3
2. Le système s'initialise automatiquement
3. L'écran affiche "Init" puis "Après setup"
4. Les mesures commencent immédiatement

### Interface utilisateur

- **Écran principal** : Affichage de la vitesse du vent en m/s
- **Port série** : Messages de debug et valeurs détaillées
- **LED** : Indicateur d'état du système

### Données transmises

Les données sont diffusées via ESP-NOW toutes les 2 secondes :
- ID de l'anémomètre
- Adresse MAC du dispositif
- Vitesse du vent actuelle

## 🔍 Débogage

### Messages série

```
Init
Après setup
Wind Speed: 5.42 m/s
ESP-NOW broadcast success
```

### Codes d'erreur

- `Unit Vmeter Init Fail` : Problème d'initialisation ADC
- `Error initializing ESP-NOW` : Erreur communication WiFi
- `ESP-NOW broadcast failed` : Échec transmission

## 🤝 Contribution

Les contributions sont les bienvenues ! Merci de :

1. Fork le projet
2. Créer une branche pour votre fonctionnalité
3. Commiter vos changements
4. Pousser vers la branche
5. Ouvrir une Pull Request

### Standards de code

- Commentaires en français
- Documentation des fonctions publiques
- Tests unitaires pour les nouvelles fonctionnalités
- Respect de la convention de nommage existante

## 📝 Licence

Ce projet est sous licence **GNU General Public License v3.0**. Voir le fichier [LICENSE](LICENSE) pour plus de détails.

```
Copyright (C) 2025 Philippe Hubert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
```

## 👤 Auteur

**Philippe Hubert** - *Développement initial* - [FRA-222](https://github.com/FRA-222)

## 🙏 Remerciements

- **M5Stack** pour l'écosystème hardware
- **Espressif** pour le processeur ESP32-S3
- **Communauté PlatformIO** pour l'environnement de développement
- **Communauté OpenSailingRC** pour les tests et retours

## 📚 Documentation supplémentaire

- [Wiki du projet](../../wiki)
- [Guide de calibration](docs/calibration.md)
- [API Reference](docs/api.md)
- [Troubleshooting](docs/troubleshooting.md)

## 🔗 Liens utiles

- [Site M5Stack](https://m5stack.com/)
- [Documentation ESP32-S3](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/)
- [PlatformIO Documentation](https://docs.platformio.org/)
- [ESP-NOW Protocol](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_now.html)

---

*Ce projet fait partie de l'écosystème OpenSailingRC pour la voile radiocommandée.*