#include "declarations.h"

extern ALLEGRO_DISPLAY *display, *endGame;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_EVENT ev;
extern ALLEGRO_FONT *font, *leavesTitle, *normalText;

#define BACKGROUND al_map_rgb(255, 0, 255)
#define FOREGROUND al_map_rgb(0, 179, 0)

int moveBackgrounds(Backgrounds &city, Backgrounds &tree, Backgrounds &ground){
    //draw two backgrounds connected to each other for each layer
    al_draw_bitmap(city.image, city.x, 0, 0);
    al_draw_bitmap(city.image, city.x + 1800, 0, 0);

    al_draw_bitmap(tree.image, tree.x, 0, 0);
    al_draw_bitmap(tree.image, tree.x + 1800, 0, 0);

    al_draw_bitmap(ground.image, ground.x, 0, 0);
    al_draw_bitmap(ground.image, ground.x + 1800, 0, 0);

    //Control speed of background
    city.x --;
    tree.x -= 3;
    ground.x -= 5;

    //Repeat
    if (city.x <= -1800){
        city.x = 0;
    }
    if (tree.x <= -1800){
        tree.x = 0;
    }
    if (ground.x <= -1800){
        ground.x = 0;
    }

    //al_rest(.01);
	return 0;

}

int startGame(Backgrounds &city, Backgrounds &tree, Backgrounds &ground){
    al_draw_bitmap(city.image, 0, 0, 0);
    al_draw_bitmap(tree.image, 0, 0, 0);
    al_draw_bitmap(ground.image, 0, 0, 0);

    al_draw_text(font, FOREGROUND, 1800/2, (900/4), ALLEGRO_ALIGN_CENTRE, "A Walk in the Park");

    return 0;
}

int gameOver(Backgrounds &city, Backgrounds &tree, Backgrounds &ground, int score, int high, bool newHighscore){
    al_draw_bitmap(city.image, 0, 0, 0);
    al_draw_bitmap(tree.image, 0, 0, 0);
    al_draw_bitmap(ground.image, 0, 0, 0);

    al_draw_text(font, FOREGROUND, 1800/2, (900/4), ALLEGRO_ALIGN_CENTRE, "GAME OVER");
    al_draw_text(font, FOREGROUND, 1800/2, 300, ALLEGRO_ALIGN_CENTRE, "You did not get home safely!");
    //Print the scores to display
    printFinalScore(score, high);
    newBestScore(newHighscore);
    return 0;
}

int gamePaused(Backgrounds &city, Backgrounds &tree, Backgrounds &ground){
    al_draw_bitmap(city.image, 0, 0, 0);
    al_draw_bitmap(tree.image, 0, 0, 0);
    al_draw_bitmap(ground.image, 0, 0, 0);

   al_draw_text(font, FOREGROUND, 1800/2, (900/4), ALLEGRO_ALIGN_CENTRE, "GAME PAUSED");
   //al_rest(.01);
   //al_draw_text(font, FOREGROUND, 1800/2, (900/2), ALLEGRO_ALIGN_CENTRE, "Do you want to continue?");
   //al_flip_display();

    return 0;
}


