#include "declarations.h"

extern ALLEGRO_DISPLAY *display, *endGame;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_EVENT ev;
extern ALLEGRO_FONT *font, *leavesTitle, *normalText;

#define BACKGROUND al_map_rgb(255, 0, 255)
#define FOREGROUND al_map_rgb(26, 165, 35)

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

    al_draw_text(font, FOREGROUND, 1800/2 - 10, 130, ALLEGRO_ALIGN_CENTRE, "A Walk in the Park");

    return 0;
}

int gameOver(Backgrounds &city, Backgrounds &tree, Backgrounds &ground){
    al_draw_bitmap(city.image, 0, 0, 0);
    al_draw_bitmap(tree.image, 0, 0, 0);
    al_draw_bitmap(ground.image, 0, 0, 0);

    al_draw_text(font, FOREGROUND, 1800/2, 150, ALLEGRO_ALIGN_CENTRE, "GAME OVER");

    return 0;
}

int gamePaused(Backgrounds &city, Backgrounds &tree, Backgrounds &ground){
    al_draw_bitmap(city.image, 0, 0, 0);
    al_draw_bitmap(tree.image, 0, 0, 0);
    al_draw_bitmap(ground.image, 0, 0, 0);

   al_draw_text(font, FOREGROUND, 1800/2, 130, ALLEGRO_ALIGN_CENTRE, "PAUSED");
    return 0;
}

int gameInstruction(Keys instruction, int px, int py){
    al_draw_bitmap(instruction.image, px, py, 0);
}


