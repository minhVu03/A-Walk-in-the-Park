
#include "declarations.h"

const float FPS = 60;			// set frame rate   (60 would be more normal)
const int SCREEN_W = 1800;      // screen width
const int SCREEN_H = 900;       // screen height

#define BACKGROUND al_map_rgb(255, 0, 255)
#define INST al_map_rgb(60, 180, 75)

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
    al_init_image_addon(); //put images into program
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon
    al_install_audio();
    al_init_acodec_addon();

    //initialize display
    display = al_create_display(SCREEN_W, SCREEN_H);
    // add event queue object
    event_queue = al_create_event_queue();
    // add timer object
	timer = al_create_timer(1.0/ FPS);

    //Check allegro settings
    allegroSettings();

    //Register event queues
    al_register_event_source(event_queue, al_get_display_event_source(display));
 	al_register_event_source(event_queue, al_get_keyboard_event_source());
 	al_register_event_source(event_queue, al_get_timer_event_source(timer));
 	al_register_event_source(event_queue, al_get_mouse_event_source());


    /********************* Declare and initialize variables ******************************/
    ALLEGRO_SAMPLE *startSound = nullptr;
    ALLEGRO_SAMPLE *endSound = nullptr;
    ALLEGRO_SAMPLE *loopSound = nullptr;
    ALLEGRO_SAMPLE *hitSound = nullptr;
    ALLEGRO_SAMPLE *clickSound = nullptr;

    //Obstacles
    Obstacle fog, bag[3], log;

    //score
    int counter = 0;
    int high = 0;

    //Backgrounds and character
    Backgrounds city, tree, ground;
    Keys arrows, letters;

    Button button[4];
    for (int i = 0; i < 4; i++){
        button[i].clicked = false;
    }
    Character bunny;
    bunny.x = 100;
    bunny.y = 540;

    Life lives[3];
    Danger warning;
    int lifeNum = 3;
    int counte = 6;

    bool gameOn = true;
    bool newBest = false;
    int gamePhase = 1;

    //Load and check
    loopSound = al_load_sample("gameLoop.wav");
    startSound = al_load_sample("gameStart.wav");
    endSound = al_load_sample("gameDie.wav");
    hitSound = al_load_sample("gameHit.wav");
    clickSound = al_load_sample("gameClick.wav");

    initializeSounds(startSound, endSound, loopSound, hitSound, clickSound);

    loadBackgrounds(city, tree, ground);
    loadText();
    imageSettings(bunny, fog, log, bag, arrows, letters, warning);
    loadButtons(button);
    initializeLives(lives);

    //Start the timer
 	al_start_timer(timer);

 	// Loop game sound
 	al_play_sample(loopSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

 	/********************************* Run game code ***********************************************/

    while (gameOn == true){
        switch (gamePhase){

            /******************************* Start menu ************************************/
            case 1:
                //al_wait_for_event(event_queue, &ev);
                startGame(city, tree, ground);
                printButton(button[0], 600, 280);
                printButton(button[1], 900, 280);
                al_flip_display();
                //Determine positions for obstacles
                obstaclePosition(fog, log, bag);
                //Start game
                if(buttonClicked(button[0]) == true || ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
                    al_play_sample(startSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
                    gamePhase = 2;
                }
                //Exit game
                if(buttonClicked(button[1]) == true){
                    al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    al_destroy_display(display);
                    al_destroy_sample(loopSound);
                    printf("Exited successfully\n");
                }
                highScore(high);
                break;
            /******************************* Run the game **********************************/
            //highScore(high);
            case 2:
                al_wait_for_event(event_queue, &ev);
                //al_get_next_event(event_queue, &ev);
                //Make backgrounds move
                moveBackgrounds(city, tree, ground);

                //Print instructions in the beginning of the game
                if(counter <= 300){
                    gameInstruction(arrows, 520, 30);
                    al_draw_text(normalText, INST, 890, 72, ALLEGRO_ALIGN_CENTRE, "or ");
                    gameInstruction(letters, 940, 30);
                }

                //Add character to the game
                character(bunny);

                //Variables for timing the game
                counte++;

                //Log obstacles
                staticObstacle(log);
                if(isCollision(bunny, log) == true){
                    counte = 0;
                }

                //Fog obstacles
                moveObstacle(fog);
                if(isCollision(bunny, fog) == true){
                    counte = 0;
                }

                //Garbage bag obstacles
                moveObstacle(bag[0]);
                if (counter > 2000){
                    moveObstacle(bag[1]);
                }
                if (counter > 4000){
                    moveObstacle(bag[2]);
                }
                if(isCollision(bunny, bag[0]) == true || isCollision(bunny, bag[1]) == true || isCollision(bunny, bag[2]) == true){
                    counte = 0;
                }

                //Print the score and highscore to platform
                printScore(counter, high);
                //Print hearts to display
                printLives(lives, lifeNum);
                //Display pause button
                printButton(button[2], 1650, 785);

                isHit(warning, bunny, counte, lifeNum, hitSound);
                al_flip_display();

                //Player loses when number of lives hits 0
                if(lifeNum <= 0){
                    al_play_sample(endSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    gamePhase = 4;
                }

                //Score
                counter++;

                if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE || buttonClicked(button[2]) == true){
                    al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    gamePhase = 3;
                }
                break;
            /******************************** Pause the game *********************************/
            case 3:
                gamePaused(city, tree, ground);
                al_get_next_event(event_queue, &ev);
                printButton(button[3], 480, 280);
                printButton(button[0], 780, 280);
                printButton(button[1], 1080, 280);

                //Replay
                if(buttonClicked(button[3]) == true){
                    al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    lifeNum = 3;
                    counter = 0;
                    bunny.x = 100;
                    bunny.y = 540;
                    gamePhase = 1;
                }
                //Continue
                if(buttonClicked(button[0]) == true){
                    al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    gamePhase = 2;
                }
                //Exit game
                if(buttonClicked(button[1]) == true || ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
                    al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    storeHighscore(counter, high);
                    al_destroy_display(display);
                    al_destroy_sample(loopSound);
                    printf("Exited successfully\n");
                }
                al_flip_display();
                break;
            /********************************** Game Over **********************************/
            case 4:
                //Determine high score
                compareHighscore(counter, high, newBest);
                gameOver(city, tree, ground);   //includes printing the final score
                //Print the scores to display
                printFinalScore(counter, high, newBest);

                printButton(button[3], 650, 280);
                printButton(button[1], 950, 280);

                al_flip_display();

                al_get_next_event(event_queue, &ev);
                //Replay
                if(buttonClicked(button[3]) == true){
                    al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    lifeNum = 3;
                    counter = 0;
                    bunny.x = 100;
                    bunny.y = 540;
                    gamePhase = 1;
                }
                //Exit game
                if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE || buttonClicked(button[1]) == true){
                        al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        storeHighscore(counter, high);
                        al_destroy_display(display);
                        al_destroy_sample(loopSound);
                        printf("Exited successfully\n");
                }
                break;
        } //end of switch statement
    }
    return 0;
}
