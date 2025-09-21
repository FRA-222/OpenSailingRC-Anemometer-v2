# Instructions de Flash - OpenSailingRC-Anemometer-v2 v1.0.0

## 📦 Contenu de la release

- **`firmware.bin`** - Firmware principal de l'anémomètre
- **`bootloader.bin`** - Bootloader ESP32-S3
- **`partitions.bin`** - Table des partitions Flash

## 🛠️ Méthodes de flash

### Méthode 1 : Avec esptool (recommandée)

#### Installation d'esptool
```bash
pip install esptool
```

#### Flash complet (tous les binaires)
```bash
esptool.py --chip esp32s3 --port /dev/ttyUSB0 --baud 921600 \
  --before default_reset --after hard_reset write_flash -z \
  --flash_mode dio --flash_freq 80m --flash_size 8MB \
  0x0000 bootloader.bin \
  0x8000 partitions.bin \
  0x10000 firmware.bin
```

#### Flash firmware seulement (mise à jour)
```bash
esptool.py --chip esp32s3 --port /dev/ttyUSB0 --baud 921600 \
  --before default_reset --after hard_reset write_flash -z \
  --flash_mode dio --flash_freq 80m --flash_size 8MB \
  0x10000 firmware.bin
```

### Méthode 2 : Avec PlatformIO

1. **Cloner le projet source**
   ```bash
   git clone https://github.com/FRA-222/OpenSailingRC-Anemometer-v2.git
   cd OpenSailingRC-Anemometer-v2
   ```

2. **Flash avec PlatformIO**
   ```bash
   platformio run --target upload
   ```

### Méthode 3 : Avec ESP32-S3 Flash Download Tool

1. **Télécharger** [ESP32 Flash Download Tool](https://www.espressif.com/en/support/download/other-tools)
2. **Sélectionner** : ESP32-S3 dans le menu déroulant
3. **Configurer les adresses :**
   - `bootloader.bin` → `0x0000`
   - `partitions.bin` → `0x8000`
   - `firmware.bin` → `0x10000`
4. **Paramètres :**
   - SPI Speed: `80MHz`
   - SPI Mode: `DIO`
   - Flash Size: `8MB`

## 🔧 Identification du port série

### Windows
- Généralement `COM3`, `COM4`, etc.
- Vérifier dans le Gestionnaire de périphériques

### macOS
```bash
ls /dev/tty.usbserial-*
# ou pour M5Stack Atom S3
ls /dev/tty.usbmodem*
```

### Linux
```bash
ls /dev/ttyUSB*
# ou
ls /dev/ttyACM*
```

## ⚠️ Prérequis et précautions

### Hardware requis
- **M5Stack Atom S3** (ESP32-S3 basé)
- **Capteur anémomètre** compatible
- **Câble USB-C** de qualité
- **Alimentation** 5V via USB ou batterie externe

### Spécifications M5Stack Atom S3
- **Processeur** : ESP32-S3 dual-core 240MHz
- **Mémoire** : 8MB Flash, 512KB SRAM
- **Écran** : 128x128 pixels couleur
- **Connectivité** : WiFi 802.11 b/g/n, Bluetooth 5.0
- **GPIO** : Connecteurs Grove pour capteurs

### Avant le flash
1. **Installer les pilotes** USB-Serial CH9102 si nécessaire
2. **Fermer** tous les moniteurs série ouverts
3. **Connecter** le M5Stack Atom S3 via USB-C
4. **Presser et maintenir** le bouton reset si nécessaire

### Vérification post-flash
1. **Redémarrer** le M5Stack Atom S3
2. **Vérifier** l'affichage sur l'écran LCD
3. **Tester** la lecture du capteur anémomètre
4. **Valider** la transmission WiFi des données
5. **Confirmer** l'affichage des vitesses de vent

## 🌪️ Configuration de l'anémomètre

### Calibration du capteur
Le firmware inclut une calibration par défaut pour anémomètres standard. Pour une calibration personnalisée :

1. **Connecter** l'anémomètre aux ports Grove
2. **Placer** dans un environnement de vent contrôlé
3. **Noter** les valeurs affichées vs vitesse réelle
4. **Ajuster** les paramètres de calibration si nécessaire

### Connexions matérielles
- **Anémomètre** : Port Grove A (GPIO 1/2)
- **Alimentation** : USB-C ou connecteur JST
- **Communication** : WiFi intégré

## 🐛 Résolution de problèmes

### Erreurs communes

#### `Failed to connect to ESP32-S3`
- Vérifier le câble USB-C
- Maintenir le bouton reset pendant le flash
- Essayer un autre port USB
- Réduire la vitesse de baud à `115200`

#### `Invalid head of packet`
- Flash corrompu, recommencer le flash complet
- Vérifier l'intégrité des fichiers binaires
- S'assurer que le chip est bien ESP32-S3

#### `No wind speed detected`
- Vérifier les connexions de l'anémomètre
- Tester l'alimentation du capteur
- Vérifier la calibration

#### `WiFi connection failed`
- Configurer les credentials WiFi
- Vérifier la portée du réseau
- Redémarrer le dispositif

### Debugging
```bash
# Monitorer les logs série
esptool.py --port /dev/ttyUSB0 monitor
```

### Support
- **Issues GitHub** : [Signaler un problème](https://github.com/FRA-222/OpenSailingRC-Anemometer-v2/issues)
- **Documentation** : [Wiki du projet](https://github.com/FRA-222/OpenSailingRC-Anemometer-v2/wiki)

## 📋 Checksums (vérification d'intégrité)

Vérifiez l'intégrité des fichiers avec ces checksums SHA256 :

```bash
# Générer les checksums
sha256sum *.bin
```

| Fichier | SHA256 |
|---------|--------|
| firmware.bin | *À générer après build* |
| bootloader.bin | *À générer après build* |
| partitions.bin | *À générer après build* |

## 🔄 Écosystème OpenSailingRC

Ce dispositif fait partie de l'écosystème OpenSailingRC et communique avec :
- **OpenSailingRC-Display** : Affichage des données de vent
- **OpenSailingRC-GPS** : Données de navigation
- **OpenSailingRC-Base** : Station de contrôle

---

**Version :** v1.0.0  
**Date :** 21 septembre 2025  
**Compatibilité :** M5Stack Atom S3  
**Auteur :** Philippe Hubert