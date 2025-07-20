#include "linux_console.h"

void clear(){
    std::cout << "\033c\033[2J\033[H" << std::flush;
}

std::string getButton() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::string result;
    int ch = getchar();

    if (ch == 27) { // ESC
        int next1 = getchar();
        if (next1 == '[') {
            int next2 = getchar();

            if (next2 >= '0' && next2 <= '6') {
                int next3 = getchar(); // Should be ~
                switch (next2) {
                    case '1': result = "Home"; break;      // May not trigger
                    case '2': result = "Insert"; break;
                    case '3': result = "Delete"; break;
                    case '4': result = "End"; break;        // May not trigger
                    case '5': result = "PageUp"; break;
                    case '6': result = "PageDown"; break;
                    default:  result = "UnknownEscapeSeq"; break;
                }
            } else {
                // Common alternative Home/End codes
                switch (next2) {
                    case 'A': result = "ArrowUp"; break;
                    case 'B': result = "ArrowDown"; break;
                    case 'C': result = "ArrowRight"; break;
                    case 'D': result = "ArrowLeft"; break;
                    case 'H': result = "Home"; break;  // <- this works in most terminals
                    case 'F': result = "End"; break;   // <- this too
                    default:  result = "UnknownEscapeSeq"; break;
                }
            }
        } else {
            result = "Escape";  // ESC alone
        }
    } else if (ch == 10 || ch == 13) {
        result = "Enter";
    } else if (ch == 127 || ch == 8) {
        result = "Backspace";
    } else if (ch == 9) {
        result = "Tab";
    } else if (ch == 32) {
        result = "Space";
    } else {
        result = std::string(1, static_cast<char>(ch));
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return result;
}

