#include "node.h"
#include "player.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



struct Node* playSong(struct Node* item){
    system("echo \'{ \"command\": [\"quit\"] }\' | socat - /tmp/mpvsocket");
    char aux_command[256];
    char command[256];

    strcpy(command, "mpv ");
    strcat(command, item->title);
    strcat(command, ".mp3");

    /*
    mpv can be controlled by external programs using the JSON-based IPC protocol. 
    It can be enabled by specifying the path
    to a unix socket or a named pipe using the option --input-ipc-server. 
    Clients can connect to this socket and send commands to the player or receive events from it.
    */
    strcpy(aux_command, " --no-audio-display --no-resume-playback --no-terminal --input-ipc-server=/tmp/mpvsocket &");
    strcat(command, aux_command);
    system(command);

    system("clear");
    printf("\nTocando \U0001F3B5 %s \U0001F3B5", item->title);

    return item;

}

void stop (){

    system("echo \'{ \"command\" : [\"set_property\", \"pause\", true] }\' | socat - /tmp/mpvsocket");
    system("clear");
}

void continueSong(){
    system("echo \'{ \"command\" : [\"set_property\", \"pause\", false] }\' | socat - /tmp/mpvsocket");
    system("clear");
}
