# Releases - OpenSailingRC-Anemometer-v2

Ce répertoire contient les binaires compilés et prêts à flasher pour différentes versions d'OpenSailingRC-Anemometer-v2.

## 📦 Structure des releases

Chaque version suit la structure suivante :
```
releases/
├── v1.0.0/
│   ├── firmware.bin          # Firmware principal anémomètre
│   ├── bootloader.bin        # Bootloader ESP32-S3
│   ├── partitions.bin        # Table des partitions
│   ├── firmware.elf          # Symboles de debug (optionnel)
│   ├── checksums.sha256      # Checksums de vérification
│   ├── release_info.txt      # Informations de build
│   ├── FLASH_INSTRUCTIONS.md # Instructions de flash ESP32-S3
│   └── RELEASE_NOTES.md      # Notes de release
├── OpenSailingRC-Anemometer-v2-v1.0.0.zip # Archive complète
└── README.md                 # Ce fichier
```

## 🚀 Utilisation rapide

### Pour flasher la dernière version :
1. **Télécharger** les binaires de la dernière version
2. **Suivre** les instructions dans `FLASH_INSTRUCTIONS.md`
3. **Utiliser esptool** ou PlatformIO pour flasher sur ESP32-S3

### Commande flash rapide pour M5Stack Atom S3 :
```bash
# Flash complet avec esptool
esptool.py --chip esp32s3 --port /dev/ttyUSB0 --baud 921600 \
  --before default_reset --after hard_reset write_flash -z \
  --flash_mode dio --flash_freq 80m --flash_size 8MB \
  0x0000 bootloader.bin \
  0x8000 partitions.bin \
  0x10000 firmware.bin
```

## 🛠️ Création d'une nouvelle release

### Méthode automatique (recommandée) :
```bash
./build_release.sh v1.1.0 "Description de la release"
```

### Méthode manuelle :
```bash
# 1. Compiler le projet
platformio run

# 2. Créer le répertoire
mkdir -p releases/v1.1.0

# 3. Copier les binaires ESP32-S3
cp .pio/build/m5stack-atomsS3/*.bin releases/v1.1.0/

# 4. Générer les checksums
cd releases/v1.1.0
sha256sum *.bin > checksums.sha256
```

## 🎯 Hardware cible

### M5Stack Atom S3
- **Processeur** : ESP32-S3 dual-core @ 240MHz
- **Mémoire** : 8MB Flash, 512KB SRAM
- **Écran** : 128x128 pixels LCD couleur
- **Connectivité** : WiFi 802.11 b/g/n, Bluetooth 5.0
- **Ports** : Grove (I2C/Analogique), USB-C

### Capteurs supportés
- **Anémomètres à coupelles** (contact reed)
- **Capteurs analogiques** 0-3.3V
- **Capteurs I2C** via Grove
- **Capteurs numériques** avec interface série

## 📋 Vérification d'intégrité

Avant de flasher, vérifiez toujours l'intégrité des fichiers :
```bash
# Vérifier les checksums
sha256sum -c checksums.sha256
```

## 🏷️ Versions disponibles

| Version | Date | Taille | Description | Hardware |
|---------|------|--------|-------------|----------|
| [v1.0.0](v1.0.0/) | 2025-09-21 | ~950KB | Première release stable | M5Stack Atom S3 |

## 🌪️ Spécifications de l'anémomètre

### Mesures
- **Plage** : 0-50 m/s (0-180 km/h, 0-97 nœuds)
- **Résolution** : 0.1 m/s
- **Précision** : ±2% @ 10 m/s
- **Fréquence** : 0.5 Hz (toutes les 2 secondes)

### Communication
- **Protocole** : WiFi 802.11 b/g/n
- **Format** : JSON structuré
- **Portée** : 50-100m en champ libre
- **Compatibilité** : Écosystème OpenSailingRC

## 🔗 Liens utiles

- **Documentation** : [README principal](../README.md)
- **Code source** : [Repository GitHub](https://github.com/FRA-222/OpenSailingRC-Anemometer-v2)
- **Issues** : [GitHub Issues](https://github.com/FRA-222/OpenSailingRC-Anemometer-v2/issues)
- **Releases GitHub** : [GitHub Releases](https://github.com/FRA-222/OpenSailingRC-Anemometer-v2/releases)

## 🔄 Écosystème OpenSailingRC

### Intégrations
- **OpenSailingRC-Display** : Affichage des données de vent
- **OpenSailingRC-GPS** : Données de navigation combinées
- **OpenSailingRC-Base** : Station de contrôle télécommande

### Compatibilité
- **Protocole unifié** pour tous les capteurs
- **API standardisée** pour développement tiers
- **Format de données** JSON cohérent

## ⚠️ Important

- **Ne jamais committer** les binaires dans le repository principal
- **Toujours tester** sur hardware réel avant release GitHub
- **Vérifier les checksums** avant distribution
- **Maintenir** la documentation technique à jour
- **Valider** la calibration de l'anémomètre

## 🧪 Tests recommandés

### Avant chaque release
- [ ] **Flash test** : Validation sur M5Stack Atom S3
- [ ] **Calibration** : Vérification avec anémomètre de référence
- [ ] **WiFi** : Test de transmission à différentes distances
- [ ] **Durabilité** : Test fonctionnement continu 24h
- [ ] **Conditions** : Test par temps variable (vent/pluie)

---

**Maintenu par :** Philippe Hubert  
**Licence :** GPL v3.0  
**Hardware cible :** M5Stack Atom S3 (ESP32-S3)