#include "declarations.h"

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_EVENT ev;

void obstaclePosition(Obstacle &fog, Obstacle &log, Obstacle &bag){
    srand(time(0));

    fog.x = rand()%(1600 - 300) + 900;
    fog.y = rand()%(540 - 196) + 1;
    fog.dy = -3;   //direction of obstacle

    bag.x = rand()%(1400 - 100) + 900;
    bag.y = rand()%(540 - 100) + 1;
    bag.dy = 3;   //direction of obstacle
    //Initialize positions of the first log obstacle
    log.x = rand()%(1500 - 300) + 900;
    log.y = 540;
}
int moveObstacle(Obstacle &obstacle){
    srand(time(0));

    //draw obstacle to screen, repetitively
    al_draw_bitmap(obstacle.image, obstacle.x, obstacle.y, 0);

    //Move up and down the screen
    if(obstacle.y > 0 && obstacle.y < 540){
        obstacle.y += obstacle.dy;
    }
    else if(obstacle.y <= 0){
        obstacle.dy = 3;
        obstacle.y += obstacle.dy;
    }
    else if(obstacle.y >= 540){
        obstacle.dy = -3;
        obstacle.y += obstacle.dy;
    }

    //Move sideways towards character
    obstacle.x -= 2;
    if (obstacle.x <= -300){
        obstacle.x = rand()%(1600 - 300) + 1800;
    }
    return 0;
}

//for the log
int staticObstacle(Obstacle &obstacle){
    srand(time(0));
    al_draw_bitmap(obstacle.image, obstacle.x, obstacle.y, 0);
    obstacle.x -= 5;
    if(obstacle.x < -195){
        obstacle.x = rand()%900 + 1800;
    }
    return 0;
}
