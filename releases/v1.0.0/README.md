# 📦 OpenSailingRC Anemometer v2 - Release v1.0.0

**Date** : 5 octobre 2025  
**Plateforme** : M5Stack AtomS3 (ESP32-S3)  
**Version Firmware** : 1.0.0

---

## 🎯 Installation Rapide

### **Pour Utilisateurs Non Techniques : M5Burner (Recommandé)**

**Fichier** : `OpenSailingRC_Anemometer_v1.0.0_MERGED.bin` (903 KB)

**Installation en 3 clics** :
1. Ouvrir M5Burner → Custom Firmware
2. Sélectionner `MERGED.bin` → Adresse **0x0** ⚠️
3. Cocher "Erase Flash" → BURN

⏱️ **Temps** : 1-2 minutes  
📖 **Guide détaillé** : `M5BURNER_INSTRUCTIONS.txt`

---

### **Pour Développeurs : ESPTool**

**Firmware Fusionné** (recommandé) :
```bash
esptool.py --chip esp32s3 --port PORT write_flash 0x0 \
    OpenSailingRC_Anemometer_v1.0.0_MERGED.bin
```

**Fichiers Séparés** :
```bash
esptool.py --chip esp32s3 --port PORT write_flash \
    0x0 bootloader.bin \
    0x8000 partitions.bin \
    0x10000 firmware.bin
```

📖 **Toutes les méthodes** : `FLASH_INSTRUCTIONS.md`

---

## 📦 Contenu de la Release

### **Fichiers Binaires**

| Fichier | Taille | Description | Usage |
|---------|--------|-------------|-------|
| **OpenSailingRC_Anemometer_v1.0.0_MERGED.bin** | 903 KB | ⭐ **Firmware fusionné** | **M5Burner à 0x0** |
| bootloader.bin | 15 KB | Bootloader ESP32-S3 | ESPTool à 0x0 |
| partitions.bin | 3 KB | Table partitions | ESPTool à 0x8000 |
| firmware.bin | 839 KB | Application | ESPTool à 0x10000 |

### **Documentation**

| Fichier | Description |
|---------|-------------|
| README.md | Ce fichier - Vue d'ensemble |
| M5BURNER_INSTRUCTIONS.txt | Instructions M5Burner détaillées |
| FLASH_INSTRUCTIONS.md | Toutes les méthodes de flash |
| MERGED_FIRMWARE_GUIDE.md | Guide complet firmware fusionné |
| RELEASE_NOTES.md | Notes de version |
| checksums.sha256 | Checksums SHA256 |

---

## ✨ Nouveauté : Firmware Fusionné

### **Pourquoi ?**

**Avant** : Installation complexe (3 fichiers + ligne de commande)  
**Maintenant** : Installation simple (1 fichier + M5Burner)

### **Avantages**

- ✅ **1 seul fichier** à gérer
- ✅ **Interface graphique** (M5Burner)
- ✅ **Accessible à tous**
- ✅ **Zéro erreur**

📖 **Détails** : `MERGED_FIRMWARE_GUIDE.md`

---

## 🔍 Vérification de l'Installation

### **LED RGB**

1. **Rouge** (1 sec) - Démarrage
2. **Bleu** (continu) - Configuration WiFi nécessaire
3. **Vert** (clignotant) - Fonctionnement normal

### **WiFi Manager** (Premier démarrage)

1. L'AtomS3 crée un AP : `OpenSailingRC-Anemometer-XXXXXX`
2. Se connecter au WiFi
3. Ouvrir : http://192.168.4.1
4. Configurer votre réseau WiFi

### **Moniteur Série** (115200 baud)

```
[I] WiFiManager: Starting configuration portal
[I] Anemometer: Calibration complete
[I] Anemometer: Ready to measure
✅ Aucune erreur de boot
```

---

## 🔐 Sécurité - Vérification des Checksums

**Avant de flasher**, vérifiez l'intégrité :

```bash
# Calculer le checksum
shasum -a 256 OpenSailingRC_Anemometer_v1.0.0_MERGED.bin

# Doit afficher :
4c6f23a7777f3f36584dbdbe38ad74e5955e3a8bf5b849d6b28d2f8c286e81b4
```

Ou vérifier avec le fichier `checksums.sha256` :
```bash
shasum -a 256 -c checksums.sha256
```

---

## ⚠️ Dépannage Rapide

### **Problème : Reboot Infini**

**Cause** : Adresse incorrecte ou bootloader manquant

**Solution** :
```bash
python3 -m esptool --chip esp32s3 --port PORT erase_flash
python3 -m esptool --chip esp32s3 --port PORT write_flash 0x0 MERGED.bin
```

⚠️ **Vérifiez** : Adresse = **0x0** (pas 0x10000)

---

### **Problème : M5Burner "No Serial Data"**

**Solutions** :
1. Essayer un autre câble USB-C
2. Installer drivers CH9102 : https://docs.m5stack.com/en/download
3. Redémarrer M5Burner

---

### **Problème : LED Reste Rouge**

**Cause** : Firmware corrompu ou erreur matérielle

**Solution** :
1. Vérifier le checksum SHA256
2. Re-télécharger le firmware
3. Re-flasher avec "Erase Flash" coché

---

## 📚 Documentation Complète

### **Guides d'Installation**
- 📄 `M5BURNER_INSTRUCTIONS.txt` - Installation M5Burner (débutants)
- 📄 `FLASH_INSTRUCTIONS.md` - Toutes les méthodes (avancés)
- 📄 `MERGED_FIRMWARE_GUIDE.md` - Guide firmware fusionné (technique)

### **Informations**
- 📄 `RELEASE_NOTES.md` - Fonctionnalités et corrections
- 📄 `checksums.sha256` - Vérification intégrité

### **Projet Source**
- 🔗 GitHub : https://github.com/FRA-222/OpenSailingRC-Anemometer-v2
- 📖 README : https://github.com/FRA-222/OpenSailingRC-Anemometer-v2/blob/main/README.md

---

## 🎯 Fonctionnalités

### **Mesure du Vent**
- Vitesse du vent (0-100 km/h)
- Direction du vent (0-360°)
- Rafales (max sur 3 secondes)
- Calibration automatique

### **Connectivité**
- WiFi Manager (configuration facile)
- Serveur web embarqué
- API REST pour données
- OTA updates (future v1.1.0)

### **Affichage**
- LED RGB état système
- Bouton programmable
- Monitoring série (debug)

### **Stockage**
- Configuration persistante (NVS)
- Logs système
- Calibration sauvegardée

---

## 🆚 Comparaison des Méthodes

| Méthode | Fichiers | Complexité | Public |
|---------|----------|------------|--------|
| **M5Burner (MERGED)** | 1 | ⭐ Simple | **Tous** |
| **ESPTool (MERGED)** | 1 | ⭐⭐ Moyenne | Avancés |
| **ESPTool (3 fichiers)** | 3 | ⭐⭐⭐ Complexe | Développeurs |
| **PlatformIO** | Source | ⭐⭐⭐⭐ Expert | Développeurs |

**Recommandation** : **M5Burner** avec firmware fusionné pour 99% des cas

---

## 📊 Spécifications Techniques

### **Hardware**
- **Plateforme** : M5Stack AtomS3
- **Chip** : ESP32-S3-MINI-1-N4R2
- **Flash** : 8 MB
- **RAM** : 512 KB SRAM + 2 MB PSRAM
- **WiFi** : 802.11 b/g/n
- **LED** : SK6812 RGB
- **Capteur** : ADS1115 (16-bit ADC)

### **Firmware**
- **Taille** : 903 KB (11% flash)
- **Framework** : Arduino-ESP32
- **Libraries** : M5Unified, WiFiManager, FastLED
- **Partition** : OTA enabled (2x 1.9 MB)

### **Performance**
- **Boot** : ~2 secondes
- **Sampling** : 100 Hz (anémomètre)
- **Latence** : <10 ms
- **Précision** : ±0.5 km/h (vitesse), ±5° (direction)

---

## 🚀 Prochaines Versions

### **v1.1.0 (Q4 2025)**
- [ ] OTA updates via WiFi
- [ ] Interface web configuration
- [ ] Export données JSON/CSV
- [ ] Alarmes configurables

### **v1.2.0 (Q1 2026)**
- [ ] Bluetooth BLE
- [ ] Application mobile
- [ ] Mode économie d'énergie
- [ ] Logs sur carte SD

---

## 📞 Support

### **Documentation**
- GitHub : https://github.com/FRA-222/OpenSailingRC-Anemometer-v2
- Wiki : https://github.com/FRA-222/OpenSailingRC-Anemometer-v2/wiki

### **Aide**
- Issues : https://github.com/FRA-222/OpenSailingRC-Anemometer-v2/issues
- Discussions : https://github.com/FRA-222/OpenSailingRC-Anemometer-v2/discussions

### **Contact**
- Email : support@opensailingrc.org
- Discord : OpenSailingRC Community

---

## 📜 Licence

**MIT License**

Copyright (c) 2025 OpenSailingRC

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED.

---

## 🙏 Remerciements

- **M5Stack** pour le hardware AtomS3
- **Espressif** pour l'ESP32-S3 et ESPTool
- **La communauté** pour les retours et contributions

---

## ✅ Checklist Installation

Avant de considérer l'installation réussie :

- [ ] Firmware téléchargé (903 KB)
- [ ] Checksum vérifié
- [ ] M5Burner installé (ou ESPTool)
- [ ] AtomS3 connecté
- [ ] Flash réussi (100%)
- [ ] LED RGB fonctionne
- [ ] WiFi Manager accessible
- [ ] Mesures anémomètre OK

---

**🎉 Bonne mesure du vent avec OpenSailingRC Anemometer v2 ! ⛵**

Si vous aimez ce projet, donnez-lui une ⭐ sur GitHub !

---

**Version** : 1.0.0  
**Date** : 5 octobre 2025  
**Auteur** : OpenSailingRC Team  
**Licence** : MIT