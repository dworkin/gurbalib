void usage() {
   write("Usage: eat [-h] [OBJECT]\n");
   write("Consume the specified object.\n");
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

   obj = this_player()->present(lowercase(str));
   if (!obj) {
      write("Consume what?\n");
      return;
   }

   if (!obj->is_eatable()) {
      write(" You can not consume that.\n");
      return;
   }

   call_other(obj, "do_eat");
}
