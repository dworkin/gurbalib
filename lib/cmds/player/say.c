void usage() {
   write("Usage: say [-h] MSG\n");
   write("Tell everyone in the current room MSG.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("Examples:\n");
   write("\tsay I'm sleepy, I should go now.\n");
   write("\tsay no your not!\n");
   if (query_wizard(this_player())) {
      write("See also: bug, emote, rsay, shout, ssay, tell, translate, " +
         "whisper, wizcall\n");
   } else {
      write("See also: bug, emote, rsay, shout, tell, whisper, wizcall\n");
   }
}

/* Ok so it isn't the best method in the world for making sure that you 
   get the correct conjugation, but it works.*/
void main(string str) {
   int i;
   string me;			/*what I, the one who's talking, sees */
   string you;			/*what all the others in the room sees */

   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   /* Strip trailing whitespaces */

   if (!this_environment()) {
      write("You have no environment, so there is no way to " +
	 "say things either.");
      return;
   }

   for (i = strlen(str) - 1; i > 0; i--) {
      if (str[i] != ' ')
	 break;
      str = str[0..(i - 1)];
   }

   me = " say: ";
   you = " says: ";		/*default values */

   if (str != "") {

      if ((str[strlen(str) - 1]) == '!') {
	 me = " say excitedly: ";
	 you = " says excitedly: ";
	 if ((str[strlen(str) - 2]) == '!') {
	    if ((str[strlen(str) - 3]) == '!') {
	       me = " shout: ";
	       you = " shouts: ";
	    } else {
	       me = " yell: ";
	       you = " yells: ";
	    }
	 }
      }

      if ((str[strlen(str) - 1]) == '.') {
	 if ((str[strlen(str) - 2]) == '.') {
	    if ((str[strlen(str) - 3]) == '.') {
	       me = " trail off: ";
	       you = " trails off: ";
	    }
	 }
      }

      switch (str[strlen(str) - 1]) {
	 case '?':
	    me = " ask: ";
	    you = " asks: ";
	    break;
	 case '@':
	    me = " exclaim proudly: ";
	    you = " exclaims proudly: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '#':
	    me = " boast: ";
	    you = " boasts: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '$':
	    me = " say sarcastically: ";
	    you = " says sarcastically: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '%':
	    me = " say thoughtfully: ";
	    you = " says thoughtfully: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '^':
	    me = " say admiringly: ";
	    you = " says admiringly: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '&':
	    me = " say mockingly: ";
	    you = " says mockingly: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '*':
	    me = " snap: ";
	    you = " snarls: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '/':
	    me = " say with a rising voice: ";
	    you = " says with a rising voice: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '+':
	    me = " say loudly: ";
	    you = " says loudly: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '-':
	    me = " whisper: ";
	    you = " whispers: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '=':
	    me = " correct: ";
	    you = " corrects: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '~':
	    me = " blurt out: ";
	    you = " blurts out: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case ';':
	    me = " say softly: ";
	    you = " says softly: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case ':':
	    me = " mumble: ";
	    you = " mumbles: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '|':
	    me = " reply with: ";
	    you = " replies with: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '>':
	    me = " point and say: ";
	    you = " points and says: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '\{':
	    me = " slobber out: ";
	    you = " slobbers out: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '\]':
	    me = " say jokingly: ";
	    you = " says with a light chuckle: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '\}':
	    me = " struggle to say: ";
	    you = " has to struggle to say: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '\\':
	    me = " say with a sinking voice: ";
	    you = " says with a sinking voice: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '`':
	    me = " comment: ";
	    you = " comments: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '\[':
	    me = " laugh and say: ";
	    you =
	       " laughs as " + this_player()->query_gender_pronoun() +
	       " says: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '<':
	    me = " point at yourself and say: ";
	    you =
	       " points at " + this_player()->query_gender_reflexive() +
	       " and says: ";
	    str = str[..strlen(str) - 2];
	    break;
	 case '_':
	    me = " say under your breath: ";
	    you =
	       " says under " + this_player()->query_gender_possessive() +
	       " breath: ";
	    str = str[..strlen(str) - 2];
	    break;
      }

      switch (str[strlen(str) - 1]) {
	 case '.':
	 case '?':
	 case '!':
	 case ',':
	    break;
	 default:
	    str += ".";
            break;
      }

      if (this_player()->query_Name()) {
	 this_environment()->tell_room(this_player(),
	    "%^GREEN%^" + capitalize(this_player()->query_Name()) + you +
	    "%^RESET%^" + capitalize(str) + "\n");
      } else {
	 this_environment()->tell_room(this_player(),
	    "%^GREEN%^" + "The " + this_player()->query_id() + you +
	    "%^RESET%^" + capitalize(str) + "\n");
      }
      this_player()->message("%^GREEN%^You" + me + "%^RESET%^" +
	 capitalize(str) + "\n", 1);
   } else {
      write("Say what?\n");
   }
}
