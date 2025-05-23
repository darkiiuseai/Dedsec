#include "include/dedsec.hpp"

namespace DedSec {
    
    void DevTools::gitStatus() {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║            STATUT GIT                ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        if (!SystemUtils::isSoftwareInstalled("git")) {
            consoleColor.setColor(ConsoleColor::BRIGHT_RED);
            cout << "[DEDSEC] Git n'est pas installé!" << endl;
            consoleColor.setColor(ConsoleColor::WHITE);
            return;
        }
        
        Animation::showLoading("Analyse du dépôt Git", 2);
        
        system("git status");
        cout << endl;
        system("git log --oneline -10");
        cout << endl;
        system("git branch -a");
    }
    
    void DevTools::dockerStatus() {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║           STATUT DOCKER              ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        if (!SystemUtils::isSoftwareInstalled("docker")) {
            consoleColor.setColor(ConsoleColor::BRIGHT_RED);
            cout << "[DEDSEC] Docker n'est pas installé!" << endl;
            consoleColor.setColor(ConsoleColor::WHITE);
            return;
        }
        
        Animation::showLoading("Vérification de Docker", 2);
        
        system("docker --version");
        system("docker ps");
        system("docker images");
    }
    
    void DevTools::nodeStatus() {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║           STATUT NODE.JS             ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        if (!SystemUtils::isSoftwareInstalled("node")) {
            consoleColor.setColor(ConsoleColor::BRIGHT_RED);
            cout << "[DEDSEC] Node.js n'est pas installé!" << endl;
            consoleColor.setColor(ConsoleColor::WHITE);
            return;
        }
        
        Animation::showLoading("Vérification de Node.js", 2);
        
        system("node --version");
        system("npm --version");
        system("npm list -g --depth=0");
    }
    
    void DevTools::pythonStatus() {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║           STATUT PYTHON              ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        if (!SystemUtils::isSoftwareInstalled("python")) {
            consoleColor.setColor(ConsoleColor::BRIGHT_RED);
            cout << "[DEDSEC] Python n'est pas installé!" << endl;
            consoleColor.setColor(ConsoleColor::WHITE);
            return;
        }
        
        Animation::showLoading("Vérification de Python", 2);
        
        system("python --version");
        system("pip --version");
        system("pip list");
    }
    
    void DevTools::createProject(const string& type, const string& name) {
        consoleColor.setColor(ConsoleColor::BRIGHT_YELLOW);
        cout << "[DEDSEC] Création du projet " << type << ": " << name << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::progressBar("Création en cours", 100);
        
        if (type == "cpp" || type == "c++") {
            system(("mkdir " + name).c_str());
            ofstream mainFile(name + "/main.cpp");
            mainFile << "#include <iostream>\n\nint main() {\n    std::cout << \"Hello, World!\" << std::endl;\n    return 0;\n}";
            mainFile.close();
            
            ofstream cmakeFile(name + "/CMakeLists.txt");
            cmakeFile << "cmake_minimum_required(VERSION 3.10)\n";
            cmakeFile << "project(" << name << ")\n";
            cmakeFile << "set(CMAKE_CXX_STANDARD 17)\n";
            cmakeFile << "add_executable(" << name << " main.cpp)";
            cmakeFile.close();
            
        } else if (type == "python" || type == "py") {
            system(("mkdir " + name).c_str());
            ofstream mainFile(name + "/main.py");
            mainFile << "#!/usr/bin/env python3\n\ndef main():\n    print(\"Hello, World!\")\n\nif __name__ == \"__main__\":\n    main()";
            mainFile.close();
            
            ofstream reqFile(name + "/requirements.txt");
            reqFile << "# Add your dependencies here";
            reqFile.close();
            
        } else if (type == "node" || type == "js") {
            system(("mkdir " + name).c_str());
            system(("cd " + name + " && npm init -y").c_str());
            
            ofstream indexFile(name + "/index.js");
            indexFile << "console.log('Hello, World!')";
            indexFile.close();
        }
        
        consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
        cout << "[DEDSEC] Projet " << name << " créé avec succès!" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
    void DevTools::runTests() {
        consoleColor.setColor(ConsoleColor::BRIGHT_YELLOW);
        cout << "[DEDSEC] Exécution des tests..." << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::progressBar("Tests en cours", 100);
        
        // Détection automatique du type de projet
        if (ifstream("package.json")) {
            system("npm test");
        } else if (ifstream("CMakeLists.txt")) {
            system("ctest");
        } else if (ifstream("requirements.txt")) {
            system("python -m pytest");
        } else {
            consoleColor.setColor(ConsoleColor::BRIGHT_RED);
            cout << "[DEDSEC] Aucun système de test détecté!" << endl;
            consoleColor.setColor(ConsoleColor::WHITE);
        }
    }
    
    void DevTools::buildProject() {
        consoleColor.setColor(ConsoleColor::BRIGHT_YELLOW);
        cout << "[DEDSEC] Compilation du projet..." << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::progressBar("Compilation en cours", 100);
        
        // Détection automatique du type de projet
        if (ifstream("CMakeLists.txt")) {
            system("mkdir -p build && cd build && cmake .. && make");
        } else if (ifstream("package.json")) {
            system("npm run build");
        } else if (ifstream("Makefile")) {
            system("make");
        } else {
            consoleColor.setColor(ConsoleColor::BRIGHT_RED);
            cout << "[DEDSEC] Aucun système de build détecté!" << endl;
            consoleColor.setColor(ConsoleColor::WHITE);
            return;
        }
        
        consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
        cout << "[DEDSEC] Compilation terminée avec succès!" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
}