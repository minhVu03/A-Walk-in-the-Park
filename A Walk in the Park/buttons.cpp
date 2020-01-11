#include "declarations.h"

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_EVENT ev;

int printButton(Button &button, int px, int py){

	button.x = px;
	button.y = py;
    al_draw_bitmap(button.image, button.x, button.y, 0);
    return 0;
}
bool buttonClicked(Button button){
    button.clicked = false;
    //al_wait_for_event(event_queue, &ev);
    al_get_next_event(event_queue, &ev);
    if(ev.mouse.x >= button.x && ev.mouse.x <= button.x + al_get_bitmap_width(button.image) && ev.mouse.y >= button.y  && ev.mouse.y <= button.y + al_get_bitmap_height(button.image) && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
    printf("mouseclicked(%d, %d)\n", ev.mouse.x, ev.mouse.y);
    button.clicked = true;
    }
    //If mouse is clicked outside boundaries of the button
    else if(ev.mouse.x >= 500 && ev.mouse.y >= 500 && ev.mouse.x <= 800 && ev.mouse.y <= 800){
    printf(" mouse is working(%d, %d)\n", ev.mouse.x, ev.mouse.y);
    }
    return button.clicked;
}
