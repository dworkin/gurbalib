inherit M_COMMAND;
void usage() {
   string *lines;

   lines = ({ "Usage: edit [-h] [FILENAME]" });
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
   lines += ({ "See also:" });
   lines += ({ "\tbrowse, cat, cd, cp, diff, indent, ls, more, mkdir, pwd, " +
      "rm, tail" });

   this_player()->more(lines);
}

static void main(string str) {

   if (!str || (str == "")) {
      /* Not starting with a file */
      this_player()->edit("");
      this_player()->edit("file");
   } else if (sscanf(str, "-%s", str)) {
      usage();
      return;
   } else {
      this_player()->write("Starting editor...");
      this_player()->edit("e " + str);
      this_player()->edit("file");
   }
}
