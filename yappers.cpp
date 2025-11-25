#include <iostream>//this one's for the cin and cout stuff
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <ctime>
#include <vector>
using namespace std;
void clearcmd ()
{
    cout << "\033[2J\033[H";
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
string bgRed (string word)
{
    return "\033[41m"  +  word  +  "\033[0m";
}
string bgGreen (string word)
{
    return "\033[42m" + word + "\033[0m";
}
string bgYellow (string word)
{
    return "\033[43m"  +  word  +  "\033[0m";
}
string bgBlue (string word)
{
    return "\033[44m" + word + "\033[0m";
}
string bgPurple (string word)
{
    return "\033[45m" + word + "\033[0m";
}
string bgCyan (string word)
{
    return "\033[46m" + word + "\033[0m";
}
string bgWhite (string word)
{
    return "\033[47m" + word + "\033[0m";
}
//get defined elsewhere
int player_x_pos, player_y_pos, boss_x_pos, boss_y_pos, player_hp, boss_hp;
bool poisoned = false;

void damagePlayer(int tile_data) {
    int damage = 0;
    switch (tile_data) {
        case 0:
        break;
        case 1:
            damage = 125;
        break;
        case 2:
            damage = 45;
        break;
        case 3:
            damage = 5;
        break;
        case 4://pur
            damage = 0;
            poisoned = true;
        break;
        case 5://whi
            damage = 1;
        break;
        case 255://whi
            damage = 25;
        break;
    }
    if (poisoned && damage != 0) {
        damage = damage * 2;
        poisoned = false;
    }
    player_hp = player_hp - damage;
}

string strPadRight(string to_pad, int total_length, char pad_with = ' ') {//why isnt this a default feature smh
    if (to_pad.size() >= total_length) {
        return to_pad;
    }
    return to_pad + string(total_length - to_pad.size(), pad_with);
}

string healthBar(double hp_remaining, double max_hp) {
    int usage_of_hp_bar;
    string hp_bar_colored, hp_bar_uncolored, full_hp_bar;
    usage_of_hp_bar = ceil(((hp_remaining / max_hp) * 100) / 2);

    full_hp_bar = "hp: " + to_string((int)hp_remaining) + "/" + to_string((int)max_hp);

    full_hp_bar = strPadRight(full_hp_bar, 50);

    if (usage_of_hp_bar > 30) {
        hp_bar_colored = bgGreen(full_hp_bar.substr(0, usage_of_hp_bar));
    } else if (usage_of_hp_bar > 15) {
        hp_bar_colored = bgYellow(full_hp_bar.substr(0, usage_of_hp_bar));
    } else if (hp_remaining > 0) {
        hp_bar_colored = bgRed(full_hp_bar.substr(0, usage_of_hp_bar));
    } else {
        return "[" + full_hp_bar + "]";
    }
    hp_bar_uncolored = full_hp_bar.substr(usage_of_hp_bar);
    return "[" + hp_bar_colored + hp_bar_uncolored + "]";
}

bool isAdjacent(int self_x, int self_y, int target_x, int target_y, bool allow_diagional = true)
{
    if (allow_diagional) {
        if ((self_x == target_x || self_x + 1 == target_x || self_x - 1 == target_x) &&
        (self_y == target_y || self_y + 1 == target_y || self_y - 1 == target_y)) {
            return true;
        }
    }

    if ((self_x + 1 == target_x || self_x - 1 == target_x) && self_y == target_y) {
        return true;
    }
    if ((self_y + 1 == target_y || self_y - 1 == target_y) && self_x == target_x) {
        return true;
    }
    return false;
}

vector<vector<int>> createField(int field_size, int field_size_horizontal, int types_amount, int seed)
{//god i hate this
    srand(seed);
    vector<vector<int>> boss_grid(field_size_horizontal, vector<int>(field_size));
    for (int y = 0; y < field_size; y++) {
        for (int x = 0; x < field_size_horizontal; x++) {
            boss_grid[x][y] = (rand() % types_amount) + 1;
        }
    }
    //get random boss and player positions, check if theyre not the same, and place them there,
    boss_x_pos = (rand() % field_size_horizontal);
    boss_y_pos = (rand() % field_size);
    player_x_pos = (rand() % field_size_horizontal);
    player_y_pos = (rand() % field_size);
    while(isAdjacent(player_x_pos, player_y_pos, boss_x_pos, boss_y_pos, true)) {
        player_x_pos = (rand() % field_size_horizontal);
        player_y_pos = (rand() % field_size);
    }
    boss_grid[boss_x_pos][boss_y_pos] = 100;
    boss_grid[player_x_pos][player_y_pos] = 255;
    return boss_grid;
}

void randomizeField(vector<vector<int>>& boss_grid, int field_size, int field_size_horizontal, int types_amount)
{
    for (int y = 0; y < field_size; y++) {
        for (int x = 0; x < field_size_horizontal; x++) {
            //skip boss and player
            if (boss_grid[x][y] == 100 || boss_grid[x][y] == 255) {
                continue;
            }//213
            if (boss_grid[x][y] == 1) {boss_grid[x][y] = 3;continue;}
            if (boss_grid[x][y] == 2) {boss_grid[x][y] = 1;continue;}
            if (boss_grid[x][y] == 3) {boss_grid[x][y] = rand() % types_amount + 1;continue;}
            if (boss_grid[x][y] == 4) {boss_grid[x][y] = rand() % (types_amount - 1) + 2;continue;}
            // 5/white is random
            boss_grid[x][y] = (rand() % types_amount) + 1;
        }
    }
}

int movePlayer(vector<vector<int>>& boss_grid, int field_size, int field_size_horizontal, string direction)
{
    int tile_data = 0;
    boss_grid[player_x_pos][player_y_pos] = 2;
    if (direction == "up") {
        if (player_y_pos == 0 || boss_grid[player_x_pos][player_y_pos - 1] == 100) {
            cout << "cant" << endl;
            return 1;
        } else {
            tile_data = boss_grid[player_x_pos][player_y_pos - 1];
            boss_grid[player_x_pos][player_y_pos - 1] = 255;
            --player_y_pos;
        }
    } else if (direction == "down") {
        if (player_y_pos == field_size - 1 || boss_grid[player_x_pos][player_y_pos + 1] == 100) {
            cout << "cant" << endl;
        } else {
            tile_data = boss_grid[player_x_pos][player_y_pos + 1];
            boss_grid[player_x_pos][player_y_pos + 1] = 255;
            ++player_y_pos;
        }
    } else if (direction == "left") {
        if (player_x_pos == 0 || boss_grid[player_x_pos - 1][player_y_pos] == 100) {
            cout << "cant" << endl;
        } else {
            tile_data = boss_grid[player_x_pos - 1][player_y_pos];
            boss_grid[player_x_pos - 1][player_y_pos] = 255;
            --player_x_pos;
        }
    } else if (direction == "right") {
        if (player_x_pos == field_size_horizontal - 1 || boss_grid[player_x_pos + 1][player_y_pos] == 100) {
            cout << "cant" << endl;
        } else {
            tile_data = boss_grid[player_x_pos + 1][player_y_pos];
            boss_grid[player_x_pos + 1][player_y_pos] = 255;
            ++player_x_pos;
        }
    } else if (direction == "stay") {
        cout << "okie :3" << endl;
        tile_data = boss_grid[player_x_pos][player_y_pos] = 255;
    } else {
        cout << "didnt understand that" << endl;
    }
    return tile_data;// returns 0 if it wasnt understood, or the tiledata of the tile user stepped on
}

void printField(vector<vector<int>> boss_grid, int arena_size, int arena_size_horizontal, int view_size = 2)
{
    int boss_texture_part, player_texture_part;
    player_texture_part = boss_texture_part = 0;

    vector<string> boss_texture;
    vector<string> boss_texture_left;
    vector<string> boss_texture_right;

    vector<string> player_texture;
    vector<string> player_texture_left;
    vector<string> player_texture_right;

    if (view_size == 1) {//2*1
        player_texture_left = {bgCyan(blue("▟▙"))};
        player_texture_right = {bgCyan(blue("▟▙"))};
        boss_texture_left = {bgCyan(red("▛▜"))};
        boss_texture_right = {bgCyan(red("▛▜"))};
    } else if (view_size == 2) {//4*2
        player_texture_left = {blue("▛▚"), blue("▞▜"), blue("▙") + red("▘"), red("▝") + blue("▟")};
        player_texture_right = {blue("▛▚"), blue("▞▜"), blue("▙") + red("▘"), red("▝") + blue("▟")};
        boss_texture_left = {white("▞▛"), white("▜█"), white("▛▛"), white("▛ ")};
        boss_texture_right = {white("█▛"), white("▜▚"), white(" ▜"), white(" ▜▜")};
    } else if (view_size == 3) {//6*3
        boss_texture_left = {
            "▟█", "██", "█▙",
            "▖▐", "▀▍", "▗█",
            "▜▚", "▚▜", "▛▘"};
        boss_texture_right = {
            "▟█", "██", "█▙",
            "█▖", "▐▀", "▍▗",
            "▝▜", "▛▞", "▞▛"};
        //todo change texture to left or right depending on eachother position
        player_texture_left = {
            cyan("▟█"), cyan("██"), cyan("█▙"),
            cyan("█▛"), yellow("▀") + cyan("▜"), purple("█") + cyan("▛"),
            yellow("▐▙"), yellow(bgBlue("▟")) + yellow("▃"), yellow("▞") + cyan("▘")};
        player_texture_right = {
            cyan("▟█"), cyan("██"), cyan("█▙"),
            cyan("▜"), purple("█") + cyan("▛"), yellow("▀") + cyan("▜█"),
            cyan("▝") + yellow("▚"), yellow("▃" + bgBlue("▙")), yellow("▟▍")};


        //player
        //▟████▙
        //█▛▀▜█▛
        //▟▙▟▃▞▘

        //boss
        //▟████▙
        //▖▐▀▍▗█
        //▀▙▙█▛▘

    }  else if (view_size == 4) {//8*4


        boss_texture_left = {
            "  ","  ","  ","  ",
            "  ","  ","  ","  ",
            "  ","  ","  ","  ",
            "  ","  ","  ","  ",
        };
        boss_texture_right = {
            "  ","  ","  ","  ",
            "  ","  ","  ","  ",
            "  ","  ","  ","  ",
            "  ","  ","  ","  ",
        };
        player_texture_left = {
            "  ","  ","  ","  ",
            "  ","  ","  ","  ",
            "  ","  ","  ","  ",
            "  ","  ","  ","  ",
        };
        player_texture_right = {
            cyan("▗█"),cyan("██"),cyan("▀▜"),cyan("▛▚"),
            cyan("█")+cyan(bgRed("▃")), cyan("█▘"), yellow("▗") + yellow(("▐")), yellow(("▍")) + cyan("▐"),
            cyan("██"), yellow(" ▃"), yellow("▟▟"), yellow("▙")+ cyan("▐"),
            cyan("█▖"), yellow(" ▜"), yellow("█▃"),yellow("▞") + cyan("▍"),
        };
//▗███▀▜▛▚
//█▃█▘▗▐▍▐
//██ ▃▟▟▙▐
//█▖ ▜█▃▞▐

//█ █ █ █ █ █ █ █ █ █ █ █ █ █ █
//▘ ▝ ▖ ▗ ▀ ▃ ▐ ▍ ▞ ▚ ▛ ▜ ▙ ▟ █
//before
//▍▍▜▀▍█▞▍
//▙▝ ▐▘▀▝▃
// ▃▖█▚▗ ▞
//▀▖▀▙▗▜▜▘
//after
//▗▟██▍█▖▖
//▛▀▀▜▘▀▝▚
//▙  ▟▚▗ ▞
//▀█▀▙▗▜▜▘


    } else {//10*5
        cout << "make your own textures, you need 50 characters total, good luck" << endl;
        exit(0);
    }

    if (player_x_pos > boss_x_pos) {
        boss_texture = boss_texture_right;
        player_texture = player_texture_left;
    } else {
        boss_texture = boss_texture_left;
        player_texture = player_texture_right;
    }

    bool encountered_player_first = false, encountered_boss_first = false;
    for (int y = 0; y < arena_size; y++) {//controls vertical lines
        for (int sizeY = 0; sizeY < view_size; sizeY++) {//controls vertical scaling
            for (int x = 0; x < arena_size_horizontal; x++) {//controls horizontal lines
                for (int sizeX = 0; sizeX < view_size; sizeX++) {//controls horizontal scaling

                    switch(boss_grid[x][y]) {

                        case 0://if you see blue i fucked something up
                            cout << bgBlue("  ");
                        break;
                        case 1:
                            cout << bgRed("  ");
                        break;
                        case 2:
                            cout << bgYellow("  ");
                        break;
                        case 3:
                            cout << bgGreen("  ");
                        break;
                        case 4:
                            cout << bgPurple("  ");
                        break;
                        case 5:
                            cout << bgWhite("  ");
                        break;
                        case 100://boss
                            cout << boss_texture[boss_texture_part];
                            ++boss_texture_part;
                        break;
                        case 255://player
                            cout << player_texture[player_texture_part];
                            ++player_texture_part;
                        break;

                    }
                }
            }
        cout << "\n";
        }
    }
}

void PsRandField(int seed)
{
//    cout << seed << endl;
    string userReturns, action;
    int color_types, view_size, number_of_types, arena_size, arena_size_horizontal, max_boss_hp, max_player_hp;
    view_size = 4;
    arena_size = 3;
    arena_size_horizontal = 7;
    vector<vector<int>> boss_grid;
    color_types = 5;
    max_boss_hp = boss_hp = 7500;
    max_player_hp = player_hp = 2500;

    string field_types[] = {"red", "yellow", "green", "purple", "white"};
    number_of_types = (sizeof(field_types)/sizeof(field_types[0]));
    //generates the pseudorandom tiles

    //initial creation of the thing, call only at the start
    //printField(boss_grid, arena_size, view_size);

    //randomizes existing bossgrid

    //gives the graphical output
    boss_grid = createField(arena_size, arena_size_horizontal, number_of_types, seed);
    while(boss_hp > 0 && player_hp > 0) {
        bool continue_loop = false;
        clearcmd();
        cout << strPadRight("boss: ", 10) << healthBar(boss_hp, max_boss_hp) << endl;
        cout << strPadRight("player: ", 10) << healthBar(player_hp, max_player_hp) << "\n" << endl;
        randomizeField(boss_grid, arena_size, arena_size_horizontal, number_of_types);
        printField(boss_grid, arena_size, arena_size_horizontal, view_size);
        int tile_data = 0;
        while(tile_data == 0) {
            cin >> action;
            if (action == "hit" && isAdjacent(player_x_pos, player_y_pos, boss_x_pos, boss_y_pos, false)) {
                cout << "yeppers" << endl;
                ++arena_size;
                ++arena_size_horizontal;
                boss_hp = boss_hp - 1000;
                boss_grid = createField(arena_size, arena_size_horizontal, number_of_types, seed);
                continue_loop = true;
                tile_data = 999;
                continue;
            }
            tile_data = movePlayer(boss_grid, arena_size, arena_size_horizontal, action);
            damagePlayer(tile_data);
        }
        if (continue_loop) {
            continue_loop  = false;
            continue;
        }
    }
}