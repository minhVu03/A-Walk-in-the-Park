
#include "declarations.h"

const float FPS = 60;			// set frame rate   (60 would be more normal)
const int SCREEN_W = 1800;      // screen width
const int SCREEN_H = 900;       // screen height

#define BACKGROUND al_map_rgb(255, 0, 255)
#define BUTTON al_map_rgb(0, 179, 0)

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *timer;
ALLEGRO_EVENT ev;
ALLEGRO_FONT *font, *leavesTitle, *normalText;



int main(int argc, char *argv[]){

    //Initializing allegro
    al_init();
    al_init_primitives_addon();
    al_install_mouse();
    al_init_image_addon(); //need this to put images into program
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon
    //initialize displays
    display = al_create_display(SCREEN_W, SCREEN_H);
    // add event queue object
    event_queue = al_create_event_queue();
    // 1. add timer object
	timer = al_create_timer(1.0 / FPS);    //affects speed of bunny

    //Check allegro settings
    allegroSettings();

    //Register event queues
    al_register_event_source(event_queue, al_get_display_event_source(display));
 	al_register_event_source(event_queue, al_get_keyboard_event_source());
 	al_register_event_source(event_queue, al_get_timer_event_source(timer));
 	al_register_event_source(event_queue, al_get_mouse_event_source());


    /********************* Declare and initialize variables ******************************/
    //ALLEGRO_SAMPLE *startSound = nullptr;
    //ALLEGRO_SAMPLE *endSound = nullptr;
    ALLEGRO_SAMPLE *loopSound = nullptr;
    //ALLEGRO_SAMPLE *hitSound = nullptr;

    //Obstacles
    Obstacle fog, bag, log;
    obstaclePosition(fog, log, bag);
    //score
    int counter = 0;
    int high = 0;

    //Backgrounds and character
    Backgrounds city, tree, ground;
    Button button[3];
    for (int i = 0; i < 3; i++){
        button[i].clicked = false;
    }

    Character bunny;
    bunny.x = 100;
    bunny.y = 540;

    Life lives[3];
    Danger warning;
    int lifeNum = 3;
    int counte = 11;

    bool gameOn = false;
    bool doExit = false;
    bool doPaused = false;
    bool newBest = false;
    bool replay = true;                   //put everything in while loop to replay

    //Load backgrounds
    loadBackgrounds(city, tree, ground);
    loadText();

    //Load character and obstacles and allegro settings
    imageSettings(bunny, fog, log, bag, button);

    //Load heart images
    initializeLives(lives);

    //Start the timer
 	al_start_timer(timer);

 	/************************************ SOunds ***********************************/
 	/******************************* Start menu ************************************/
 	while (gameOn == false && doExit == false && doPaused == false){
        //al_wait_for_event(event_queue, &ev);
        startGame(city, tree, ground); //will turn gameOn true when player press ENTER
        printButton(button[0], 750, 400);
        al_draw_text(font, BUTTON, 760, 410, ALLEGRO_ALIGN_LEFT, "START");

        if(buttonClicked(button[0]) == true || ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
            gameOn = true;
        }

        printButton(button[1], 750, 550);
        al_draw_text(font, BUTTON, 760, 560, ALLEGRO_ALIGN_LEFT, "EXIT");
        al_flip_display();
        if(buttonClicked(button[1]) == true){
            doExit = true;
        }
 	}
 	/******************************* Run the game **********************************/
    highScore(high);
    while (gameOn == true && doExit == false && doPaused == false){
        al_wait_for_event(event_queue, &ev);
        //al_get_next_event(event_queue, &ev);
        //Make backgrounds move
        moveBackgrounds(city, tree, ground);
        //Print the score and highscore to platform
        printScore(counter, high);
        //Print hearts to display
        printLives(lives, lifeNum);
        //Add character to the game
        character(doPaused, bunny);
        //Variables for timing the game
        counte++;

        //Log obstacles
        staticObstacle(log);
        if(isCollision(bunny, log) == true){
            printf("Collision with log! \n");
            counte = 0;
        }

        //Fog obstacles
        moveObstacle(fog);
        if(isCollision(bunny, fog) == true){
            printf("COLLISION with fog!\n");
            counte = 0;
        }

        //Garbage bag obstacles
        moveObstacle(bag);
        if(isCollision(bunny, bag) == true){
            printf("COLLISION with bag!\n");
            counte = 0;
        }
        isHit(warning, bunny, counte, lifeNum);
        al_flip_display();

        //Player loses when number of lives hits 0
        if(lifeNum <= 0){
            gameOn = false;
        }

        counter++;
    }
    /******************************** Pause the game *******************************/
    while(doPaused == true && gameOn == true && doExit == false){
        gamePaused(city, tree, ground);    //Use text file to store current positions of obstacles to continue game
        //exit game when ESC is pressed
        al_get_next_event(event_queue, &ev);

        printButton(button[2], 750, 400);
        al_draw_text(font, BUTTON, 760, 410, ALLEGRO_ALIGN_LEFT, "EXIT");

        if(buttonClicked(button[2]) == true || ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
            al_destroy_display(display);
            printf("EXITED successfully\n");
        }
        al_flip_display();
    }
    /********************************** Game Over **********************************/
    while(doPaused == false && doExit == false && gameOn == false){
        compareHighscore(counter, high, newBest);
        gameOver(city, tree, ground, counter, high, newBest);   //includes printing the final score
        al_flip_display();
        //exit game when ENTER is pressed
        al_get_next_event(event_queue, &ev);
        if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
                al_destroy_display(display);
                break;
        }
    }
    al_destroy_sample(loopSound);
    //Write the highscore to a text file
    storeHighscore(counter, high);

    return 0;
}
