#include "include/dedsec.hpp"

namespace DedSec {
    
    void NetworkTools::scanNetwork() {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║           SCAN RÉSEAU                ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::hackingAnimation("Réseau local");
        
#ifdef _WIN32
        system("arp -a");
        system("netstat -an | findstr LISTENING");
#else
        system("nmap -sn 192.168.1.0/24");
        system("netstat -tuln");
#endif
    }
    
    void NetworkTools::portScan(const string& target) {
        consoleColor.setColor(ConsoleColor::BRIGHT_RED);
        cout << "[DEDSEC] Scan de ports sur: " << target << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::hackingAnimation(target);
        
        vector<int> commonPorts = {21, 22, 23, 25, 53, 80, 110, 143, 443, 993, 995, 3389, 5432, 3306};
        
        for (int port : commonPorts) {
            cout << "Port " << port << ": ";
            
#ifdef _WIN32
            WSADATA wsaData;
            WSAStartup(MAKEWORD(2, 2), &wsaData);
            
            SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
            if (sock == INVALID_SOCKET) {
                consoleColor.setColor(ConsoleColor::BRIGHT_RED);
                cout << "[ERREUR]" << endl;
                continue;
            }
            
            struct sockaddr_in server;
            server.sin_family = AF_INET;
            server.sin_port = htons(port);
            server.sin_addr.s_addr = inet_addr(target.c_str());
            
            // Timeout de 1 seconde
            int timeout = 1000;
            setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
            
            if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == 0) {
                consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
                cout << "[OUVERT]" << endl;
            } else {
                consoleColor.setColor(ConsoleColor::BRIGHT_RED);
                cout << "[FERMÉ]" << endl;
            }
            
            closesocket(sock);
#else
            string command = "nc -z -v -w1 " + target + " " + to_string(port) + " 2>&1";
            if (system(command.c_str()) == 0) {
                consoleColor.setColor(ConsoleColor::BRIGHT_GREEN);
                cout << "[OUVERT]" << endl;
            } else {
                consoleColor.setColor(ConsoleColor::BRIGHT_RED);
                cout << "[FERMÉ]" << endl;
            }
#endif
            consoleColor.setColor(ConsoleColor::WHITE);
        }
        
#ifdef _WIN32
        WSACleanup();
#endif
    }
    
    void NetworkTools::traceRoute(const string& target) {
        consoleColor.setColor(ConsoleColor::BRIGHT_YELLOW);
        cout << "[DEDSEC] Traceroute vers: " << target << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::showLoading("Traçage de la route", 2);
        
#ifdef _WIN32
        string command = "tracert " + target;
#else
        string command = "traceroute " + target;
#endif
        system(command.c_str());
    }
    
    void NetworkTools::dnsLookup(const string& domain) {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "[DEDSEC] Résolution DNS pour: " << domain << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::showLoading("Résolution en cours", 1);
        
#ifdef _WIN32
        string command = "nslookup " + domain;
#else
        string command = "dig " + domain;
#endif
        system(command.c_str());
    }
    
    void NetworkTools::showNetworkInterfaces() {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║       INTERFACES RÉSEAU              ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
#ifdef _WIN32
        system("ipconfig /all");
#else
        system("ifconfig -a");
#endif
    }
    
    void NetworkTools::monitorTraffic(int duration) {
        consoleColor.setColor(ConsoleColor::BRIGHT_YELLOW);
        cout << "[DEDSEC] Surveillance du trafic réseau pour " << duration << " secondes..." << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::progressBar("Surveillance en cours", duration);
        
#ifdef _WIN32
        system("netstat -e");
#else
        system("iftop -t -s " + to_string(duration));
#endif
    }
    
    void NetworkTools::wifiAnalysis() {
        consoleColor.setColor(ConsoleColor::BRIGHT_CYAN);
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║         ANALYSE WIFI                 ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        
        Animation::showLoading("Scan des réseaux WiFi", 3);
        
#ifdef _WIN32
        system("netsh wlan show profiles");
        system("netsh wlan show interfaces");
#else
        system("iwlist scan | grep ESSID");
        system("iwconfig");
#endif
    }
    
}