#include "include/dedsec.hpp"

namespace DedSec {
    
    void Animation::showLoading(const string& message, int duration) {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "[DEDSEC] " << message;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        const string loadingChars = "|/-\\";
        for (int i = 0; i < duration * 10; i++) {
            cout << "\r[DEDSEC] " << message << " " << loadingChars[i % 4] << flush;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        
        consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
        cout << "\r[DEDSEC] " << message << " [TERMINÉ]" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
    void Animation::typeWriter(const string& text, int delay) {
        for (char c : text) {
            cout << c << flush;
            this_thread::sleep_for(chrono::milliseconds(delay));
        }
        cout << endl;
    }
    
    void Animation::glitchEffect(const string& text, int iterations) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 255);
        
        for (int i = 0; i < iterations; i++) {
            cout << "\r";
            for (size_t j = 0; j < text.length(); j++) {
                if (gen() % 10 == 0) {
                    cout << (char)(33 + (gen() % 94)); // Caractères ASCII imprimables
                } else {
                    cout << text[j];
                }
            }
            cout << flush;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        
        cout << "\r" << text << endl;
    }
    
    void Animation::matrixRain(int duration) {
        consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(33, 126);
        
        auto start = chrono::steady_clock::now();
        while (chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start).count() < duration) {
            for (int i = 0; i < 80; i++) {
                if (gen() % 10 == 0) {
                    cout << (char)dis(gen);
                } else {
                    cout << " ";
                }
            }
            cout << endl;
            this_thread::sleep_for(chrono::milliseconds(50));
        }
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
    void Animation::progressBar(const string& task, int steps) {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "[DEDSEC] " << task << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        for (int i = 0; i <= steps; i++) {
            int progress = (i * 50) / steps;
            cout << "\r[";
            
            consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
            for (int j = 0; j < progress; j++) {
                cout << "█";
            }
            
            consoleColor.setColor(ConsoleColor::BRIGHT_BLACK);
            for (int j = progress; j < 50; j++) {
                cout << "░";
            }
            
            consoleColor.setColor(ConsoleColor::WHITE);
            cout << "] " << (i * 100) / steps << "%" << flush;
            
            this_thread::sleep_for(chrono::milliseconds(50));
        }
        
        consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
        cout << " [TERMINÉ]" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
    void Animation::hackingAnimation(const string& target) {
        consoleColor.setColor(ConsoleColor::BRIGHT_RED);
        cout << "[DEDSEC] Initialisation du hack sur: " << target << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        vector<string> hackSteps = {
            "Scan des ports ouverts...",
            "Recherche de vulnérabilités...",
            "Injection de payload...",
            "Contournement des défenses...",
            "Établissement de la connexion...",
            "Accès obtenu!"
        };
        
        for (const auto& step : hackSteps) {
            consoleColor.setColor(ConsoleColor::YELLOW);
            cout << "[HACK] " << step << flush;
            
            // Animation de points
            for (int i = 0; i < 3; i++) {
                this_thread::sleep_for(chrono::milliseconds(500));
                cout << "." << flush;
            }
            
            consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
            cout << " [OK]" << endl;
        }
        
        consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
        cout << "[DEDSEC] Hack terminé avec succès!" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
}