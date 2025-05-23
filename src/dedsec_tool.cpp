#include "include/dedsec.hpp"

namespace DedSec {
    
    DedSecTool::DedSecTool() : isAuthenticated(false), currentUser("Anonymous") {
        initializeHiddenCommands();
    }
    
    DedSecTool::~DedSecTool() {
        consoleColor.resetColor();
    }
    
    void DedSecTool::initializeHiddenCommands() {
        hiddenCommands["ghost"] = "Mode fantôme activé";
        hiddenCommands["matrix"] = "Pluie de code Matrix";
        hiddenCommands["hack"] = "Simulation de hack";
        hiddenCommands["breach"] = "Brèche de sécurité simulée";
        hiddenCommands["ctOS"] = "Accès au système ctOS";
        hiddenCommands["wrench"] = "Outil de Wrench activé";
        hiddenCommands["aiden"] = "Mode Aiden Pearce";
        hiddenCommands["marcus"] = "Mode Marcus Holloway";
    }
    
    void DedSecTool::showLogo() {
        clearScreen();
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        
        cout << R"(
██████╗ ███████╗██████╗ ███████╗███████╗ ██████╗
██╔══██╗██╔════╝██╔══██╗██╔════╝██╔════╝██╔════╝
██║  ██║█████╗  ██║  ██║███████╗█████╗  ██║     
██║  ██║██╔══╝  ██║  ██║╚════██║██╔══╝  ██║     
██████╔╝███████╗██████╔╝███████║███████╗╚██████╗
╚═════╝ ╚══════╝╚═════╝ ╚══════╝╚══════╝ ╚═════╝
)" << endl;
        
        consoleColor.setColor(ConsoleColor::BRIGHT_RED);
        cout << R"(
    ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
   ██ DEDSEC HACKING COLLECTIVE TOOLKIT ██
    ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
)" << endl;
        
        consoleColor.setColor(ConsoleColor::BRIGHT_YELLOW);
        cout << "    ┌─────────────────────────────────────────┐" << endl;
        cout << "    │  \"We are DedSec. We are everywhere.\"   │" << endl;
        cout << "    │     Développé par: Darkii               │" << endl;
        cout << "    │     Version: 2.0 - Watch Dogs Edition │" << endl;
        cout << "    └─────────────────────────────────────────┘" << endl;
        
        consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
        cout << "\n    [SYSTÈME INITIALISÉ] - " << getCurrentTime() << endl;
        
        consoleColor.setColor(ConsoleColor::WHITE);
        cout << "\n    Tapez 'help' pour voir les commandes disponibles" << endl;
        cout << "    Tapez 'menu' pour accéder au menu principal" << endl;
        cout << "\n" << string(60, '=') << endl;
    }
    
    void DedSecTool::showWelcomeMessage() {
        Animation::typeWriter("[DEDSEC] Connexion au réseau DedSec...", 30);
        Animation::showLoading("Authentification", 2);
        
        consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
        cout << "[DEDSEC] Accès autorisé. Bienvenue, hacker." << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        playSound("success");
    }
    
    void DedSecTool::authenticate() {
        string username, password;
        
        consoleColor.setColor(ConsoleColor::BRIGHT_YELLOW);
        cout << "[DEDSEC] Authentification requise" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        cout << "Nom d'utilisateur: ";
        getline(cin, username);
        
        cout << "Mot de passe: ";
        getline(cin, password);
        
        Animation::showLoading("Vérification des identifiants", 2);
        
        // Authentification simple (pour démonstration)
        if (username == "dedsec" && password == "watchdogs") {
            isAuthenticated = true;
            currentUser = username;
            consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
            cout << "[DEDSEC] Authentification réussie!" << endl;
            playSound("success");
        } else {
            consoleColor.setColor(ConsoleColor::BRIGHT_RED);
            cout << "[DEDSEC] Identifiants incorrects!" << endl;
            playSound("error");
        }
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
    void DedSecTool::showHelp() {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "\n╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                    COMMANDES DISPONIBLES                    ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        vector<pair<string, string>> commands = {
            {"help", "Affiche cette aide"},
            {"menu", "Affiche le menu principal"},
            {"install [logiciel]", "Installe un logiciel"},
            {"list", "Liste les logiciels installés"},
            {"system", "Informations système"},
            {"clean", "Nettoie le système"},
            {"update", "Vérifie les mises à jour"},
            {"network", "Menu des outils réseau"},
            {"security", "Menu des outils de sécurité"},
            {"dev", "Menu des outils de développement"},
            {"monitor", "Surveillance système"},
            {"scan", "Scan de vulnérabilités"},
            {"auth", "Authentification DedSec"},
            {"history", "Historique des commandes"},
            {"clear", "Efface l'écran"},
            {"exit", "Quitte le programme"}
        };
        
        for (const auto& [cmd, desc] : commands) {
            consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
            cout << "  " << setw(20) << left << cmd;
            consoleColor.setColor(ConsoleColor::WHITE);
            cout << " - " << desc << endl;
        }
        
        consoleColor.setColor(ConsoleColor::BRIGHT_YELLOW);
        cout << "\n[ASTUCE] Certaines commandes cachées existent... Explorez!" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
    void DedSecTool::showMainMenu() {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "\n╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                      MENU PRINCIPAL                         ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        vector<pair<string, string>> menuItems = {
            {"1", "🛠️  Gestion des logiciels"},
            {"2", "💻 Informations système"},
            {"3", "🌐 Outils réseau"},
            {"4", "🔒 Outils de sécurité"},
            {"5", "⚡ Outils de développement"},
            {"6", "🔍 Surveillance et monitoring"},
            {"7", "🎯 Menu avancé"},
            {"8", "❓ Aide"},
            {"0", "🚪 Quitter"}
        };
        
        for (const auto& [num, desc] : menuItems) {
            consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
            cout << "  [" << num << "] ";
            consoleColor.setColor(ConsoleColor::WHITE);
            cout << desc << endl;
        }
        
        cout << "\nChoisissez une option: ";
    }
    
    void DedSecTool::showAdvancedMenu() {
        consoleColor.setColor(ConsoleColor::BRIGHT_RED);
        cout << "\n╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                     MENU AVANCÉ                             ║" << endl;
        cout << "║                  [ACCÈS RESTREINT]                          ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        if (!isAuthenticated) {
            consoleColor.setColor(ConsoleColor::BRIGHT_RED);
            cout << "[ACCÈS REFUSÉ] Authentification requise!" << endl;
            consoleColor.setColor(ConsoleColor::WHITE);
            return;
        }
        
        vector<pair<string, string>> advancedItems = {
            {"1", "🎭 Mode fantôme"},
            {"2", "🌊 Pluie Matrix"},
            {"3", "💀 Simulation de hack"},
            {"4", "⚡ Brèche système"},
            {"5", "🎯 Scan de vulnérabilités avancé"},
            {"6", "🔥 Outils cachés"},
            {"0", "🔙 Retour"}
        };
        
        for (const auto& [num, desc] : advancedItems) {
            consoleColor.setColor(ConsoleColor::BRIGHT_YELLOW);
            cout << "  [" << num << "] ";
            consoleColor.setColor(ConsoleColor::WHITE);
            cout << desc << endl;
        }
        
        cout << "\nChoisissez une option: ";
    }
    
    void DedSecTool::showNetworkMenu() {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "\n╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                    OUTILS RÉSEAU                            ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        vector<pair<string, string>> networkItems = {
            {"1", "🔍 Scan du réseau local"},
            {"2", "🎯 Scan de ports"},
            {"3", "🗺️  Traceroute"},
            {"4", "🌐 Résolution DNS"},
            {"5", "📡 Interfaces réseau"},
            {"6", "📊 Surveillance du trafic"},
            {"7", "📶 Analyse WiFi"},
            {"0", "🔙 Retour"}
        };
        
        for (const auto& [num, desc] : networkItems) {
            consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
            cout << "  [" << num << "] ";
            consoleColor.setColor(ConsoleColor::WHITE);
            cout << desc << endl;
        }
        
        cout << "\nChoisissez une option: ";
    }
    
    void DedSecTool::showSecurityMenu() {
        consoleColor.setColor(ConsoleColor::BRIGHT_RED);
        cout << "\n╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                  OUTILS DE SÉCURITÉ                         ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        vector<pair<string, string>> securityItems = {
            {"1", "🔐 Générateur de mots de passe"},
            {"2", "🔒 Chiffrement de texte"},
            {"3", "🔓 Déchiffrement de texte"},
            {"4", "#️⃣  Hash de fichier"},
            {"5", "🛡️  Scan de vulnérabilités"},
            {"6", "🔥 Statut du pare-feu"},
            {"7", "🦠 Statut de l'antivirus"},
            {"0", "🔙 Retour"}
        };
        
        for (const auto& [num, desc] : securityItems) {
            consoleColor.setColor(ConsoleColor::BRIGHT_YELLOW);
            cout << "  [" << num << "] ";
            consoleColor.setColor(ConsoleColor::WHITE);
            cout << desc << endl;
        }
        
        cout << "\nChoisissez une option: ";
    }
    
    void DedSecTool::showDevMenu() {
        consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
        cout << "\n╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║               OUTILS DE DÉVELOPPEMENT                       ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        vector<pair<string, string>> devItems = {
            {"1", "📦 Statut Git"},
            {"2", "🐳 Statut Docker"},
            {"3", "🟢 Statut Node.js"},
            {"4", "🐍 Statut Python"},
            {"5", "🏗️  Créer un projet"},
            {"6", "🧪 Exécuter les tests"},
            {"7", "🔨 Compiler le projet"},
            {"0", "🔙 Retour"}
        };
        
        for (const auto& [num, desc] : devItems) {
            consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
            cout << "  [" << num << "] ";
            consoleColor.setColor(ConsoleColor::WHITE);
            cout << desc << endl;
        }
        
        cout << "\nChoisissez une option: ";
    }
    
    void DedSecTool::showHiddenMenu() {
        Animation::glitchEffect("[ACCÈS AUX OUTILS CACHÉS]", 3);
        
        consoleColor.setColor(ConsoleColor::BRIGHT_MAGENTA);
        cout << "\n╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                    OUTILS CACHÉS                            ║" << endl;
        cout << "║                 [ULTRA SECRET]                              ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        cout << "Commandes spéciales disponibles:" << endl;
        for (const auto& [cmd, desc] : hiddenCommands) {
            consoleColor.setColor(ConsoleColor::BRIGHT_MAGENTA);
            cout << "  " << setw(15) << left << cmd;
            consoleColor.setColor(ConsoleColor::WHITE);
            cout << " - " << desc << endl;
        }
    }
    
    void DedSecTool::executeHiddenCommand(const string& command) {
        if (command == "ghost") {
            Animation::glitchEffect("[MODE FANTÔME ACTIVÉ]", 5);
            consoleColor.setColor(ConsoleColor::BRIGHT_BLACK);
            cout << "Vous êtes maintenant invisible..." << endl;
            
        } else if (command == "matrix") {
            Animation::matrixRain(10);
            
        } else if (command == "hack") {
            string target;
            cout << "Cible à hacker: ";
            getline(cin, target);
            if (target.empty()) target = "127.0.0.1";
            Animation::hackingAnimation(target);
            
        } else if (command == "breach") {
            Animation::typeWriter("[BRÈCHE DÉTECTÉE] Intrusion en cours...", 50);
            Animation::progressBar("Exploitation de la faille", 100);
            consoleColor.setColor(ConsoleColor::BRIGHT_RED);
            cout << "[SYSTÈME COMPROMIS] Accès root obtenu!" << endl;
            
        } else if (command == "ctOS") {
            Animation::typeWriter("Connexion au système ctOS de Chicago...", 30);
            Animation::showLoading("Contournement des sécurités", 3);
            consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
            cout << "[ctOS] Accès au réseau de surveillance urbaine accordé!" << endl;
            
        } else if (command == "wrench") {
            consoleColor.setColor(ConsoleColor::BRIGHT_YELLOW);
            cout << "🔧 [WRENCH] Outil de débogage avancé activé!" << endl;
            cout << "Toutes les fonctions de diagnostic sont maintenant disponibles." << endl;
            
        } else if (command == "aiden") {
            consoleColor.setColor(ConsoleColor::BRIGHT_BLUE);
            cout << "👤 [AIDEN PEARCE] Mode vigilante activé." << endl;
            cout << "\"Sometimes you gotta do bad things to catch the bad guys.\"" << endl;
            
        } else if (command == "marcus") {
            consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
            cout << "🎭 [MARCUS HOLLOWAY] Mode hackeur social activé." << endl;
            cout << "\"We're not terrorists. We're hacktivists.\"" << endl;
        }
        
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
    bool DedSecTool::processCommand(const string& command) {
        commandHistory.push_back(command);
        
        if (command == "exit" || command == "quit") {
            return false;
        } else if (command == "help") {
            showHelp();
        } else if (command == "menu") {
            showMainMenu();
        } else if (command == "clear" || command == "cls") {
            clearScreen();
            showLogo();
        } else if (command == "system") {
            SystemUtils::showSystemInfo();
        } else if (command == "list") {
            SystemUtils::listInstalledSoftware();
        } else if (command == "clean") {
            SystemUtils::cleanSystem();
        } else if (command == "update") {
            SystemUtils::checkUpdates();
        } else if (command == "network") {
            showNetworkMenu();
        } else if (command == "security") {
            showSecurityMenu();
        } else if (command == "dev") {
            showDevMenu();
        } else if (command == "auth") {
            authenticate();
        } else if (command == "history") {
            consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
            cout << "Historique des commandes:" << endl;
            for (size_t i = 0; i < commandHistory.size(); i++) {
                cout << "  " << (i + 1) << ". " << commandHistory[i] << endl;
            }
            consoleColor.setColor(ConsoleColor::WHITE);
        } else if (command == "monitor") {
            SystemUtils::monitorSystem(30);
        } else if (command == "scan") {
            SecurityTools::vulnerabilityScan();
        } else if (command.substr(0, 7) == "install") {
            if (command.length() > 8) {
                string software = command.substr(8);
                SystemUtils::installSoftware(software);
            } else {
                cout << "Usage: install <nom_du_logiciel>" << endl;
            }
        } else if (hiddenCommands.find(command) != hiddenCommands.end()) {
            executeHiddenCommand(command);
        } else if (command == "hidden") {
            showHiddenMenu();
        } else {
            consoleColor.setColor(ConsoleColor::BRIGHT_RED);
            cout << "[DEDSEC] Commande inconnue: " << command << endl;
            cout << "Tapez 'help' pour voir les commandes disponibles." << endl;
            consoleColor.setColor(ConsoleColor::WHITE);
        }
        
        return true;
    }
    
    void DedSecTool::run() {
        showLogo();
        showWelcomeMessage();
        
        string command;
        while (true) {
            consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
            cout << "\n[DEDSEC@" << currentUser << "]$ ";
            consoleColor.setColor(ConsoleColor::WHITE);
            
            getline(cin, command);
            
            // Convertir en minuscules pour la comparaison
            transform(command.begin(), command.end(), command.begin(), ::tolower);
            
            if (!processCommand(command)) {
                break;
            }
        }
        
        consoleColor.setColor(ConsoleColor::BRIGHT_YELLOW);
        cout << "\n[DEDSEC] Déconnexion du réseau..." << endl;
        Animation::typeWriter("Au revoir, hacker. Restez vigilant.", 50);
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
    void DedSecTool::runCommand(const string& command) {
        processCommand(command);
    }
    
}