#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <thread>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

string strPadRight(string to_pad, int total_length, char pad_with = ' ') {//why isnt this a default feature smh
    if (to_pad.size() >= total_length) {
        return to_pad;
    }
    return to_pad + string(total_length - to_pad.size(), pad_with);
}

string bgRed (string word)
{
    return "\033[41m"  +  word  +  "\033[0m";
}
string bgPurple (string word)
{
    return "\033[45m" + word + "\033[0m";
}
string red(string word)
{
    return "\033[31m" + word + "\033[0m";
}
string green (string word)
{
    return "\033[32m" + word + "\033[0m";
}
string yellow (string word)
{
    return "\033[33m" + word + "\033[0m";
}
string blue (string word)
{
    return "\033[34m" + word + "\033[0m";
}
string purple (string word)
{
    return "\033[35m" + word + "\033[0m";
}
string cyan (string word)
{
    return "\033[36m" + word + "\033[0m";
}
string white (string word)
{
    return "\033[37m" + word + "\033[0m";
}

void cursorUp (int amount = 1) {
    cout << "\033[" << amount << "A";
}
void cursorDown (int amount = 1) {
    cout << "\033[" << amount << "B";
}

string screenStatic (int screen_size) {
    string static_line = "";
    vector<string> rand_chars = {"▘","▝","▀","▖","▍","▞","▛","▗","▚","▐","▜","▃","▙","▟","█"," "};
    int rand_nr = 0, rand_chars_length = 16;
    for (int nr = 0; nr < screen_size; nr++) {
        rand_nr = rand() % 16;
        int rand_nr_color = rand() % 7;
        string rand_colored_char, rand_uncolored_char = rand_chars[rand_nr];
        switch(rand_nr_color) {
            case 0: rand_colored_char = white(rand_uncolored_char); break;
            case 1: rand_colored_char = green(rand_uncolored_char); break;
            case 2: rand_colored_char = yellow(rand_uncolored_char); break;
            case 3: rand_colored_char = red(rand_uncolored_char); break;
            case 4: rand_colored_char = purple(rand_uncolored_char); break;
            case 5: rand_colored_char = cyan(rand_uncolored_char); break;
            case 6: rand_colored_char = blue(rand_uncolored_char); break;
        }
        static_line.append(rand_colored_char);
    }
    return "██" + static_line + "██";
}

int main(int argc, char *argv[])
{
    #ifdef _WIN32
            SetConsoleOutputCP(CP_UTF8);
            //i think ive heard that this is default on linux
        #endif
//    string static = {"", };

    cout << "▃▟██████████████████▙▃" << endl;
    cout << "██                  ██" << endl;
    cout << "██                  ██" << endl;
    cout << "██                  ██" << endl;
    cout << "██                  ██" << endl;
    cout << "██                  ██" << endl;
    cout << "▀▜██████████████████▛▀" << endl;
    while(true) {
        for(int xy = 0; xy < 400; xy++) {
            cursorUp(6);
            cout << screenStatic(18) << endl;
            cout << screenStatic(18) << endl;
            cout << screenStatic(18) << endl;
            cout << screenStatic(18) << endl;
            cout << screenStatic(18) << endl;

            cursorDown();
            this_thread::sleep_for(200ms);
        }
        cursorUp(4);
        this_thread::sleep_for(1s);
        cout << "\r" << "██  I'm watching..  ██" << endl;

        this_thread::sleep_for(1s);
        cursorUp(3);
        //good luck desciphering this lmao
        cout << "\r" << "██" + strPadRight("", 4) << cyan("▗▟▚▛▐▚▚█▃") << strPadRight("", 5) + "██" << endl;//18 spaces
        cout << "\r" << "██" + strPadRight("", 4) << cyan("█▚▀") + yellow("▞█▟▖") + cyan("▛▞") + cyan("▚") << strPadRight("", 4) + "██" << endl;
        cout << "\r" << "██" + strPadRight("", 4) << cyan("█▚") + (yellow("▘▝▝▙ ")) + cyan("▀▞▚") << strPadRight("", 4) + "██" << endl;//18 spaces
        cout << "\r" << "██" + strPadRight("", 4) << cyan("▛▐") + (yellow("▙▃▟")) + yellow(" █▖") + cyan("▀▞") << strPadRight("", 4) + "██" << endl;
        cout << "\r" << "██"  + strPadRight("", 4)<< cyan("▍") + yellow(" ▝▀") + (yellow("▃▞")) + yellow("▀ ") + cyan("▐▘") << strPadRight("", 4) + "██" << endl;//18 spaces
        this_thread::sleep_for(1500ms);
        cursorDown();

    }
}