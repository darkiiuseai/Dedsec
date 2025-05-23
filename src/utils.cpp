#include "include/dedsec.hpp"

namespace DedSec {
    
    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
    
    void pauseSystem() {
#ifdef _WIN32
        system("pause");
#else
        cout << "Appuyez sur Entrée pour continuer...";
        cin.get();
#endif
    }
    
    string getCurrentTime() {
        auto now = chrono::system_clock::now();
        auto time_t = chrono::system_clock::to_time_t(now);
        auto tm = *localtime(&time_t);
        
        stringstream ss;
        ss << put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
    
    string generateRandomString(int length) {
        const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, chars.length() - 1);
        
        string result;
        for (int i = 0; i < length; i++) {
            result += chars[dis(gen)];
        }
        return result;
    }
    
    void playSound(const string& soundType) {
#ifdef _WIN32
        if (soundType == "beep") {
            Beep(750, 300);
        } else if (soundType == "error") {
            Beep(300, 500);
        } else if (soundType == "success") {
            Beep(1000, 200);
        }
#else
        // Linux/Mac - utilise le terminal bell
        cout << "\a" << flush;
#endif
    }
    
}