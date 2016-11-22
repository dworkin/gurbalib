inherit M_COMMAND;
inherit M_GETOPT;

#define REMOVE_OPTION "remove"

string *usage(void) {
   string *lines;

   lines = ({ "Usage: history [-h|-r [range]]" });
   lines += ({ "" });
   lines += ({ "The last twenty successful commands are saved.  You can " +
      "repeat any command " });
   lines += ({ "in your history.  You may also remove commands from your " +
      "history." });
   lines += ({ "You can use the following shortcuts to repeate commands:" });
   lines += ({ "!\tDisplay saved history." });
   lines += ({ "!!\tRepeat the last command in your history." });
   lines += ({ "!drink\tRepeat the last command in your history starting " +
       "with \"drink\"" });
   lines += ({ "" });
   lines += ({ "If you want to remove commands from your saved history you " +
      "can use the -r " });
   lines += ({ "option.  The -r option also works with ranges." });
   lines += ({ "To remove the third command use: history -r 3" });
   lines += ({ "" });
   lines += ({ "If no arguments are given you will get a display of your " +
      "history." });
   
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\t-r\tRemove, removes a range of history." });
   lines += ({ "" });
   lines += ({ "Examples:" });
   lines += ({ "\thistory" });
   lines += ({ "\thistory -h" });
   lines += ({ "\thistory -r 1-3,5,7-10" });
   lines += ({ "\t!!" });
   lines += ({ "\t!" });

   return lines;
}

static void main(string str) {
   string opt;
   int *range, i, dim;

   if (empty_str(str)) {
	write(this_player()->list_history());
	return;
   } else if (sscanf(str, "-r %s", opt)) {
         range = parse_range(opt);
         dim = sizeof(range);
         for (i = 0; i < dim; i++) {
            this_player()->remove_history(range[i]);
         }
         this_player()->compress_history();
         write(this_player()->list_history());
      return;
   }

   this_player()->more(usage());
}

