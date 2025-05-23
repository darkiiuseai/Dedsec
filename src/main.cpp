#include "include/dedsec.hpp"

using namespace DedSec;

int main(int argc, char* argv[]) {
    try {
        // Configuration de la console pour Windows
#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
        
        // Activer les couleurs ANSI sur Windows 10+
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
#endif
        
        // Créer l'instance principale du tool DedSec
        DedSecTool tool;
        
        // Si des arguments sont passés en ligne de commande
        if (argc > 1) {
            string command = "";
            for (int i = 1; i < argc; i++) {
                if (i > 1) command += " ";
                command += argv[i];
            }
            
            // Convertir en minuscules
            transform(command.begin(), command.end(), command.begin(), ::tolower);
            
            // Exécuter la commande directement
            tool.runCommand(command);
        } else {
            // Mode interactif
            tool.run();
        }
        
    } catch (const exception& e) {
        consoleColor.setColor(ConsoleColor::BRIGHT_RED);
        cout << "[ERREUR CRITIQUE] " << e.what() << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        return 1;
    } catch (...) {
        consoleColor.setColor(ConsoleColor::BRIGHT_RED);
        cout << "[ERREUR CRITIQUE] Erreur inconnue!" << endl;
        consoleColor.setColor(ConsoleColor::WHITE);
        return 1;
    }
    
    return 0;
}