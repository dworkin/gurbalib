inherit M_COMMAND;
inherit M_GETOPT;

#define REMOVE_OPTION "remove"

string *usage(void) {
   string *lines;

   lines = ({ "Usage: history <-h|-r <range>>" });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\t-r\tRemove, removes a range of history." });
   lines += ({ "" });
   lines += ({ "Examples:" });
   lines += ({ "\thistory -h" });
   lines += ({ "\thistory -r 1-3,5,7-10" });
   lines += get_alsos();

   return lines;
}

void setup_alsos() {
}

static void main(string str) {
   string opt;
   int *range, i, dim;

   if (!alsos) {
      setup_alsos();
   }

   if (!empty_str(str) && sscanf(str, "-r %s", opt)) {
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

