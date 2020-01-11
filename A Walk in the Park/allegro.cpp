#include "declarations.h"

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_EVENT ev;
extern ALLEGRO_FONT *font, *leavesTitle, *normalText;

int allegroSettings() {

    // initialize display
	if (!display) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}

   	// Initialize keyboard routines
	if (!al_install_keyboard()) {
	    al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
     	return -1;
   	}

	// need to add image processor
 	if (!al_init_image_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize image addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	// 2. setup timer
   	if (!timer) {
   		al_show_native_message_box(display, "Error", "Error", "Failed to create timer!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

	// set up event queue
	if (!event_queue) {
		al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
      	return -1;
	}
	al_register_event_source(event_queue, al_get_display_event_source(display));
 	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));			// 3. register timer events

    return 0;
}

int imageSettings(Character &character, Obstacle &fog, Obstacle &log, Obstacle &bag, Button button[]){
    //Load obstacles
    fog.image = al_load_bitmap("fogObstacle.png");
    log.image = al_load_bitmap("logObstacle.png");
    bag.image = al_load_bitmap("bagObstacle.png");
    //Check image settings
    if (!fog.image) {
       		al_show_native_message_box(display, "Error", "Error",
    			"fogObstacle.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    		return -1;
	}
	if (!log.image) {
       		al_show_native_message_box(display, "Error", "Error",
    			"logObstacle.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    		return -1;
	}
	if (!bag.image) {
       		al_show_native_message_box(display, "Error", "Error",
    			"bagObstacle.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    		return -1;
	}

    //Load character
    character.image = al_load_bitmap("bunny1.png");
    //Check image settings
	if (!character.image) {
       		al_show_native_message_box(display, "Error", "Error",
    			"bunny1.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    		return -1;
	}

    for(int i = 0; i < 3; i++){
            button[i].image = al_load_bitmap("blackButton.png"); // Load our picture
            if (!button[i].image) {
       		al_show_native_message_box(display, "Error", "Error",
    			"button.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    		return -1;
	}
    }

	return 0;
}

int loadText(){
    //Load text font
	font = al_load_ttf_font("snowFairy.ttf", 70, 0);
    if (!font){
      al_show_native_message_box(display, "Error", "Error", "Could not load snow fairy title.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
    }

    leavesTitle = al_load_ttf_font("leaves title.ttf", 80, 0);
    if (!font){
      al_show_native_message_box(display, "Error", "Error", "Could not load leaves title.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
    }

    normalText = al_load_ttf_font("normal text.ttf", 90, 0);
    if (!font){
      al_show_native_message_box(display, "Error", "Error", "Could not load normal text.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
    }

    return 0;

}

int loadBackgrounds(Backgrounds &city, Backgrounds &tree, Backgrounds &ground){

	city.x = 0;
    tree.x = 0;
    ground.x = 0;
	//Load city skyline background
	city.image = al_load_bitmap("cityBackground.png"); // Load our picture
	if (!city.image) {
       		al_show_native_message_box(display, "Error", "Error",
    			"cityBackground.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    		return -1;
	}

	//Load trees background
	tree.image = al_load_bitmap("treeBackground.png"); // Load our picture
	if (!tree.image) {
       		al_show_native_message_box(display, "Error", "Error",
    			"treeBackground.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    		return -1;
	}
	//Load ground background
	ground.image = al_load_bitmap("groundBackground.png"); // Load our picture
	if (!ground.image) {
       		al_show_native_message_box(display, "Error", "Error",
    			"groundBackground.png", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    		return -1;
	}


    return 0;
}

