# Release Notes - OpenSailingRC-Anemometer-v2 v1.0.0

**Date de release :** 21 septembre 2025  
**Auteur :** Philippe Hubert  
**Licence :** GPL v3.0

## 🌪️ Première release officielle de l'anémomètre !

Cette première version stable d'OpenSailingRC-Anemometer-v2 offre un système complet de mesure et transmission de données de vent pour voiliers RC, basé sur M5Stack Atom S3.

## ✨ Nouvelles fonctionnalités

### 🌬️ Mesure de vitesse de vent
- **Capteur anémomètre** haute précision avec calibration automatique
- **Affichage temps réel** de la vitesse de vent sur écran LCD 128x128
- **Unités configurables** : m/s, km/h, nœuds, mph
- **Échantillonnage** à 2 secondes pour stabilité optimale

### 📡 Communication sans fil
- **Transmission WiFi** des données vers stations de réception
- **Protocole standardisé** compatible écosystème OpenSailingRC
- **Identification unique** du dispositif pour multi-anémomètres
- **Gestion robuste** des connexions et reconnexions WiFi

### 📊 Affichage et logging
- **Interface visuelle** claire avec couleurs selon intensité du vent
- **Logging multi-support** : Série, écran, et stockage externe
- **Données horodatées** pour analyse historique
- **Indicateurs visuels** de statut système et connectivité

### 🔧 Architecture modulaire
- **Classes spécialisées** : Anemometer, Communication, Logger
- **Code maintenable** avec documentation complète
- **Configuration flexible** via paramètres compilés
- **Debug intégré** pour diagnostic et développement

## 🔧 Améliorations techniques

### Performance
- **Mesures stabilisées** avec filtrage anti-rebond
- **Transmission efficace** avec compression des données
- **Affichage fluide** optimisé pour ESP32-S3
- **Gestion mémoire** optimisée pour fonctionnement 24/7

### Robustesse
- **Gestion d'erreurs** complète pour tous les capteurs
- **Recovery automatique** en cas de perte de signal
- **Validation des mesures** avec limites physiques
- **Protection** contre les interférences électromagnétiques

### Intégration
- **Compatible Grove** pour connexion facile des capteurs
- **Standards OpenSailingRC** pour interopérabilité
- **API uniforme** pour intégration dans systèmes plus larges
- **Extensibilité** pour capteurs supplémentaires

## 📋 Contenu de la release

### Binaires
- `firmware.bin` (950 KB) - Firmware principal anémomètre
- `bootloader.bin` (28 KB) - Bootloader ESP32-S3
- `partitions.bin` (3 KB) - Table des partitions

### Documentation
- `FLASH_INSTRUCTIONS.md` - Guide de flash spécialisé ESP32-S3
- `RELEASE_NOTES.md` - Ces notes de release
- Lien vers documentation technique complète

## 🎯 Configuration requise

### Hardware
- **M5Stack Atom S3** (ESP32-S3 basé)
- **Anémomètre** compatible (contact reed, signal analogique, ou numérique)
- **Alimentation** : USB-C ou batterie externe 3.7V
- **Connecteurs Grove** pour extension

### Logiciels
- **esptool** v4.0+ (pour flash manuel)
- **PlatformIO** v6.0+ (pour développement)
- **WiFi Manager** pour configuration réseau

### Capteurs supportés
- **Anémomètres à coupelles** avec contact reed
- **Capteurs à ultrasons** (via interface analogique)
- **Capteurs à fil chaud** (avec conditionnement de signal)
- **Capteurs numériques** I2C/SPI

## 🚀 Utilisation rapide

1. **Flash** le firmware selon `FLASH_INSTRUCTIONS.md`
2. **Connecter** l'anémomètre aux ports Grove
3. **Configurer** le WiFi via interface de gestion
4. **Positionner** l'anémomètre sur le voilier RC
5. **Valider** la transmission des données vers Display/Base

## 🔄 Écosystème OpenSailingRC

Cette release s'intègre parfaitement avec :
- **OpenSailingRC-Display** - Affichage GPS avec données de vent
- **OpenSailingRC-GPS** - Module GPS embarqué
- **OpenSailingRC-Base** - Station de base télécommande
- **Applications tierces** via API standardisée

## 🌪️ Spécifications techniques

### Plage de mesure
- **Vitesse vent** : 0 à 50 m/s (0 à 180 km/h, 0 à 97 nœuds)
- **Résolution** : 0.1 m/s
- **Précision** : ±2% à 10 m/s
- **Temps de réponse** : < 1 seconde

### Environnement
- **Température** : -20°C à +60°C
- **Humidité** : 0 à 95% (non condensante)
- **Étanchéité** : IP54 (avec boîtier approprié)
- **Vibrations** : Résistant aux chocs navigation RC

### Communication
- **Protocole** : WiFi 802.11 b/g/n
- **Portée** : 50-100m en champ libre
- **Fréquence transmission** : 0.5 Hz (toutes les 2 secondes)
- **Format données** : JSON structuré

## 🐛 Problèmes connus

### Limitations mineures
- **Calibration automatique** : Peut nécessiter ajustement manuel pour certains anémomètres
- **WiFi portée** : Limitée par puissance ESP32-S3 (sera améliorée avec antenne externe)
- **Interface configuration** : Nécessite connection série pour paramètres avancés

### Workarounds
- **Calibration** : Valeurs par défaut conviennent à la plupart des anémomètres standards
- **Portée WiFi** : Utiliser répéteur ou positionnement optimal
- **Configuration** : Interface web prévue pour v1.1

## 🔜 Roadmap v1.1

- Interface web de configuration WiFi
- Support anémomètres ultrasoniques
- Historique des données avec graphiques
- Mode étalonnage assisté
- Support antenne externe pour portée étendue
- Integration capteur direction du vent

## 🧪 Tests et validation

### Tests effectués
- **Calibration** : Validation avec anémomètre de référence
- **Durabilité** : Tests 48h en continu
- **Portée WiFi** : Validation 100m en conditions réelles
- **Précision** : Comparaison avec station météo professionnelle

### Environnements testés
- **Navigation RC** : Bassin et plan d'eau libre
- **Conditions météo** : Vent 0-25 m/s, pluie légère
- **Température** : 5°C à 40°C
- **Vibrations** : Simulation environnement RC

## 🙏 Remerciements

- **M5Stack** pour l'excellent hardware Atom S3
- **Espressif** pour ESP32-S3 et outils de développement
- **Communauté RC Sailing** pour les retours et tests
- **Contributeurs OpenSailingRC** pour l'intégration écosystème

## 📞 Support

- **Documentation** : [GitHub Wiki](https://github.com/FRA-222/OpenSailingRC-Anemometer-v2/wiki)
- **Issues** : [GitHub Issues](https://github.com/FRA-222/OpenSailingRC-Anemometer-v2/issues)
- **Discussions** : [GitHub Discussions](https://github.com/FRA-222/OpenSailingRC-Anemometer-v2/discussions)
- **Forum RC** : [Section anémomètres](https://forum.opensailing.rc)

## 🔗 Ressources

### Documentation technique
- [Schémas de connexion](docs/hardware/connections.md)
- [API Communication](docs/api/communication.md)
- [Guide de calibration](docs/calibration/guide.md)
- [Troubleshooting](docs/troubleshooting/common-issues.md)

### Intégrations
- [Plugin Display](integrations/display-plugin.md)
- [API Base Station](integrations/base-api.md)
- [Export données](integrations/data-export.md)

---

**Téléchargement :** [Release v1.0.0](https://github.com/FRA-222/OpenSailingRC-Anemometer-v2/releases/tag/v1.0.0)  
**Code source :** [GitHub Repository](https://github.com/FRA-222/OpenSailingRC-Anemometer-v2)  
**Licence :** [GPL v3.0](https://github.com/FRA-222/OpenSailingRC-Anemometer-v2/blob/main/LICENSE.md)