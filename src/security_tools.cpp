#include "include/dedsec.hpp"

namespace DedSec {
    
    void SecurityTools::passwordGenerator(int length) {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║       GÉNÉRATEUR DE MOTS DE PASSE    ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=[]{}|;:,.<>?";
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, chars.length() - 1);
        
        string password;
        for (int i = 0; i < length; i++) {
            password += chars[dis(gen)];
        }
        
        Animation::showLoading("Génération du mot de passe", 2);
        
        consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
        cout << "[DEDSEC] Mot de passe généré: " << password << endl;
        
        // Analyse de la force du mot de passe
        int strength = 0;
        bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
        
        for (char c : password) {
            if (c >= 'A' && c <= 'Z') hasUpper = true;
            else if (c >= 'a' && c <= 'z') hasLower = true;
            else if (c >= '0' && c <= '9') hasDigit = true;
            else hasSpecial = true;
        }
        
        strength = hasUpper + hasLower + hasDigit + hasSpecial;
        
        cout << "[DEDSEC] Force du mot de passe: ";
        if (strength >= 4 && length >= 12) {
            consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
            cout << "TRÈS FORTE" << endl;
        } else if (strength >= 3 && length >= 8) {
            consoleColor.setColor(ConsoleColor::YELLOW);
            cout << "FORTE" << endl;
        } else {
            consoleColor.setColor(ConsoleColor::BRIGHT_RED);
            cout << "FAIBLE" << endl;
        }
        
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
    void SecurityTools::hashFile(const string& filePath) {
        consoleColor.setColor(ConsoleColor::BRIGHT_YELLOW);
        cout << "[DEDSEC] Calcul du hash pour: " << filePath << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::showLoading("Calcul en cours", 2);
        
        ifstream file(filePath, ios::binary);
        if (!file.is_open()) {
            consoleColor.setColor(ConsoleColor::BRIGHT_RED);
            cout << "[DEDSEC] Erreur: Impossible d'ouvrir le fichier!" << endl;
            consoleColor.setColor(ConsoleColor::WHITE);
            return;
        }
        
        // Hash simple (pour démonstration)
        size_t hash = 0;
        char buffer[1024];
        while (file.read(buffer, sizeof(buffer))) {
            for (int i = 0; i < file.gcount(); i++) {
                hash = hash * 31 + buffer[i];
            }
        }
        
        consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
        cout << "[DEDSEC] Hash calculé: " << hex << hash << dec << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
    void SecurityTools::encryptText(const string& text) {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "[DEDSEC] Chiffrement du texte..." << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::showLoading("Chiffrement en cours", 2);
        
        // Chiffrement César simple (pour démonstration)
        string encrypted = "";
        int shift = 13; // ROT13
        
        for (char c : text) {
            if (c >= 'A' && c <= 'Z') {
                encrypted += char((c - 'A' + shift) % 26 + 'A');
            } else if (c >= 'a' && c <= 'z') {
                encrypted += char((c - 'a' + shift) % 26 + 'a');
            } else {
                encrypted += c;
            }
        }
        
        consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
        cout << "[DEDSEC] Texte chiffré: " << encrypted << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
    void SecurityTools::decryptText(const string& encryptedText) {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "[DEDSEC] Déchiffrement du texte..." << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::showLoading("Déchiffrement en cours", 2);
        
        // Déchiffrement César (ROT13)
        string decrypted = "";
        int shift = 13;
        
        for (char c : encryptedText) {
            if (c >= 'A' && c <= 'Z') {
                decrypted += char((c - 'A' - shift + 26) % 26 + 'A');
            } else if (c >= 'a' && c <= 'z') {
                decrypted += char((c - 'a' - shift + 26) % 26 + 'a');
            } else {
                decrypted += c;
            }
        }
        
        consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
        cout << "[DEDSEC] Texte déchiffré: " << decrypted << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
    void SecurityTools::vulnerabilityScan() {
        consoleColor.setColor(ConsoleColor::BRIGHT_RED);
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║       SCAN DE VULNÉRABILITÉS         ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::hackingAnimation("Système local");
        
        vector<string> vulnerabilityChecks = {
            "Vérification des ports ouverts",
            "Analyse des services en cours",
            "Contrôle des permissions de fichiers",
            "Vérification des mots de passe faibles",
            "Scan des logiciels obsolètes",
            "Analyse des configurations de sécurité"
        };
        
        for (const auto& check : vulnerabilityChecks) {
            cout << "[SCAN] " << check << "... ";
            this_thread::sleep_for(chrono::milliseconds(1000));
            
            // Simulation de résultats aléatoires
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, 2);
            
            switch (dis(gen)) {
                case 0:
                    consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
                    cout << "[SÉCURISÉ]" << endl;
                    break;
                case 1:
                    consoleColor.setColor(ConsoleColor::YELLOW);
                    cout << "[ATTENTION]" << endl;
                    break;
                case 2:
                    consoleColor.setColor(ConsoleColor::BRIGHT_RED);
                    cout << "[VULNÉRABLE]" << endl;
                    break;
            }
            consoleColor.setColor(ConsoleColor::WHITE);
        }
        
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "[DEDSEC] Scan de vulnérabilités terminé!" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
    void SecurityTools::firewallStatus() {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "[DEDSEC] Vérification du statut du pare-feu..." << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::showLoading("Analyse en cours", 2);
        
#ifdef _WIN32
        system("netsh advfirewall show allprofiles");
#else
        system("sudo ufw status verbose");
#endif
    }
    
    void SecurityTools::antivirusStatus() {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "[DEDSEC] Vérification du statut de l'antivirus..." << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::showLoading("Analyse en cours", 2);
        
#ifdef _WIN32
        system("wmic /namespace:\\\\root\\SecurityCenter2 path AntiVirusProduct get displayName,productState /format:list");
#else
        system("ps aux | grep -i antivirus");
        system("systemctl status clamav-daemon");
#endif
    }
    
}