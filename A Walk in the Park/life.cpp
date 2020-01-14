#include "declarations.h"

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_EVENT ev;

int initializeLives(Life heart[]){
    for (int i = 0; i < 3; i++){
        heart[i].image = al_load_bitmap("heart.png"); // Load our picture
        if (!heart[i].image) {
       		al_show_native_message_box(display, "Error", "Error",
    			"heart.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    		return -1;
        }
    }
    return 0;
}
void printLives(Life heart[], int lifeN){
    int x = 30;

    for (int i = 0; i < lifeN; i++){
        al_draw_bitmap(heart[i].image, x, 30, 0);
        x += 150;
    }
}

void isHit(Danger &warning, Character &bunny, int &counte, int &lifeNum, ALLEGRO_SAMPLE *hit){
    if (counte == 1){
        al_play_sample(hit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }
    if (counte == 10){
        lifeNum--;
    }
    if (counte >= 0 && counte <= 10){
        printDanger(warning, bunny.x + al_get_bitmap_width(bunny.image), bunny.y + 5);
    }
}

int printDanger(Danger &warning, int px, int py){

    warning.image = al_load_bitmap("danger.png"); // Load our picture
        if (!warning.image) {
       		al_show_native_message_box(display, "Error", "Error",
    			"danger.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    		return -1;
        }
    warning.x = px;
    warning.y = py;
    al_draw_bitmap(warning.image, warning.x, warning.y, 0);
    al_flip_display();
    //al_destroy_bitmap(warning.image);
    return 0;
}
