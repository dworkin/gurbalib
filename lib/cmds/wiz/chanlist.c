void usage() {
  write("Usage: chanlist [-h]\n");
  write("List the available channels you can use to communicate on.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

XXX why is there this and channels????

void main( string str){
   string *channels;
   mapping ichans;
   string *lines;
   string line;
   int i;

   if (str && str != "") {
     usage();
     return;
   }

   channels = CHANNEL_D->query_channels();

   lines = ({ });
   lines += ({"Local channels"});
   lines += ({"--------------"});

   for( i=0; i < sizeof( channels ); i++ ) {
      lines += ({ channels[i] });
   }

   ichans = IMUD_D->query_chanlist();
   channels = map_indices(ichans);

   lines += ({""});
   lines += ({""});
   lines += ({"IMud channels"});
   lines += ({"--------------"});

   for( i=0; i < sizeof( channels ); i++ ) {
      if( ichans[channels[i]][0] && ichans[channels[i]][0] != -1 )
	 lines += ({ channels[i] + ", " + ichans[channels[i]][0] });
   }

   this_player()->more( lines );
}
