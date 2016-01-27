inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: say [-h] MSG" });
   lines += ({ "" });
   lines += ({ "Tell everyone in the current room MSG." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tsay I'm sleepy, I should go now." });
   lines += ({ "\tsay no your not!" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "bug");
   add_also("player", "chan");
   add_also("player", "emote");
   add_also("player", "rsay");
   add_also("player", "shout");
   add_also("player", "tell");
   add_also("player", "whisper");
   add_also("player", "wizcall");

   add_also("wiz", "echo");
   add_also("wiz", "echoto");
   add_also("wiz", "ssay");
   add_also("wiz", "sysmsg");
   add_also("wiz", "translate");
   add_also("wiz", "wizlog");

   add_also("admin", "wall");
}

string *get_strtype(string me, string you, string str) {
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
      return ({me, you, str});
}

/* Ok so it isn't the best method in the world for making sure that you 
   get the correct conjugation, but it works.*/
static void main(string str) {
   int i;
   string me;         /*what I, the one who's talking, sees */
   string you;        /*what all the others in the room sees */

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }
   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   /* Strip trailing whitespaces */

   if (!this_environment()) {
      write("You have no environment, so there is no way to " +
         "say things either.");
      return;
   }

   for (i = strlen(str) - 1; i > 0; i--) {
      if (str[i] != ' ') {
         break;
      }
      str = str[0..(i - 1)];
   }

   /*default values */
   me = " say: ";
   you = " says: ";

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

      ({me, you, str}) = get_strtype(me, you, str);

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
