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
string bg_red (string word)
{
    return "\033[41m"  +  word  +  "\033[0m";
}
string bg_green (string word)
{
    return "\033[42m" + word + "\033[0m";
}
string bg_yellow (string word)
{
    return "\033[43m"  +  word  +  "\033[0m";
}
string bg_blue (string word)
{
    return "\033[44m" + word + "\033[0m";
}
string bg_purple (string word)
{
    return "\033[45m" + word + "\033[0m";
}
string bg_cyan (string word)
{
    return "\033[46m" + word + "\033[0m";
}
string bg_white (string word)
{
    return "\033[47m" + word + "\033[0m";
}



vector<vector<int>> createField(int field_size, int types_amount, int seed){//god i hate this
    srand(seed);
    vector<vector<int>> boss_grid(field_size  * 2, vector<int>(field_size));
    for (int y = 0; y < field_size; y++) {
        for (int x = 0; x < field_size * 2; x++) {
            int temp = (rand() % types_amount) + 1;
            boss_grid[x][y] = temp;
        }
    }
    //get random boss and player positions, check if theyre not the same, and place them there,
    int rand_boss_x, rand_boss_y, rand_player_x, rand_player_y;
    rand_boss_x = (rand() % field_size * 2);
    rand_boss_y = (rand() % field_size);
    rand_player_x = (rand() % field_size * 2);
    rand_player_y = (rand() % field_size);
    while(rand_boss_x == rand_player_x || rand_boss_x == rand_player_x + 1 || rand_boss_x == rand_player_x - 1) {
        rand_player_x = (rand() % field_size * 2);
    }
    while(rand_boss_y == rand_player_y || rand_boss_y == rand_player_y + 1 || rand_boss_y == rand_player_y - 1) {
        rand_player_y = (rand() % field_size);
    }
    boss_grid[rand_boss_x][rand_boss_y] = 100;
    boss_grid[rand_player_x][rand_player_y] = 255;
    return boss_grid;
}

void randomizeField(vector<vector<int>>& boss_grid, int field_size,int types_amount) {
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

int movePlayer(vector<vector<int>>& boss_grid, int field_size, string direction) {
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
        if (player_y_pos == 0) {
            cout << "cant" << endl;
            return 1;
        } else {
            boss_grid[player_x_pos][player_y_pos - 1] = 255;
        }
    } else if (direction == "down") {
        if (player_y_pos == field_size) {
            cout << "cant" << endl;
            return 1;
        } else {
            boss_grid[player_x_pos][player_y_pos + 1] = 255;
        }
    } else if (direction == "left") {
        if (player_x_pos == 0) {
            cout << "cant" << endl;
            return 1;
        } else {
            boss_grid[player_x_pos - 1][player_y_pos] = 255;
        }
    } else if (direction == "right") {
        if (player_x_pos == field_size * 2) {
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

void printField(vector<vector<int>> boss_grid, int arena_size, int view_size = 2) {
    int boss_texture_part, player_texture_part;
    player_texture_part = boss_texture_part = 0;

    vector<string> player_texture;
    vector<string> boss_texture;
    vector<string> boss_texture_left;
    vector<string> boss_texture_right;

    if (view_size == 1) {
        player_texture = {bg_cyan(blue("▛▜"))};
        boss_texture = {bg_cyan(blue("▛▜"))};
    } else if (view_size == 2) {
        player_texture = {blue("▛▚"), blue("▞▜"), blue("▙") + red("▘"), red("▝") + blue("▟")};
//        player_texture = {"a ", "a ", "a ", "a "};
//        boss_texture = {blue("▛▚"), blue("▞▜"), blue("▙") + red("▘"), red("▝") + blue("▟")};
        boss_texture = {white("▞▛"), white("▜▉"), white("▛▛"), white("▛ ")};
        boss_texture_right = {white("█▛"), white("▜▚"), white(" ▜"), white(" ▜▜")};

//        boss_texture = {"a ", "a ", "a ", "a "};

    } else if (view_size == 3) {
        //string player_texture[16] =
        //string boss_texture[16] =
    } else {
        cout << "make your own textures" << endl;
        exit(0);
    }

    for (int y = 0; y < arena_size; y++) {//controls vertical lines
        for (int sizeY = 0; sizeY < view_size; sizeY++) {//controls vertical scaling
            for (int x = 0; x < arena_size * 2; x++) {//controls horizontal lines
                for (int sizeX = 0; sizeX < view_size; sizeX++) {//controls horizontal scaling

                    switch(boss_grid[x][y]) {

                        case 0:
                            cout << bg_blue("  ");
                        break;
                        case 1:
                            cout << bg_red("  ");
                        break;
                        case 2:
                            cout << bg_yellow("  ");
                        break;
                        case 3:
                            cout << bg_green("  ");
                        break;
                        case 4:
                            cout << bg_purple("  ");
                        break;
                        case 5:
                            cout << bg_white("  ");
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

void PsRandField(int seed){
//    cout << seed << endl;
    string userReturns, test;
    int color_types, view_size, number_of_types, boss_hp, player_hp, arena_size;
    view_size = 2;
    arena_size = 3;
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
        boss_grid = randomizeField(boss_grid, arena_size, number_of_types);
        printField(boss_grid, arena_size, view_size);
        int success = 1;
        while(success != 0) {
            cin >> test;
            success = movePlayer(boss_grid, arena_size, test);
        }
    }
    
}