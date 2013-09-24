inherit M_COMMAND;

void usage() {
   write("Usage: call [-h] FUNCTION [ARGS]\n");
   write("call the function FUNCTION with arguments ARGS in this object.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

static void main(string arg) {
   string *tmp;
   int i;

   if (!arg || arg == "") {
      usage();
      return;
   }
   if (sscanf(arg, "-%s", arg)) {
      usage();
      return;
   }

   tmp = explode(arg, " ");
   call_other(this_player(), tmp...);
}
