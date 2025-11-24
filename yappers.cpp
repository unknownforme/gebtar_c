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

vector<vector<int>> createField(int field_size, int types_amount, int seed)
{//god i hate this
    srand(seed);
    vector<vector<int>> boss_grid(field_size  * 2, vector<int>(field_size));
    for (int y = 0; y < field_size; y++) {
        for (int x = 0; x < field_size * 2; x++) {
            boss_grid[x][y] = (rand() % types_amount) + 1;
        }
    }
    //get random boss and player positions, check if theyre not the same, and place them there,
    int rand_boss_x, rand_boss_y, rand_player_x, rand_player_y;
    rand_boss_x = (rand() % field_size * 2);
    rand_boss_y = (rand() % field_size);
    rand_player_x = (rand() % field_size * 2);
    rand_player_y = (rand() % field_size);
    while(isAdjacent(rand_player_x, rand_player_y, rand_boss_x, rand_boss_y, true)) {
        rand_player_x = (rand() % field_size * 2);
        rand_player_y = (rand() % field_size);
    }
    boss_grid[rand_boss_x][rand_boss_y] = 100;
    boss_grid[rand_player_x][rand_player_y] = 255;
    return boss_grid;
}

void randomizeField(vector<vector<int>>& boss_grid, int field_size,int types_amount)
{
    for (int y = 0; y < field_size; y++) {
        for (int x = 0; x < field_size * 2; x++) {
            //skip boss and player
            if (boss_grid[x][y] == 100 || boss_grid[x][y] == 255) {
                continue;
            }
            boss_grid[x][y] = (rand() % types_amount) + 1;
        }
    }
}

int movePlayer(vector<vector<int>>& boss_grid, int field_size, string direction)
{
    int player_x_pos, player_y_pos, boss_x_pos, boss_y_pos;
    bool stays = false, found_player = false, found_boss = false;
    for (int y = 0; y < field_size; y++) {
        for (int x = 0; x < field_size * 2; x++) {
            if (boss_grid[x][y] == 255) {
                player_x_pos = x;
                player_y_pos = y;
                found_player = true;
            }
            if (boss_grid[x][y] == 100) {
                boss_x_pos = x;
                boss_y_pos = y;
                found_boss = true;
            }
            if (found_player && found_boss) {
                y = field_size;
                break;
            }
        }
    }
    if (direction == "up") {
        if (player_y_pos == 0 || boss_grid[player_x_pos][player_y_pos - 1] == 100) {
            cout << "cant" << endl;
            return 1;
        } else {
            boss_grid[player_x_pos][player_y_pos - 1] = 255;
        }
    } else if (direction == "down") {
        if (player_y_pos == field_size - 1 || boss_grid[player_x_pos][player_y_pos + 1] == 100) {
            cout << "cant" << endl;
            return 1;
        } else {
            boss_grid[player_x_pos][player_y_pos + 1] = 255;
        }
    } else if (direction == "left") {
        if (player_x_pos == 0 || boss_grid[player_x_pos - 1][player_y_pos] == 100) {
            cout << "cant" << endl;
            return 1;
        } else {
            boss_grid[player_x_pos - 1][player_y_pos] = 255;
        }
    } else if (direction == "right") {
        if (player_x_pos == field_size * 2 - 1 || boss_grid[player_x_pos + 1][player_y_pos] == 100) {
            cout << "cant" << endl;
            return 1;
        } else {
            boss_grid[player_x_pos + 1][player_y_pos] = 255;

        }
    } else if (direction == "stay") {
        cout << "okie :3" << endl;
        stays = true;
    } else {
        cout << "didnt understand that";
        return 1;
    }
    if (!stays) {
        boss_grid[player_x_pos][player_y_pos] = 2;
    }
    return 0;
}

void printField(vector<vector<int>> boss_grid, int arena_size, int view_size = 2)
{
    int boss_texture_part, player_texture_part;
    player_texture_part = boss_texture_part = 0;

    vector<string> boss_texture;
    vector<string> boss_texture_left;
    vector<string> boss_texture_right;

    vector<string> player_texture;
    vector<string> player_texture_left;
    vector<string> player_texture_right;

    if (view_size == 1) {
        player_texture = {bgCyan(blue("▟▙"))};
        boss_texture = {bgCyan(red("▛▜"))};
    } else if (view_size == 2) {
        player_texture = {blue("▛▚"), blue("▞▜"), blue("▙") + red("▘"), red("▝") + blue("▟")};
        boss_texture = {white("▞▛"), white("▜█"), white("▛▛"), white("▛ ")};
        boss_texture_right = {white("█▛"), white("▜▚"), white(" ▜"), white(" ▜▜")};
    } else if (view_size == 3) {
        boss_texture = {
            "▟█", "██", "█▙",
            "▖▐", "▀▍", "▗█",
            "▀▙", "▙█", "▛▘"};
        boss_texture = {
            "▟█", "██", "█▙",
            "█▖", "▐▀", "▍▗",
            "▝▜", "█▟", "▟▀"};
        //todo change texture to left or right depending on eachother position
        player_texture = {
            cyan("▟█"), cyan("██"), cyan("█▙"),
            cyan("█▛"), yellow("▀") + cyan("▜"), purple("█") + cyan("▛"),
            yellow("▐▙"), yellow("▟▃"), yellow("▞") + cyan("▘")};
        player_texture_right = {
            cyan("▟█"), cyan("██"), cyan("█▙"),
            cyan("▜"), purple("█") + cyan("▛"), yellow("▀") + cyan("▜█"),
            cyan("▝") + yellow("▚"), yellow("▃▙"), yellow("▟▍")};

        //['▘','▝','▀','▖','▍','▞','▛','▗','▚','▐','▜','▃','▙','▟','█',' ']

        //player
        //▟████▙
        //█▛▀▜█▛
        //▟▙▟▃▞▘

        //boss
        //▟████▙
        //▖▐▀▍▗█
        //▀▙▙█▛▘

    } else {
        cout << "make your own textures" << endl;
        exit(0);
    }
    for (int y = 0; y < arena_size; y++) {
        auto testing = find(boss_grid[y].begin(),boss_grid[y].end(), 255);
        if (testing != boss_grid[y].end()) {
        cout << "wowa" << endl;
        }
    }
    bool encountered_player_first = false, encountered_boss_first = false;
    for (int y = 0; y < arena_size; y++) {//controls vertical lines
        for (int sizeY = 0; sizeY < view_size; sizeY++) {//controls vertical scaling
            for (int x = 0; x < arena_size * 2; x++) {//controls horizontal lines
                for (int sizeX = 0; sizeX < view_size; sizeX++) {//controls horizontal scaling

                    switch(boss_grid[x][y]) {

                        case 0:
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
                            if (!encountered_boss_first && !encountered_player_first) {
                                encountered_boss_first = true;
                                boss_texture = boss_texture_right;
                            } else if (!encountered_boss_first) {
                                boss_texture = boss_texture_left;
                            }

                            cout << boss_texture[boss_texture_part];
                            ++boss_texture_part;
                        break;
                        case 255://player
                            if (!encountered_boss_first && !encountered_player_first) {
                                encountered_player_first = true;
                            } else if (!encountered_player_first) {
                                player_texture = player_texture_left;
                            }
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
    string userReturns, test;
    int color_types, view_size, number_of_types, boss_hp, player_hp, arena_size;
    view_size = 3;
    arena_size = 5;
    vector<vector<int>> boss_grid;
    color_types = 5;
    boss_hp = 10000;
    player_hp = 2500;

    string field_types[] = {"red", "yellow", "green", "purple", "white"};
    number_of_types = (sizeof(field_types)/sizeof(field_types[0]));
    //generates the pseudorandom tiles

    //initial creation of the thing, call only at the start
    //printField(boss_grid, arena_size, view_size);

    //randomizes existing bossgrid

    //gives the graphical output
    boss_grid = createField(arena_size, number_of_types, seed);
    while(boss_hp > 0 && player_hp > 0) {
        clearcmd();
        randomizeField(boss_grid, arena_size, number_of_types);
        printField(boss_grid, arena_size, view_size);
        int success = 1;
        while(success != 0) {
            cin >> test;
            success = movePlayer(boss_grid, arena_size, test);
        }
    }
}