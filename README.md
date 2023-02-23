# myplayer
Implemented a CLI Gstreamer player

The files included are:
myplayer4.0.c
myplayer4.0_lib.h
myplayer4.0_def.c

DESCRIPTION OF THE FILES:

1) myplayer4.0.c
   This C file contains the main implementation of the pipline. It has two threads in it other than the main thread. One thread is used to run the pipeline and the other thread namely "controller" will take care of the controls or the input given by the user.
   The features included in this player are:
   * PLAYING THE GIVEN VIDEO FILE
   * PLAY/PAUSE
   * SET UP NEW PATH TO THE VIDEO FILE
   * LOOP MODE
 
2) myplayer4.0_lib.h
   This file contains structure definition that is being used and all the declarations of the functions that are created.
   The functions that are included are:
   * pauseplay
   * setting
   * looping
    
3) myplayer4.0_def.c
   This file contains all the defininitions of the functions that are being created and used.
   
   
STEPS TO EXECUTE:

1) Have the three files in the same directory.
2) Execute the following command in the terminal.
     gcc myplayer4.0.c -o myplayer4.0 myplayer4.0_def.c `pkg-config --cflags --libs gstreamer-1.0 gtk+-3.0`
3) Then to run the player execute the following command.
     ./myplayer4.0.c
4) This will start the player.
5) The command line interface will be shown for further.

