
#include "declarations.h"

#define RED         al_map_rgb(255, 0, 0)

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_EVENT ev;

void calcBoundsCharacter(Character &object) {
    object.bbLeft = object.x;
	object.bbTop  = object.y;
	object.bbRight = object.bbLeft + al_get_bitmap_width(object.image);
	object.bbBottom = object.bbTop + al_get_bitmap_height(object.image);
}

void calcBoundsObstacle(Obstacle &object) {
    object.bbLeft = object.x;
	object.bbTop  = object.y;
	object.bbRight = object.bbLeft + al_get_bitmap_width(object.image);
	object.bbBottom = object.bbTop + al_get_bitmap_height(object.image);

}

void drawBoundingBox(Character &image) {
    calcBoundsCharacter(image);
	al_draw_line(image.bbLeft, image.bbTop, image.bbRight, image.bbTop, RED, 1);
    al_draw_line(image.bbLeft, image.bbBottom, image.bbRight, image.bbBottom, RED, 1);
	al_draw_line(image.bbLeft, image.bbTop, image.bbLeft, image.bbBottom, RED, 1);
	al_draw_line(image.bbRight, image.bbTop, image.bbRight, image.bbBottom, RED,1);
}

bool isCollision(Character &a, Obstacle &b) {
    calcBoundsCharacter(a);
    calcBoundsObstacle(b);
    if (a.bbBottom < b.bbTop) {
        return false;
    }
    else if (a.bbTop > b.bbBottom) {
        return false;
    }
    else if (a.bbRight < b.bbLeft) {
        return false;
    }
    else if (a.bbLeft > b.bbRight) {
        return false;
    }
    return true;
}

