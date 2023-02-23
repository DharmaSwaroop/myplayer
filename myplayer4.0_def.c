#include<stdio.h>
#include<gst/gst.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
#include<string.h>
#include"myplayer4.0_lib.h"



void playpause(struct player *myplayer)
{
	GstState state;
	gst_element_get_state(myplayer->pipeline, &state, NULL, GST_CLOCK_TIME_NONE);
	printf("The current state is: %s\n", gst_element_state_get_name(state));
	if(state == GST_STATE_PLAYING)
	{
		printf("Inside p inside if\n");
		gst_element_set_state(myplayer->pipeline, GST_STATE_PAUSED);
	}
	else if(state == GST_STATE_PAUSED)
	{
		gst_element_set_state(myplayer->pipeline, GST_STATE_PLAYING);
	}
	
	
		
}

void looping(struct player *myplayer)
{
	if(myplayer->loop == 1)
	{
		myplayer->loop = 0;
	}
	else if(myplayer->loop == 0)
	{
		printf("Changing the value of loop to 1.\n");		// TO TEST THE VALUE OF LOOP
		myplayer->loop = 1;
	}
	
	
}

void setting(struct player *myplayer)
{
	printf("Enter the path of the file: ");
	scanf(" %s", myplayer->path);
 	gst_element_set_state(myplayer->pipeline, GST_STATE_NULL);
      	gst_object_unref(myplayer->pipeline);
      	
      	
}
