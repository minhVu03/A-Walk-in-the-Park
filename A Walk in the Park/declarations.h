#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


struct Backgrounds{
    ALLEGRO_BITMAP *image;
    int x;
};

struct Character{
    ALLEGRO_BITMAP *frame[3];    //Not being used right now
    ALLEGRO_BITMAP *image;
    int x;
    int y;
    int bbRight, bbLeft, bbTop, bbBottom;
};

struct Obstacle{
    ALLEGRO_BITMAP *image;
    int x, y;
    int bbRight, bbLeft, bbTop, bbBottom;
    int dy;  //direction (up or down)
};

struct Life{
    ALLEGRO_BITMAP *image;
    int x;
};

struct Button{
    ALLEGRO_BITMAP *image;
    int x, y;
    bool clicked;

};

struct Danger{
    ALLEGRO_BITMAP *image;
    int x, y;
};
//Prototype
//Settings and backgrounds
int allegroSettings();
int loadBackgrounds(Backgrounds &city, Backgrounds &tree, Backgrounds &ground);
int loadText();
int moveBackgrounds(Backgrounds &city, Backgrounds &tree, Backgrounds &ground);
int imageSettings(Character &character, Obstacle &fog, Obstacle &log, Obstacle &bag, Button button[]);
//int initializeSounds(ALLEGRO_SAMPLE *startSound, ALLEGRO_SAMPLE *endSound, ALLEGRO_SAMPLE *loopSound);

//Character
int moveCharacter(Character &bunny); //Not being used right now
int character(bool &doPaused, Character &character);

//Obstacles
void obstaclePosition(Obstacle &fog, Obstacle &log, Obstacle &bag);
int moveObstacle(Obstacle &obstacle);
int staticObstacle(Obstacle &obstacle);

//Game status
int startGame(Backgrounds &city, Backgrounds &tree, Backgrounds &ground);
int gamePaused(Backgrounds &city, Backgrounds &tree, Backgrounds &ground);
int gameOver(Backgrounds &city, Backgrounds &tree, Backgrounds &ground, int score, int high, bool newHighscore);

//Functions for collision detection
void calcBoundsCharacter(Character &object);
void calcBoundsObstacle(Obstacle &object);
void drawBoundingBox(Character &image);
bool isCollision(Character &a, Obstacle &b);

//Score
void printScore(int score, int &high);
int highScore(int &high);
int compareHighscore(int score, int &high, bool &newHighscore);
int storeHighscore(int score, int high);
void printFinalScore(int score, int high);
void newBestScore(bool newHighscore);

//Lives
int initializeLives(Life heart[]);
void printLives(Life heart[], int lifeN);
void isHit(Danger &warning, Character &bunny, int &counte, int &lifeNum);
int printDanger(Danger &warning, int px, int py);

//Buttons
int printButton(Button &button, int px, int py);
bool buttonClicked(Button button);
