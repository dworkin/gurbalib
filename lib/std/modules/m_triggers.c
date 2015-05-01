static mapping patterns;

void respond(string message);

void add_pattern(string pattern, string action) {

   if (!patterns) {
      patterns = ([]);
   }
   patterns[pattern] = action;
}

void outside_message(string msg) {
   string *pats;
   string left, right;
   int i, j, args, patssize, patsz;

   left = "";
   right = "";

   if (msg[strlen(msg) - 1] == '\n') {
      msg = msg[..strlen(msg) - 2];
   }

   msg = ANSI_D->strip_colors(msg);

   if (!patterns) {
      patterns = ([]);
   }

   pats = map_indices(patterns);
   patssize = sizeof(pats);
   for (i = 0; i < patssize; i++) {
      args = 0;
      patsz = strlen(pats[i]);
      for (j = 0; j < patsz; j++) {
         if (pats[i][j] == '%') {
            args++;
         }
      }
      if (args == 0) {
         if (strstr(msg, pats[i]) != -1) {
            respond(patterns[pats[i]]);
            return;
         }
      } else if (sscanf(msg, pats[i], left, right) == args) {
         /* We found a match */
         msg = patterns[pats[i]];
         msg = replace_string(msg, "$1", left);
         msg = replace_string(msg, "$2", right);
         respond(msg);
         return;
      }
   }
}
