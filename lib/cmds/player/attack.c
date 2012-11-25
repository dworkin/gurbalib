void usage() {
   write("Usage: attack [-h] [OBJECT]\n");
   write("OBJ offends you, you are going to destroy it.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

void main(string str) {
   object obj;

   if (!str && str != "") {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   obj = this_player()->query_environment()->present(lowercase(str));
   if (!obj) {
      write("Attack what?\n");
      return;
   }

   if (!obj->is_living()) {
      write(" You can not attack that.\n");
      return;
   }

   this_player()->targetted_action("$N $vattack $t.", obj);
   this_player()->attack(obj);
}
