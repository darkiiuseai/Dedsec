#ifndef DEDSEC_HPP
#define DEDSEC_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <random>

#ifdef _WIN32
#include <windows.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include <psapi.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "psapi.lib")
#else
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#endif

using namespace std;

namespace DedSec {
    
    // Classe pour gérer les couleurs de la console
    class ConsoleColor {
    public:
        enum Color {
            BLACK = 0,
            BLUE = 1,
            GREEN = 2,
            CYAN = 3,
            RED = 4,
            MAGENTA = 5,
            YELLOW = 6,
            WHITE = 7,
            BRIGHT_BLACK = 8,
            BRIGHT_BLUE = 9,
            BRIGHT_GREEN = 10,
            BRIGHT_CYAN = 11,
            BRIGHT_RED = 12,
            BRIGHT_MAGENTA = 13,
            BRIGHT_YELLOW = 14,
            BRIGHT_WHITE = 15
        };
        
        void setColor(Color color);
        void resetColor();
        void setBackgroundColor(Color color);
    };
    
    // Classe pour les animations et effets visuels
    class Animation {
    public:
        static void showLoading(const string& message, int duration = 3);
        static void typeWriter(const string& text, int delay = 50);
        static void glitchEffect(const string& text, int iterations = 5);
        static void matrixRain(int duration = 5);
        static void progressBar(const string& task, int steps = 100);
        static void hackingAnimation(const string& target);
    };
    
    // Classe pour les utilitaires système
    class SystemUtils {
    public:
        static bool isSoftwareInstalled(const string& name);
        static bool installSoftware(const string& name, const string& packageName = "");
        static void showSystemInfo();
        static void listInstalledSoftware();
        static void cleanSystem();
        static void checkUpdates();
        static void testConnection();
        static vector<string> getRunningProcesses();
        static void killProcess(const string& processName);
        static void monitorSystem(int duration = 30);
    };
    
    // Classe pour les outils réseau
    class NetworkTools {
    public:
        static void scanNetwork();
        static void portScan(const string& target);
        static void traceRoute(const string& target);
        static void dnsLookup(const string& domain);
        static void showNetworkInterfaces();
        static void monitorTraffic(int duration = 30);
        static void wifiAnalysis();
    };
    
    // Classe pour les outils de sécurité
    class SecurityTools {
    public:
        static void passwordGenerator(int length = 16);
        static void hashFile(const string& filePath);
        static void encryptText(const string& text);
        static void decryptText(const string& encryptedText);
        static void vulnerabilityScan();
        static void firewallStatus();
        static void antivirusStatus();
    };
    
    // Classe pour les outils de développement
    class DevTools {
    public:
        static void gitStatus();
        static void dockerStatus();
        static void nodeStatus();
        static void pythonStatus();
        static void createProject(const string& type, const string& name);
        static void runTests();
        static void buildProject();
    };
    
    // Classe principale DedSecTool
    class DedSecTool {
    private:
        ConsoleColor consoleColor;
        bool isAuthenticated;
        string currentUser;
        vector<string> commandHistory;
        map<string, string> hiddenCommands;
        
        void initializeHiddenCommands();
        void showLogo();
        void showWelcomeMessage();
        void authenticate();
        bool processCommand(const string& command);
        void showHelp();
        void showMainMenu();
        void showAdvancedMenu();
        void showNetworkMenu();
        void showSecurityMenu();
        void showDevMenu();
        void showHiddenMenu();
        void executeHiddenCommand(const string& command);
        
    public:
        DedSecTool();
        ~DedSecTool();
        void run();
        void runCommand(const string& command);
    };
    
    // Variables globales
    extern ConsoleColor consoleColor;
    
    // Fonctions utilitaires
    void clearScreen();
    void pauseSystem();
    string getCurrentTime();
    string generateRandomString(int length);
    void playSound(const string& soundType);
    
}

#endif // DEDSEC_HPP