inherit M_COMMAND;

#define DUMMY DOMAINS_DIR + "/required/objects/fake_emote.c"

string *keys;
int do_import;

void init_keys(void) {
   keys = ({ "" });
   keys += ({ "LIV" });
   keys += ({ "STR" });
   keys += ({ "OBJ" });
}

string *usage(void) {
   string *lines;

   lines = ({ "Usage: emotediff [-h] [-i] FILE [EMOTE]" });
   lines += ({ "" });
   lines += ({ "Compare the current loaded emotes vs FILE" });
   lines += ({ "If EMOTE is given, display EMOTE for both." });
   lines += ({ "This command uses the following tags to mark differences:" });
   lines += ({ "\t+\tNew line that doesn't exist in current emoted" });
   lines += ({ "\t-\tline that exists in emoted but not in FILE" });
   lines += ({ "\t!\tline that does not match current emoted" });
   lines += ({ "\t=\tline that matches current emoted" });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\t-i\tImport missing elements from FILE to the " +
      "current emotes." });
   lines += ({ "\t\t\tIf EMOTE is given only import that emote." });
   lines += ({ "Examples:" });
   lines += ({ "\temotediff /tmp/emote_d.o" });
   lines += ({ "\temotediff /tmp/emote_d.o smile" });
   lines += ({ "\temotediff -i /tmp/emote_d.o smile" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "alias");
   add_also("player", "cmds");
   add_also("player", "emote");
   add_also("player", "help");

   add_also("wiz", "aliasadm");
   add_also("wiz", "domain");

   add_also("admin", "cmdadm");
   add_also("admin", "coloradm");
   add_also("admin", "emoteadm");
   add_also("admin", "rehash");
}

void do_diff(object obj, string emote, string myfile) {
   string tag, value, value2;
   int x, max, removal_needed;

   max = sizeof(keys);

   write("EMOTE_D : " + emote + "\n");

   for (x = 0; x < max; x++) {
      value = EMOTE_D->query_emote(emote, keys[x]);
      if (!value) {
         value = " ";
      }
      write("   " + keys[x] + ": " + value + "\n");
   }

   write(myfile + " : " + emote + "\n");

   for (x = 0; x < max; x++) {
      removal_needed = 0;

      value = EMOTE_D->query_emote(emote, keys[x]);
      value2 = obj->query_emote(emote, keys[x]);
      if ((value == "") && (value2 != "")) {
         tag = "+ ";
         if (do_import) {
            EMOTE_D->add_emote(emote, keys[x], value);
         }
      } else if ((value != "") && (value2 == "")) {
         tag = "- ";
         if (do_import) {
            removal_needed = 1;
         }
      } else if (value != value2) {
         tag = "! ";
         if (do_import) {
            EMOTE_D->add_emote(emote, keys[x], value);
         }
      } else {
         tag = "= ";
      }
      if (removal_needed) {
         EMOTE_D->remove_emote(emote);

         if ((value == "") && (value2 != "")) {
            EMOTE_D->add_emote(emote, keys[x], value);
         } else if ((value != "") && (value2 == "")) {
            /* This was a - so do nothing */
         } else if (value != value2) {
            EMOTE_D->add_emote(emote, keys[x], value);
         } else {
            EMOTE_D->add_emote(emote, keys[x], value);
         }
      }

      if (!value2) {
         value2 = " ";
      }
      write(tag + " " + keys[x] + ": " + value2 + "\n");
   }
}

void do_fulldiff(object obj, string myfile) {
   mapping big;
   string *values, *value1, *value2;
   int x, max, y, maxy, removal_needed;
   string tag;

   values = EMOTE_D->query_emotes();
   max = sizeof(values);
   big = ([ ]);
   for (x = 0; x < max; x++) {
      big[values[x]] = 1;
   }

   values = obj->query_emotes();
   max = sizeof(values);
   for (x = 0; x < max; x++) {
      big[values[x]] = 1;
   }

   write("Fulldiff EMOTE_D, " + myfile + "\n");
   max = map_sizeof(big);
   values = map_indices(big);

   maxy = sizeof(keys);

   for (x = 0; x < max; x++) {
      removal_needed = 0;
      value1 = EMOTE_D->query_rules(values[x]);
      value2 = obj->query_rules(values[x]);

      if (value1 && !value2) {
         tag = "+  ";
         if (do_import) {
            for (y = 0; y< maxy; y++) {
               EMOTE_D->add_emote(values[x], keys[y], value1[y]);
            }
         }
      } else if (!value1 && value2) {
         tag = "-  ";
         if (do_import) {
            removal_needed = 1;
         }
      } else if (value1 != value2) {
         tag = "!  ";
         if (do_import) {
            for (y = 0; y< maxy; y++) {
               EMOTE_D->add_emote(values[x], keys[y], value1[y]);
            }
         }
      } else {
         tag = "=  ";
      }

      if (removal_needed) {
         EMOTE_D->remove_emote(values[x]);

         if ((value1) && (!value2)) {
            for (y = 0; y< maxy; y++) {
               EMOTE_D->add_emote(values[x], keys[y], value1[y]);
            }
         } else if (!value1 && value2) {
            /* This was a - so do nothing */
         } else if (value1 != value2) {
            for (y = 0; y< maxy; y++) {
               EMOTE_D->add_emote(values[x], keys[y], value1[y]);
            }
         } else {
            for (y = 0; y< maxy; y++) {
               EMOTE_D->add_emote(values[x], keys[y], value1[y]);
            }
         }
      }

      write(tag + values[x] + "\n");
   }
}

static void main(string str) {
   string myfile, *tmp;
   int i, max, x;
   object obj;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "-h%s", str)) {
      this_player()->more(usage());
      return;
   }

   tmp = explode(str, " ");
   max = sizeof(tmp);
   
   if (tmp[0] == "-i") {
      if (max < 2) {
         write("Error: You need to supply a filename.\n");
         return;
      } 
      x = 2;
      myfile = tmp[1];
      do_import = 1;
   } else {
      x = 1;
      myfile = tmp[0];
      do_import = 0;
   }
   if (!file_exists(tmp[x-1])) {
      write("No such file: " + tmp[x-1] + "\n");
      return;
   }
   obj = find_object(DUMMY);

   if (!obj) {
      obj = compile_object(DUMMY);
   }

   if (!obj) {
      write("Invalid file " + tmp[x-1] + "\n");
      return;
   }
   obj->set_file(myfile);
   obj->restore_me();
   init_keys();

   if (x >= max ) {
      do_fulldiff(obj, myfile);
   } else {
      for (i = x; i < max; i++) {
         do_diff(obj, tmp[i], myfile);
      }
   }
   destruct_object(obj);
}
