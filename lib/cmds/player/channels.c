void usage() {
   string *lines;

   lines = ({ "Usage: channels [-h]" });
   lines += ({ "" });
   lines += ({ "List the available channels you can use to communicate on." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tchannels" });
   lines += ({ "See also:" });
   lines += ({ "\tchan" });

   this_player()->more(lines);
}

/* 
Display the chat channels a player is subscribed to
Arron Cusimano (mordain) 20090314
*/
void main(string str) {
   string *channels, *schannels;
   mapping ichans;
   string *lines;
   string line;
   int i, sz;

   if (str && str != "") {
      usage();
      return;
   }

   channels = CHANNEL_D->query_channels();
   schannels = this_player()->query_channels();

   lines = ( { "%^BOLD%^%^CYAN%^Available channels: %^RESET%^" } );
   for (i = 0, sz = sizeof(channels); i < sz; i++) {
      line = channels[i] + "     \t";	/* very suss formatting */
      line += (member_array(channels[i], schannels) == -1) ?
	 "%^RED%^OFF" : "%^GREEN%^ON";
      line += "%^RESET%^";
      lines += ( { line } );
   }

   if (query_wizard(this_player())) {
      ichans = IMUD_D->query_chanlist();
      channels = map_indices(ichans);

      lines += ( { } );
      lines += ( { "IMud channels" } );
      lines += ( { "--------------" } );
      for (i = 0; i < sizeof(channels); i++) {
	 if (ichans[channels[i]][0] && ichans[channels[i]][0] != -1)
	    lines += ( { channels[i] + ", " + ichans[channels[i]][0] } );
      }
   }

   this_player()->more(lines);
}
