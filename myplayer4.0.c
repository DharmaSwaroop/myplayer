//This is to add loop function.


#include<stdio.h>
#include<gst/gst.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
#include<string.h>
#include"myplayer4.0_lib.h"

pthread_t th1;									//Initializing the threads
pthread_t th2;

void *runPipeline(char *path2);

void *controller(struct player *myplayer)					//Takes care of the controlling part. This is th2
{
	char c;
		
	while(true)
	{
		//printf("the value of eos is: %d\n", myplayer->eos);
		printf("Enter the command you want to give: \n");
		printf("Enter 'p' to pause/play.\n");
		printf("Enter 'l' to enter loop mode.\n");
		printf("Enter 'n' to set new path.\n");
		printf("Enter 'e' to exit.\n");
		//printf("Enter 'e' to exit.\n");
		scanf(" %c",&c);									//Taking the input character
		
		switch(c)
		{
			case 'p':
				{									// For pausing 	
					printf("Inside p\n");
					playpause(myplayer);
					break;
				}
			case 'l':
				{									// For loop mode
					printf("Entered 'l'.\n");
					looping(myplayer);
					break;
				}
			case 'n':									// For new path setting
				{
					setting(myplayer);	
                        		pthread_cancel(th1);							//Terminating the initial thread before creating new one.
                                	pthread_create(&th1, NULL, runPipeline, myplayer->path); 		// Creating a thread again for playing the new video.
                                	pthread_exit(NULL); 							//Terminating this self loop
  					break;
				}
			case 'e':
				{
					gst_element_set_state(myplayer->pipeline, GST_STATE_NULL);
      					gst_object_unref(myplayer->pipeline);
      					pthread_cancel(th1);
      					pthread_exit(NULL);
      					break;
				}	
		   
		}
	}
	return NULL;
}


void *runPipeline(char *path2)							//This is th1
{
	//pthread_t th2;
	struct player *myplayer;						//Declaring player   
	myplayer = (struct player *)malloc(sizeof(struct player));		//Allocating memory
	
	myplayer->eos = 0;
	myplayer->loop = 0;							//Setting loop variable to zero
	strcpy(myplayer->path,path2);						//Copying the path
        sprintf(myplayer->desc, "playbin uri=file://%s", myplayer->path);
        printf("The description is: %s", myplayer->desc );
        do{
        
	myplayer->pipeline = gst_parse_launch(myplayer->desc, NULL); 		//Launched the pipeline
	gst_element_set_state(myplayer->pipeline, GST_STATE_PLAYING); 		//Set the pipleline to playing state
	pthread_create(&th2, NULL, controller, myplayer);			//Creating the controller pipeline

        myplayer->bus = gst_element_get_bus(myplayer->pipeline);		//Initalising bus 
        myplayer->msg = gst_bus_timed_pop_filtered(myplayer->bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);	//Initialising msg
        
            
        gst_message_unref(myplayer->msg);					//Freeing resources
  	gst_object_unref(myplayer->bus);
	gst_element_set_state(myplayer->pipeline, GST_STATE_NULL);
        gst_object_unref(myplayer->pipeline);  
        //myplayer->eos=1;
        printf("THE VALUE OF LOOP IS: %d\n", myplayer->loop);
        pthread_cancel(th2);							//Terminating the controller thread
        
        
        }while(myplayer->loop==1);							
        pthread_exit(NULL);
        //pthread_cancel(pthread_self());
   	//printf("still in after kill\n");
   	return NULL;
	
}

int main(int argc, char *argv[])
{
	
	gst_init(&argc, &argv);							//Initializing gstreamer
	char path2[100];							//To take the first path						
	printf("---------------------------------THE PLAYER HAS STARTED---------------------------------------\n");
	printf("Enter the pathof the file: ");
	scanf("%s",path2);
	//gboolean is_valid_uri = gst_uri_is_valid(path2);
	//if(is_valid_uri)
	//{
	pthread_create(&th1, NULL, runPipeline, path2);				// Creating the Controller thread
	//}
	//else
	//{
	//printf("Not a valid path.\n");
	//}
	pthread_exit(NULL);
	printf("HI I AM IN MAIN\n");
	return 0;
}
