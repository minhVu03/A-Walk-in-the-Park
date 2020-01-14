#include "declarations.h"

extern ALLEGRO_DISPLAY *display, *endGame;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_EVENT ev;
extern ALLEGRO_FONT *font, *leavesTitle, *normalText;

#define FOREGROUND al_map_rgb(0, 0, 0)

void printScore(int score, int &high){
    char scoreStr[10];
    char highStr[10];
    snprintf(scoreStr, 10, "%d", score);
    if(score > high){
        high = score;

    }
    snprintf(highStr, 10, "%d", high);
    al_draw_text(normalText, FOREGROUND, 1500, 30, ALLEGRO_ALIGN_CENTRE, "Distance: ");
    al_draw_text(normalText, FOREGROUND, 1700, 30, ALLEGRO_ALIGN_CENTRE, scoreStr);

    al_draw_text(normalText, FOREGROUND, 1500, 100, ALLEGRO_ALIGN_CENTRE, "Best: ");
    al_draw_text(normalText, FOREGROUND, 1710, 100, ALLEGRO_ALIGN_CENTRE, highStr);
}

int highScore(int &high){
    FILE *file;

    file = fopen("highscore.txt", "r");
        //Check if file exist
        if(!file) {
            printf ("No file");
            return 1;
        }
    fscanf(file, "%d", &high);
    fclose(file);
    return 0;
}

int compareHighscore(int score, int &high, bool &newHighscore){
    if (score > high){
        high = score;
        newHighscore = true;
    }
    return 0;
}

//Write the high score to file
int storeHighscore(int score, int high){
    FILE *file;

    file = fopen("highscore.txt", "w");
        //Check if file exist
        if(!file) {
            printf ("No file");
            return 1;
        }
    fprintf(file, "%d", high);

    fclose(file);
    return 0;
}

void printFinalScore(int score, int high, bool newHighscore){
    char scoreStr[10];
    char highStr[10];
    snprintf(scoreStr, 10, "%d", score);
    snprintf(highStr, 10, "%d", high);
    al_draw_text(font, FOREGROUND, 640, 500, ALLEGRO_ALIGN_LEFT, "Distance: ");
    al_draw_text(font, FOREGROUND, 1000, 500, ALLEGRO_ALIGN_LEFT, scoreStr);

    if (newHighscore == false){
        al_draw_text(font, FOREGROUND, 560, 630, ALLEGRO_ALIGN_LEFT, "Best Distance: ");
        al_draw_text(font, FOREGROUND, 1200, 630, ALLEGRO_ALIGN_LEFT, highStr);
    }
    if (newHighscore == true){
        al_draw_text(font, FOREGROUND, 510, 610, ALLEGRO_ALIGN_LEFT, "New Best Distance: ");
        al_draw_text(font, FOREGROUND, 1240, 610, ALLEGRO_ALIGN_LEFT, highStr);
    }
}

