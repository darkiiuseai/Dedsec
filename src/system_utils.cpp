#include "include/dedsec.hpp"

namespace DedSec {
    
    bool SystemUtils::isSoftwareInstalled(const string& name) {
#ifdef _WIN32
        string command = "where " + name + " >nul 2>&1";
        return system(command.c_str()) == 0;
#else
        string command = "which " + name + " > /dev/null 2>&1";
        return system(command.c_str()) == 0;
#endif
    }
    
    bool SystemUtils::installSoftware(const string& name, const string& packageName) {
        string package = packageName.empty() ? name : packageName;
        
        consoleColor.setColor(ConsoleColor::YELLOW);
        cout << "[DEDSEC] Installation de " << name << "..." << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::progressBar("Installation en cours", 100);
        
#ifdef _WIN32
        string command = "winget install --id " + package + " -e --accept-package-agreements --accept-source-agreements";
#else
        string command = "sudo apt-get install -y " + package;
#endif
        
        int result = system(command.c_str());
        
        if (result == 0) {
            consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
            cout << "[DEDSEC] " << name << " installé avec succès!" << endl;
            consoleColor.setColor(ConsoleColor::WHITE);
            return true;
        } else {
            consoleColor.setColor(ConsoleColor::BRIGHT_RED);
            cout << "[DEDSEC] Échec de l'installation de " << name << endl;
            consoleColor.setColor(ConsoleColor::WHITE);
            return false;
        }
    }
    
    void SystemUtils::showSystemInfo() {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║        INFORMATIONS SYSTÈME          ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
#ifdef _WIN32
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);
        
        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memInfo);
        
        DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
        char hostname[MAX_COMPUTERNAME_LENGTH + 1];
        GetComputerNameA(hostname, &size);
        
        consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
        cout << "🖥️  Nom d'hôte: " << hostname << endl;
        cout << "🏗️  Architecture: " << (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ? "64-bit" : "32-bit") << endl;
        cout << "⚡ Processeurs: " << sysInfo.dwNumberOfProcessors << endl;
        cout << "💾 Mémoire totale: " << (memInfo.ullTotalPhys / (1024 * 1024)) << " MB" << endl;
        cout << "💿 Mémoire disponible: " << (memInfo.ullAvailPhys / (1024 * 1024)) << " MB" << endl;
        
        // Informations sur le disque
        ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes;
        if (GetDiskFreeSpaceExA("C:\\", &freeBytesAvailable, &totalNumberOfBytes, NULL)) {
            cout << "💽 Espace disque C: " << (freeBytesAvailable.QuadPart / (1024 * 1024 * 1024)) << " GB libres / " 
                 << (totalNumberOfBytes.QuadPart / (1024 * 1024 * 1024)) << " GB total" << endl;
        }
#else
        struct utsname unameData;
        uname(&unameData);
        
        cout << "🖥️  Système: " << unameData.sysname << " " << unameData.release << endl;
        cout << "🏗️  Architecture: " << unameData.machine << endl;
        cout << "🖥️  Nom d'hôte: " << unameData.nodename << endl;
#endif
        
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
    void SystemUtils::listInstalledSoftware() {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║         LOGICIELS INSTALLÉS          ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        vector<pair<string, string>> softwareList = {
            {"Git", "git"},
            {"Visual Studio Code", "code"},
            {"Node.js", "node"},
            {"Python", "python"},
            {"Docker", "docker"},
            {"Postman", "postman"},
            {"Chrome", "chrome"},
            {"Firefox", "firefox"},
            {"7-Zip", "7z"},
            {"CMake", "cmake"},
            {"GCC", "gcc"},
            {"Java", "java"},
            {"Maven", "mvn"},
            {"Gradle", "gradle"}
        };
        
        for (const auto& [name, command] : softwareList) {
            bool installed = isSoftwareInstalled(command);
            if (installed) {
                consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
                cout << "[✓] ";
            } else {
                consoleColor.setColor(ConsoleColor::BRIGHT_RED);
                cout << "[✗] ";
            }
            consoleColor.setColor(ConsoleColor::WHITE);
            cout << name << endl;
        }
    }
    
    void SystemUtils::cleanSystem() {
        consoleColor.setColor(ConsoleColor::BRIGHT_YELLOW);
        cout << "[DEDSEC] Nettoyage du système en cours..." << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::progressBar("Nettoyage des fichiers temporaires", 100);
        
#ifdef _WIN32
        system("del /q /f /s %TEMP%\\*.* >nul 2>&1");
        system("cleanmgr /sagerun:1 >nul 2>&1");
#else
        system("sudo apt-get autoremove -y");
        system("sudo apt-get autoclean");
#endif
        
        consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
        cout << "[DEDSEC] Nettoyage terminé!" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
    void SystemUtils::checkUpdates() {
        consoleColor.setColor(ConsoleColor::BRIGHT_YELLOW);
        cout << "[DEDSEC] Vérification des mises à jour..." << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::showLoading("Recherche de mises à jour", 3);
        
#ifdef _WIN32
        system("winget upgrade");
#else
        system("sudo apt update && sudo apt list --upgradable");
#endif
    }
    
    void SystemUtils::testConnection() {
        consoleColor.setColor(ConsoleColor::BRIGHT_YELLOW);
        cout << "[DEDSEC] Test de connexion Internet..." << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::showLoading("Test en cours", 2);
        
        vector<string> testHosts = {"8.8.8.8", "1.1.1.1", "google.com"};
        
        for (const auto& host : testHosts) {
            cout << "Test de " << host << ": ";
#ifdef _WIN32
            string command = "ping " + host + " -n 1 >nul 2>&1";
#else
            string command = "ping -c 1 " + host + " > /dev/null 2>&1";
#endif
            if (system(command.c_str()) == 0) {
                consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
                cout << "[OK]" << endl;
            } else {
                consoleColor.setColor(ConsoleColor::BRIGHT_RED);
                cout << "[ÉCHEC]" << endl;
            }
            consoleColor.setColor(ConsoleColor::WHITE);
        }
    }
    
    vector<string> SystemUtils::getRunningProcesses() {
        vector<string> processes;
        
#ifdef _WIN32
        HANDLE hProcessSnap;
        PROCESSENTRY32 pe32;
        
        hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hProcessSnap == INVALID_HANDLE_VALUE) {
            return processes;
        }
        
        pe32.dwSize = sizeof(PROCESSENTRY32);
        
        if (Process32First(hProcessSnap, &pe32)) {
            do {
                processes.push_back(pe32.szExeFile);
            } while (Process32Next(hProcessSnap, &pe32));
        }
        
        CloseHandle(hProcessSnap);
#else
        // Implémentation Linux
        system("ps aux > /tmp/processes.txt");
        ifstream file("/tmp/processes.txt");
        string line;
        while (getline(file, line)) {
            processes.push_back(line);
        }
#endif
        
        return processes;
    }
    
    void SystemUtils::killProcess(const string& processName) {
        consoleColor.setColor(ConsoleColor::BRIGHT_RED);
        cout << "[DEDSEC] Arrêt du processus: " << processName << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
#ifdef _WIN32
        string command = "taskkill /f /im " + processName;
#else
        string command = "pkill " + processName;
#endif
        
        if (system(command.c_str()) == 0) {
            consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
            cout << "[DEDSEC] Processus arrêté avec succès!" << endl;
        } else {
            consoleColor.setColor(ConsoleColor::BRIGHT_RED);
            cout << "[DEDSEC] Échec de l'arrêt du processus!" << endl;
        }
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
    void SystemUtils::monitorSystem(int duration) {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "[DEDSEC] Surveillance système activée pour " << duration << " secondes..." << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        auto start = chrono::steady_clock::now();
        while (chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start).count() < duration) {
            // Affichage des statistiques en temps réel
#ifdef _WIN32
            MEMORYSTATUSEX memInfo;
            memInfo.dwLength = sizeof(MEMORYSTATUSEX);
            GlobalMemoryStatusEx(&memInfo);
            
            int memUsage = (int)((memInfo.ullTotalPhys - memInfo.ullAvailPhys) * 100 / memInfo.ullTotalPhys);
            
            cout << "\rMémoire: " << memUsage << "% | Processus actifs: " << getRunningProcesses().size() << " | Temps: " 
                 << chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start).count() << "s" << flush;
#endif
            this_thread::sleep_for(chrono::seconds(1));
        }
        
        cout << endl;
        consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
        cout << "[DEDSEC] Surveillance terminée!" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
    }
    
}