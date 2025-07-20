#include <sstream>
#include "tmt88v.h"
#include "linux_console.h"

int main() {
    int screw = 0;
    std::stringstream frame;   // like cout, but writes to a string

    clear();

    std::string input = "";

    std::string selectionPrompt1 = 
            "Please select a mode:\n\n"
            " 1 - line by line, smallest text\n\n";

    frame << selectionPrompt1;

    std::cout << frame.str();

    //-------------------------------------------
    //Options while loop
    while(true){
            input = getButton();

            clear();
            frame.str("");

        if ( input == "1" ){
            frame << 
                "[line by line print system activated]\n\n"
                "Instructions:\n"
                "Type enter at the end of each line to print it onto the tmt88v\n"
                "With an empty line, press END on the keyboard, then press enter to stop.\n"
                "press any button to start...\n";
            std::cout << frame.str();
            getButton();
            clear();//^These button and clear are for transition.
            break;
        }
        else{
            frame << selectionPrompt1;
            screw++;
            frame << "*That was not an option, try that again... ( you did this " << screw << " times)*\n";
            std::cout << frame.str();
        }
    }
    //------------------------------------------

    //while loop for line by line mode (the only mode at the moment)
    std::string endCheck = "";
    Tmt88v tmt88v;
    tmt88v.setCutMode(0);
    tmt88v.setCutPadding(false);
    tmt88v.setText("");
    while(true){
        std::cout << 
        "****|****|****|****|****|****|****|****|****|****|****|*\n"
        "========================================================\n\n";
        std::getline(std::cin, input);
        endCheck = input;
        input = input + "\n";
        tmt88v.setText(input);

        if (!endCheck.empty() && (endCheck == "\x1b[F" || endCheck == "\x1b[4~")) {
            break; // exit loop on END key
        }

        if (input.empty()){
            continue; //Don't what to print nothing.
        }
        tmt88v.print();
        clear();
    }
    tmt88v.setText("\n");
    tmt88v.setCutMode(2);
    tmt88v.setCutPadding(true);
    tmt88v.print();
    clear();

    std::cout << "PROGRAM_ENDED\n";
    
    return 0;
}


