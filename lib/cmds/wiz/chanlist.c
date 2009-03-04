void main( string str){
   string *channels;
   mapping ichans;
   string *lines;
   string line;
   int i;

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
