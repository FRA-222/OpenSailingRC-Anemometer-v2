#!/bin/bash

# Script de création du firmware fusionné pour OpenSailingRC Anemometer v2
# Compatible M5Burner - Flash à l'adresse 0x0

echo "🔧 Création du firmware fusionné pour M5Stack AtomS3..."

# Configuration
VERSION="1.0.0"
BUILD_DIR=".pio/build/m5stack-atomsS3"
RELEASE_DIR="releases/v${VERSION}"

# Vérifier que les fichiers sources existent
if [ ! -f "${BUILD_DIR}/bootloader.bin" ]; then
    echo "❌ Erreur: bootloader.bin non trouvé"
    echo "   Veuillez compiler le projet avec: platformio run"
    exit 1
fi

if [ ! -f "${BUILD_DIR}/partitions.bin" ]; then
    echo "❌ Erreur: partitions.bin non trouvé"
    echo "   Veuillez compiler le projet avec: platformio run"
    exit 1
fi

if [ ! -f "${BUILD_DIR}/firmware.bin" ]; then
    echo "❌ Erreur: firmware.bin non trouvé"
    echo "   Veuillez compiler le projet avec: platformio run"
    exit 1
fi

# Créer le répertoire de release si nécessaire
mkdir -p "${RELEASE_DIR}"

# Copier les fichiers individuels (pour développeurs)
echo "📦 Copie des fichiers individuels..."
cp "${BUILD_DIR}/bootloader.bin" "${RELEASE_DIR}/"
cp "${BUILD_DIR}/partitions.bin" "${RELEASE_DIR}/"
cp "${BUILD_DIR}/firmware.bin" "${RELEASE_DIR}/"

# Créer le firmware fusionné
MERGED_FILE="${RELEASE_DIR}/OpenSailingRC_Anemometer_v${VERSION}_MERGED.bin"

echo "🔀 Fusion des binaires..."
python3 -m esptool --chip esp32s3 merge_bin \
    -o "${MERGED_FILE}" \
    --flash_mode dio \
    --flash_freq 80m \
    --flash_size 8MB \
    0x0 "${BUILD_DIR}/bootloader.bin" \
    0x8000 "${BUILD_DIR}/partitions.bin" \
    0x10000 "${BUILD_DIR}/firmware.bin"

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Firmware fusionné créé avec succès!"
    echo ""
    echo "📁 Fichier créé:"
    ls -lh "${MERGED_FILE}"
    echo ""
    echo "📍 Utilisation avec M5Burner:"
    echo "   1. Ouvrir M5Burner"
    echo "   2. Custom Firmware → Browse"
    echo "   3. Sélectionner: $(basename ${MERGED_FILE})"
    echo "   4. ⚠️  IMPORTANT: Adresse = 0x0 (pas 0x10000)"
    echo "   5. ✅ Cocher: Erase Flash"
    echo "   6. BURN"
    echo ""
    echo "📍 Utilisation avec ESPTool:"
    echo "   python3 -m esptool --chip esp32s3 --port PORT write_flash 0x0 ${MERGED_FILE}"
    echo ""
else
    echo "❌ Erreur lors de la création du firmware fusionné"
    exit 1
fi
