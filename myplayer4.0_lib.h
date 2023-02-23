struct player{
	GstElement *pipeline;
	GstBus *bus;
	GstMessage *msg;
	char path[100];
        char desc[1000];
        int eos;
        int loop;
};

void playpause(struct player *myplayer);
void looping(struct player *myplayer);
void setting(struct player *myplayer);
