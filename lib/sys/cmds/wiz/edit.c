inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: edit [-h] [-here] [FILENAME]" });
   lines += ({ " " });
   lines += ({ "Start up the ed editor and edit a file." });
   lines += ({ "Ed is a line editor, you can only work with one line at a " +
      "time." });
   lines += ({ "It has two modes command mode and insert mode." });
   lines += ({ "You start in command mode, to enter insert mode you can use " +
      "a or i." });
   lines += ({ "To exit insert mode create a line with just a '.' in it " +
      "and hit return." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\t-here\tHere, edit the room you are in." });
   lines += ({ "Useful commands:" });
   lines += ({ "\tp\tprint line." });
   lines += ({ "\td\tdelete line." });
   lines += ({ "\tr FILE\tread a file named FILE." });
   lines += ({ "\tw FILE\twrite a file name FILE." });
   lines += ({ "\tq\tquit." });
   lines += ({ "\tQ\tquit, discarding any unsaved work." });
   lines += ({ "\te FILE\tedit a file named FILE." });
   lines += ({ "\t+5\tJump ahead 5 lines.  (you can use other numbers." });
   lines += ({ "\t-5\tJump back 5 lines.  (you can use other numbers." });
   lines += ({ "Examples:" });
   lines += ({ "\tedit workroom.c" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "browse");
   add_also("wiz", "cat");
   add_also("wiz", "cd");
   add_also("wiz", "cp");
   add_also("wiz", "diff");
   add_also("wiz", "indent");
   add_also("wiz", "ls");
   add_also("wiz", "more");
   add_also("wiz", "mkdir");
   add_also("wiz", "pwd");
   add_also("wiz", "rm");
   add_also("wiz", "tail");
}

static void main(string str) {
   if (!alsos) {
      setup_alsos();
   }

   if(str=="-here") {
      str = this_player()->query_environment()->file_name();
   }

   if (empty_str(str)) {
      /* Not starting with a file */
      this_player()->edit("");
      this_player()->edit("file");
   } else if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   } else {
      str = normalize_path(str, this_player()->query_env("cwd"));

      /* not needed for security, but allows giving nicer
         messages to the user. */
      if (!valid_read(str)) {
         this_player()->write("Permission denied.\n");
         return;
      }

      this_player()->write("Starting editor...");

      /* not needed for security, but warn user that they won't be able
         to write the file. */
      if (!valid_write(str)) {
         this_player()->write("WARNING: read-only file.\n");
      }

      this_player()->edit("e " + str);
      this_player()->edit("set window=" + this_player()->query_height() );
      this_player()->edit("1");
   }
}
