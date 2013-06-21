#define DUMMY DOMAINS_DIR + "/required/objects/fake_emote.c"

void usage() {
   string *lines;

   lines = ({ "Usage: emotediff [-h] [-i] FILE [EMOTE]" });
   lines += ({ "" });
   lines += ({ "Compare the current loaded emotes vs FILE" });
   lines += ({ "If EMOTE is given, display EMOTE for both." });
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
   lines += ({ "See also:" });
   lines += ({ "\temoteadm" });

   this_player()->more(lines);
}

/* XXX Need to add -i stuff  and get other stuff working */

void do_diff(object obj, string emote, string myfile) {
   string *rules1, *rules2;
   int x, max;

   rules1 = EMOTE_D->query_rules(emote);
   max = sizeof(rules1);

   write("EMOTE_D\n");
   for(x=0; x<max; x++) {
      write(" " + rules1[x] + ": " + EMOTE_D->query_emote(emote,rules1[x]) + 
         "\n");
   }

   rules2 = obj->query_rules(emote);
   max = sizeof(rules2);
   write(myfile + max +"\n");

   for(x=0; x<max; x++) {
      write(" " + rules2[x] + ": " + obj->query_emote(emote,rules2[x]) + "\n");
   }
}

void do_fulldiff(object obj, string myfile) {
   write("do_fulldiff" + myfile + "\n");
}

void main(string str) {
   string myfile, *tmp;
   int i,max, x;
   object obj;

   if (!require_priv("system")) {
      write("You must be an admin to do that.");
      return;
   }

   if (!str || (str == "")) {
      usage();
      return;
   }

   if (sscanf(str, "-h%s", str)) {
      usage();
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
   } else {
      x = 1;
      myfile = tmp[0];
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

   if (i > max ) {
      do_fulldiff(obj, myfile);
   } else {
      for(;i<max;i++) {
         do_diff(obj,tmp[i], myfile);
      }
   }
   destruct_object(obj);
}
