# 🔥 Firmware Fusionné M5Burner - Anemometer v2

**Version** : 1.0.0  
**Date** : 5 octobre 2025  
**Plateforme** : M5Stack AtomS3 (ESP32-S3)

---

## 🎯 Pourquoi un Firmware Fusionné ?

### **Le Problème**

Un firmware ESP32-S3 complet nécessite **3 fichiers** :

1. **bootloader.bin** (0x0) - 15 KB - Initialise l'ESP32-S3
2. **partitions.bin** (0x8000) - 3 KB - Table des partitions
3. **firmware.bin** (0x10000) - 839 KB - Application principale

**Problème avec M5Burner** :
- M5Burner ne peut flasher qu'**un seul fichier** à la fois
- Flasher uniquement `firmware.bin` à 0x10000 → **REBOOT INFINI**
- Cause : Bootloader manquant

### **La Solution**

**Firmware fusionné** = Bootloader + Partitions + Firmware en **un seul fichier**

```
OpenSailingRC_Anemometer_v1.0.0_MERGED.bin (903 KB)
├─ 0x0000  : Bootloader (15 KB)
├─ 0x8000  : Partitions (3 KB)
└─ 0x10000 : Application (839 KB)
```

**Avantages** :
- ✅ **1 seul fichier** à gérer
- ✅ **Compatible M5Burner** (interface graphique)
- ✅ **Installation en 3 clics**
- ✅ **Accessible à tous** (pas de ligne de commande)
- ✅ **Zéro risque d'erreur** (tout est inclus)

---

## 📦 Contenu du Firmware

### **Structure du Fichier MERGED.bin**

```
Adresse     Taille    Contenu                  Fichier Source
────────────────────────────────────────────────────────────────
0x00000     15 KB     Bootloader ESP32-S3      bootloader.bin
0x08000     3 KB      Table de Partitions      partitions.bin
0x10000     839 KB    Application Anémomètre   firmware.bin
────────────────────────────────────────────────────────────────
TOTAL       ~903 KB   Firmware Complet         MERGED.bin
```

### **Partitions Flash (8 MB)**

```
# Name,   Type, SubType, Offset,  Size
nvs,      data, nvs,     0x9000,  0x5000   # 20 KB - WiFi credentials
otadata,  data, ota,     0xe000,  0x2000   # 8 KB  - OTA Data
app0,     app,  ota_0,   0x10000, 0x1E0000 # 1.9 MB - Application
app1,     app,  ota_1,   0x1F0000,0x1E0000 # 1.9 MB - OTA Update
spiffs,   data, spiffs,  0x3D0000,0x30000  # 192 KB - Filesystem
```

**Total utilisé** : ~900 KB / 8 MB (11%)

---

## 🔧 Création du Firmware Fusionné

### **Script Automatique**

Le script `create_merged_firmware.sh` fait tout automatiquement :

```bash
#!/bin/bash
# Compile le projet
platformio run

# Crée le firmware fusionné
./create_merged_firmware.sh
```

### **Commande Manuelle**

Si vous préférez créer le firmware manuellement :

```bash
python3 -m esptool --chip esp32s3 merge_bin \
    -o OpenSailingRC_Anemometer_v1.0.0_MERGED.bin \
    --flash_mode dio \
    --flash_freq 80m \
    --flash_size 8MB \
    0x0 .pio/build/m5stack-atomsS3/bootloader.bin \
    0x8000 .pio/build/m5stack-atomsS3/partitions.bin \
    0x10000 .pio/build/m5stack-atomsS3/firmware.bin
```

---

## 📱 Installation avec M5Burner

### **Configuration Critique**

| Paramètre | ❌ Échec | ✅ Succès |
|-----------|----------|-----------|
| **Fichier** | firmware.bin | **MERGED.bin** |
| **Adresse** | 0x10000 | **0x0** ⚠️ |
| **Erase Flash** | Non | **OUI** ✅ |
| **Chip** | ESP32 | **ESP32-S3** |

### **Procédure Complète**

```
1. M5Burner → Custom Firmware
2. Browse → OpenSailingRC_Anemometer_v1.0.0_MERGED.bin
3. ⚠️  CHANGER ADRESSE : 0x10000 → 0x0
4. ✅ Cocher "Erase Flash"
5. Sélectionner port série
6. BURN
7. Attendre ~30 secondes
8. ✅ L'AtomS3 redémarre
```

**⏱️ Temps total** : 1-2 minutes

---

## 🧪 Tests de Validation

### **Test 1 : Flash Réussi**

**Commande** :
```bash
python3 -m esptool --chip esp32s3 --port PORT write_flash 0x0 MERGED.bin
```

**Résultat attendu** :
```
Wrote 923840 bytes (XXXXX compressed) at 0x00000000
Hash of data verified.
Leaving...
Hard resetting via RTS pin...
```

### **Test 2 : Démarrage de l'AtomS3**

**Séquence LED** :
1. **Rouge** - Démarrage (1 sec)
2. **Bleu** - Configuration WiFi (si pas configuré)
3. **Vert** - Fonctionnement normal

**Logs Série (115200 baud)** :
```
rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
...
[I] WiFiManager: Starting configuration portal
[I] Anemometer: Ready to measure
✅ Pas de "invalid header"
✅ Pas de reboot en boucle
```

### **Test 3 : WiFi Manager**

**Au premier démarrage** :
1. L'AtomS3 crée un AP : `OpenSailingRC-Anemometer-XXXXXX`
2. Se connecter au WiFi
3. Ouvrir : http://192.168.4.1
4. Interface de configuration apparaît ✅

---

## 🆚 Comparaison des Méthodes

### **M5Burner (Firmware Fusionné)**

**Avantages** :
- ✅ Interface graphique
- ✅ 1 seul fichier
- ✅ Accessible aux débutants
- ✅ Compatible Windows/Mac/Linux

**Inconvénients** :
- ⚠️ Doit changer l'adresse à 0x0
- ⚠️ Plus lent que ESPTool

**Public cible** : Tous utilisateurs

---

### **ESPTool (Ligne de Commande)**

**Avantages** :
- ✅ Plus rapide
- ✅ Plus de contrôle
- ✅ Scriptable
- ✅ Compatible firmware fusionné ou fichiers séparés

**Inconvénients** :
- ⚠️ Ligne de commande
- ⚠️ Installation Python requise

**Public cible** : Développeurs, utilisateurs avancés

---

### **PlatformIO**

**Avantages** :
- ✅ Flash automatique après compilation
- ✅ Gestion des dépendances
- ✅ Monitoring série intégré

**Inconvénients** :
- ⚠️ Nécessite le code source
- ⚠️ Installation PlatformIO

**Public cible** : Développeurs

---

## ⚠️ Problèmes Courants

### **Problème 1 : Reboot Infini**

**Symptôme** :
```
rst:0x7 (TG0WDT_SYS_RESET),boot:0x13
invalid header: 0x2068746f
ets_main.c 329
```

**Causes** :
1. Adresse incorrecte (0x10000 au lieu de 0x0)
2. Fichier `firmware.bin` au lieu de `MERGED.bin`
3. Bootloader manquant

**Solution** :
```bash
# 1. Effacer la flash
python3 -m esptool --chip esp32s3 --port PORT erase_flash

# 2. Reflasher MERGED.bin à 0x0
python3 -m esptool --chip esp32s3 --port PORT write_flash 0x0 MERGED.bin
```

---

### **Problème 2 : M5Burner "No Serial Data"**

**Causes** :
- Câble USB défectueux
- Drivers CH9102 non installés
- Mauvais port série

**Solutions** :
1. Essayer un autre câble USB-C
2. Installer drivers : https://docs.m5stack.com/en/download
3. Vérifier le port dans M5Burner
4. Maintenir le bouton de l'AtomS3 pendant connexion

---

### **Problème 3 : "Hash Does Not Match"**

**Cause** : Fichier corrompu

**Solution** :
```bash
# Vérifier l'intégrité
shasum -a 256 OpenSailingRC_Anemometer_v1.0.0_MERGED.bin

# Comparer avec le checksum officiel dans checksums.sha256
cat checksums.sha256

# Si différent, re-télécharger le fichier
```

---

## 📊 Performances

### **Temps de Flash**

| Méthode | Baud Rate | Temps |
|---------|-----------|-------|
| **M5Burner** | 115200 | ~60 sec |
| **M5Burner** | 460800 | ~30 sec |
| **ESPTool** | 115200 | ~45 sec |
| **ESPTool** | 921600 | ~20 sec |
| **PlatformIO** | 460800 | ~25 sec |

### **Taille des Fichiers**

| Fichier | Taille | % Flash |
|---------|--------|---------|
| bootloader.bin | 15 KB | 0.2% |
| partitions.bin | 3 KB | 0.04% |
| firmware.bin | 839 KB | 10.5% |
| **MERGED.bin** | **903 KB** | **11%** |
| Flash totale | 8 MB | 100% |

**Espace libre** : ~7 MB pour OTA, logs, données

---

## 🔐 Sécurité

### **Checksums SHA256**

Toujours vérifier l'intégrité avant de flasher :

```bash
# Calculer le checksum
shasum -a 256 OpenSailingRC_Anemometer_v1.0.0_MERGED.bin

# Comparer avec checksums.sha256
cat releases/v1.0.0/checksums.sha256
```

### **Signature (Future)**

**v1.1.0** inclura :
- Signature cryptographique du firmware
- Vérification automatique avant flash
- Protection contre firmware modifié

---

## 📚 Documentation

### **Pour Tous**
- `M5BURNER_INSTRUCTIONS.txt` - Instructions détaillées M5Burner
- `FLASH_INSTRUCTIONS.md` - Toutes les méthodes de flash

### **Pour Développeurs**
- `create_merged_firmware.sh` - Script de création
- `RELEASE_NOTES.md` - Notes de version
- `README.md` - Documentation projet

---

## 🚀 Prochaines Versions

### **v1.1.0 (Planifiée)**
- [ ] OTA (Over-The-Air) updates via WiFi
- [ ] Signature cryptographique firmware
- [ ] Interface web configuration avancée
- [ ] Logs détaillés sur flash interne

### **v1.2.0 (Future)**
- [ ] Support Bluetooth BLE
- [ ] Mode économie d'énergie
- [ ] Calibration automatique
- [ ] Application mobile dédiée

---

## 📞 Support

**GitHub Issues** : https://github.com/FRA-222/OpenSailingRC-Anemometer-v2/issues  
**Documentation** : https://github.com/FRA-222/OpenSailingRC-Anemometer-v2  
**Email** : support@opensailingrc.org

---

## ✅ Checklist Installation

Avant de considérer l'installation réussie :

- [ ] Firmware fusionné téléchargé (903 KB)
- [ ] Checksum SHA256 vérifié
- [ ] M5Burner installé
- [ ] Drivers CH9102 installés (si nécessaire)
- [ ] AtomS3 connecté (port détecté)
- [ ] Adresse changée à **0x0** ⚠️
- [ ] "Erase Flash" coché ✅
- [ ] Flash réussi (100%)
- [ ] AtomS3 redémarre sans reboot
- [ ] LED RGB fonctionne
- [ ] WiFi Manager accessible

---

**Date de création** : 5 octobre 2025  
**Auteur** : Philippe Hubert  
**Version** : 1.0.0  
**Plateforme** : M5Stack AtomS3 (ESP32-S3)

---

*Le firmware fusionné rend l'installation accessible à tous ! 🎉*