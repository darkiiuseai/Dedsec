# Dedsec Tool - Outil de développement et d'analyse système

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build Status](https://github.com/votrecompte/dedsec-tool/actions/workflows/build.yml/badge.svg)](https://github.com/votrecompte/dedsec-tool/actions)
[![Version](https://img.shields.io/github/v/release/votrecompte/dedsec-tool)](https://github.com/votrecompte/dedsec-tool/releases)

Un outil en ligne de commande inspiré de Watch Dogs 2 pour gérer vos outils de développement et analyser votre système.

## Fonctionnalités

- 🛠️ Installation facile des outils de développement courants
- 🔍 Vérification des logiciels installés
- 💻 Informations détaillées sur le système
- 🧹 Outils de maintenance système
- 🎨 Interface en couleurs inspirée de Watch Dogs 2
- ⚡ Rapide et léger

## Prérequis

- Windows 10/11
- Visual Studio 2019 ou supérieur avec le support C++
- CMake 3.10 ou supérieur
- Winget (recommandé pour les installations automatiques)

## Installation

### Méthode 1 : Téléchargement du binaire

1. Téléchargez la dernière version depuis la [page des releases](https://github.com/votrecompte/dedsec-tool/releases)
2. Extrayez l'archive ZIP
3. Exécutez `dedsec.exe` depuis l'invite de commandes

### Méthode 2 : Compilation depuis les sources

1. Clonez le dépôt :
   ```bash
   git clone https://github.com/votrecompte/dedsec-tool.git
   cd dedsec-tool
   ```

2. Créez un répertoire de build et compilez :
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build . --config Release
   ```

3. L'exécutable sera disponible dans le dossier `build/Release/`

## Utilisation

```
dedsec [command]
```

### Commandes disponibles

- `install` : Affiche le menu d'installation des outils
- `list` : Liste les logiciels installés
- `system` : Affiche les informations système
- `clean` : Nettoie les fichiers temporaires
- `update` : Met à jour les outils installés
- `help` : Affiche l'aide

## Développement

### Structure du projet

```
dedsec-tool/
├── CMakeLists.txt    # Fichier de configuration CMake
├── src/              # Code source
│   └── main.cpp      # Point d'entrée principal
├── include/          # Fichiers d'en-tête
├── tests/            # Tests unitaires
└── README.md         # Ce fichier
```

### Contribution

Les contributions sont les bienvenues ! Voici comment contribuer :

1. Forkez le projet
2. Créez une branche pour votre fonctionnalité (`git checkout -b feature/AmazingFeature`)
3. Committez vos changements (`git commit -m 'Add some AmazingFeature'`)
4. Poussez vers la branche (`git push origin feature/AmazingFeature`)
5. Ouvrez une Pull Request

## Licence

Distribué sous la licence MIT. Voir le fichier `LICENSE` pour plus d'informations.

## Auteur

**Votre Nom** - [@votretwitter](https://twitter.com/votretwitter)

## Remerciements

- Inspiration : Watch Dogs 2 (Ubisoft)
- Icônes par [Font Awesome](https://fontawesome.com/)
- [CMake](https://cmake.org/)
- [Visual Studio](https://visualstudio.microsoft.com/)

---

<p align="center">
  <img src="https://i.imgur.com/XYZ1234.png" alt="Dedsec Logo" width="200"/>
</p>
