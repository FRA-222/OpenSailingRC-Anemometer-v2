# Mise à jour des structures de données - 23 novembre 2025

## Changements effectués

### 1. Structure `AnemometerData` / `struct_message_Anemometer`

**Ajout du champ `timestamp`** pour permettre la détection de timeout (5 secondes) sur le Display.

#### Ancienne structure :
```cpp
typedef struct {
    int8_t messageType;      // 1 = Boat, 2 = Anemometer
    char anemometerId[18];   // MAC address as string
    uint8_t macAddress[6];   // MAC address of the device
    uint32_t sequenceNumber; // Sequence number
    float windSpeed;         // Wind speed value
} AnemometerData;
```

#### Nouvelle structure :
```cpp
typedef struct {
    int8_t messageType;      // 1 = Boat, 2 = Anemometer
    char anemometerId[18];   // MAC address as string
    uint8_t macAddress[6];   // MAC address of the device
    uint32_t sequenceNumber; // Sequence number
    float windSpeed;         // Wind speed value
    unsigned long timestamp; // Timestamp of the measurement (NEW)
} AnemometerData;
```

### 2. Structure `struct_message_Boat`

**Ajout du champ `timestamp`** pour permettre la détection de timeout (5 secondes) sur le Display.

#### Ancienne structure :
```cpp
typedef struct struct_message_Boat {
    int8_t messageType;
    char name[18];
    int boatId;
    uint32_t sequenceNumber;
    uint32_t gpsTimestamp;
    float latitude;
    float longitude;
    float speed;
    float heading;
    uint8_t satellites;
} struct_message_Boat;
```

#### Nouvelle structure :
```cpp
typedef struct struct_message_Boat {
    int8_t messageType;
    char name[18];
    int boatId;
    uint32_t sequenceNumber;
    uint32_t gpsTimestamp;
    float latitude;
    float longitude;
    float speed;
    float heading;
    uint8_t satellites;
    unsigned long timestamp; // Timestamp of the measurement (NEW)
} struct_message_Boat;
```

### 3. Suppression de `windDirection` de `struct_message_Anemometer`

**La direction du vent ne vient PAS de l'anémomètre.**

La direction du vent sera fournie par les **bouées GPS** dans une structure séparée.
Le Display recevra cette donnée via les paramètres optionnels de `drawDisplay()`.

## Projets mis à jour

### ✅ OpenSailingRC-Display
- [x] Ajout de `timestamp` dans `struct_message_Boat`
- [x] Ajout de `timestamp` dans `struct_message_Anemometer`
- [x] Suppression de `struct_message_Anemometer_Legacy`
- [x] Mise à jour des callbacks ESP-NOW pour initialiser les timestamps
- [x] Affichage de `--` après 5 secondes sans données
- [x] Fonction `drawDisplay()` étendue avec paramètres `windDirection` et `windDirTimestamp`

### ✅ OpenSailingRC-Anemometer-v2
- [x] Ajout de `timestamp` dans `AnemometerData` (Communication.h)
- [x] Initialisation de `data.timestamp = millis()` dans main.cpp
- [x] Compilation réussie

### ⏳ Navigation GPS (Bateau)
**À METTRE À JOUR MANUELLEMENT**

Le projet "Navigation GPS" doit être mis à jour pour ajouter le champ `timestamp` dans la structure.

#### Fichier à modifier : `Navigation GPS/src/*.cpp` (là où la structure boat est préparée)

Initialiser le timestamp à 0 (sera rempli par le Display à la réception) :
```cpp
boatData.timestamp = 0; // Pas utilisé à l'envoi - Display le remplira
```

#### Exemple de code typique :
```cpp
// Préparation des données GPS
struct_message_Boat boatData;
boatData.messageType = 1;
strcpy(boatData.name, macAddress.c_str());
boatData.boatId = BOAT_ID;
boatData.sequenceNumber = sequenceNumber++;
boatData.gpsTimestamp = gpsTimestamp;
boatData.latitude = latitude;
boatData.longitude = longitude;
boatData.speed = speed;
boatData.heading = heading;
boatData.satellites = satellites;
boatData.timestamp = 0; // ← AJOUTER CETTE LIGNE (Display le remplira à la réception)

// Envoi ESP-NOW
esp_now_send(displayAddress, (uint8_t*)&boatData, sizeof(boatData));
```

## Compatibilité

### Rétrocompatibilité
- ❌ **INCOMPATIBILITÉ** : L'ancien code du bateau (sans `timestamp`) enverra des paquets de taille incorrecte
- ❌ Le Display rejettera les paquets trop courts avec `if (len < sizeof(struct_message_Boat))`
- ✅ L'anémomètre envoie maintenant des paquets avec `timestamp`

### Action requise
**Il est IMPÉRATIF de mettre à jour le projet "Navigation GPS" avant de tester le système complet.**

Sans cette mise à jour :
1. Le Display ne recevra pas les données du bateau (paquet trop court)
2. L'affichage BOAT affichera `--` en permanence
3. Seules les données WIND (anémomètre) seront affichées correctement

## Tests recommandés

Après mise à jour du projet Navigation GPS :

1. **Test anémomètre seul**
   - Vérifier que WIND affiche les valeurs
   - Éteindre l'anémomètre → vérifier que `--` apparaît après 5s

2. **Test bateau seul**
   - Vérifier que BOAT affiche vitesse et cap
   - Éteindre le bateau → vérifier que `--` apparaît après 5s

3. **Test complet**
   - Allumer anémomètre + bateau
   - Vérifier l'affichage des 4 lignes
   - WIND direction doit afficher `--` (données non disponibles des bouées)

## Tailles des structures

```
struct_message_Boat:        ~60 bytes (avec timestamp)
struct_message_Anemometer:  ~36 bytes (avec timestamp)
```

## Notes importantes

- **Le timestamp est géré UNIQUEMENT par le Display** : il marque l'heure de réception locale
- Les émetteurs (bateau/anémomètre) mettent `timestamp = 0` (non utilisé)
- Le Display écrase ce timestamp avec `millis()` lors de la réception dans le callback ESP-NOW
- Le Display compare ensuite son propre `millis()` actuel avec le timestamp de réception
- Pas de problème de synchronisation car tout est calculé sur la même horloge (Display)
- Le timeout de 5 secondes est codé en dur dans Display.cpp
- La direction du vent sera ajoutée ultérieurement via une structure des bouées GPS
