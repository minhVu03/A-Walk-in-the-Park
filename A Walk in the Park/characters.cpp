#include "declarations.h"

//const float FPS = 100;			// set frame rate   (60 would be more normal)

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_EVENT ev;

int character(bool &doPaused, Character &character){
    al_draw_bitmap(character.image, character.x, character.y, 0);
    al_get_next_event(event_queue, &ev);

    //Use keyboard to control character
         	switch(ev.keyboard.keycode) {
            	case ALLEGRO_KEY_UP:
            	    if(character.y > 0){
                        character.y -= 20;
            	    }
               		break;
	            case ALLEGRO_KEY_DOWN:
	                if(character.y < 540){
                        character.y += 20;
	                }
            		break;
                case ALLEGRO_KEY_LEFT:
                    if(character.x > 0){
                        character.x -= 20;
                    }
                    break;
                case ALLEGRO_KEY_RIGHT:
                    if(character.x < 1800){
                        character.x += 20;
                    }
                    break;
               	case ALLEGRO_KEY_ESCAPE:
               		doPaused = true;
               		break;
         	}

    return 0;
}

int moveCharacter(Character &bunny){

    //ALLEGRO_BITMAP *frame[3];

	/*bunny.image[0] = al_load_bitmap("bunny1.png"); // Load frames
	bunny.image[1] = al_load_bitmap("bunny2.png");
	bunny.image[2] = al_load_bitmap("bunny3.png");*/

	// set current frame and position.
	int curr = 0;
	int posx = 100;
	int posy = 530;
	al_draw_bitmap(bunny.frame[0], posx, posy, 0);
	al_flip_display();
	bool doexit = false;

	//al_start_timer(timer);		// 4.   Start the timer.

	if (!doexit) {

      	al_get_next_event(event_queue, &ev);

      	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        	doexit = true;
      	}
        else if(ev.type == ALLEGRO_EVENT_TIMER) {
        	curr++;
        	curr %= 3;
	      	//al_clear_to_color(SLATEGREY);
			al_draw_bitmap(bunny.frame[curr], posx, posy, 0);
			//al_flip_display();
		}
	}

	// Wait for 2 seconds. . .
	//al_rest(2);

	// Release the bitmap data and then exit
	for (int i=0; i<3; i++)
   		al_destroy_bitmap(bunny.frame[i]);
        //al_destroy_display(display);
	return 0;
}
