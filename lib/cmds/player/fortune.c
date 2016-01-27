inherit M_COMMAND;

#define FORTUNES_DIR "/data/fortunes/"

string *get_fortune_files(void);

string *usage(void) {
   string *lines, *filetypes;
   int i, imax;
   
   filetypes = get_fortune_files();
   imax = sizeof(filetypes);

   lines = ({ "Usage: fortune [TYPE]" });
   lines += ({ "" });
   lines += ({ "If no TYPE is given choose a random fortune." });
   lines += ({ "Otherwise choose a random fortune of that type." });
   lines += ({ "Current types are: " });

   for (i = 0; i < imax; i++) {
      lines += ({ "   " + filetypes[i] }); 
   }

   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "" });
   lines += ({ "Examples:" });
   lines += ({ "\tfortune" });
   lines += ({ "\tfortune samples" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "motd");
}

string *get_fortune_files(void) {
   string *names;

   names = get_dir(FORTUNES_DIR + "*")[0];

   return names;
}

string give_fortune(string file) {
   mixed *parsed;
   string grammar, *fortunefiles;
   int x;

   fortunefiles = get_fortune_files();
   if (empty_str(file)) {
      x = random(sizeof(fortunefiles));
      file = fortunefiles[x];
   }

   if (!file_exists(FORTUNES_DIR + file)) {
      return nil;
   }
   parsed = parse_string("whitespace = /[%]/ text = /[^%]*/ " +
      "S: S: S text", read_file(FORTUNES_DIR + file));

   return parsed[random(sizeof(parsed))];
}

int valid_fortune(string str) {
   switch (str) {
      case "fortunes":
      case "literature":
      case "riddles":
      case "random":
         return 1;
         break;
      default:
         break;
   }
   return 0;
}

static void main(string str) {
   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
   } else if (str == "-h" || !valid_fortune(str)) {
      this_player()->more(usage());
      return;
   }

   str = give_fortune(str);

   if (nilp(str)) {
      write("fortune: game over, please try again.");
      return;
   }

   write(str);
}

