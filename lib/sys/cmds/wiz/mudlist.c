inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: mudlist [-h] [MUD]" });
   lines += ({ " " });
   lines += ({ "Display a list of muds connected via intermud." });
   lines += ({ "If you give a mudname it will only display that mud's info." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tmudlist" });
   lines += ({ "\tmudlist gurbalib" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "look");
   add_also("player", "who");

   add_also("wiz", "last");
   add_also("wiz", "locate");
   add_also("wiz", "possess");
   add_also("wiz", "rwho");
   add_also("wiz", "snoop");
   add_also("wiz", "where");
}

/* vim:set ft=lpc: */
static void main(string str) {
   mapping mudlist;
   string tmp, line, *muds, *lines;
   int len, slen, mlen, i, sz, count;

   if (!alsos) {
      setup_alsos();
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   mudlist = IMUD_D->query_mudlist();

   if (!mudlist) {
      write("Empty mudlist. Wait a few minutes and try again.\n");
      return;
   }

   muds = map_indices(mudlist);

   lines = ({ "Up Mud                Address         Port  Lib" +
      "            Status             " });
   lines += ({ "-----------------------------------------------" +
      "------------------------------" });

   count = 0;
   sz = sizeof(muds);
   for (i = 0; i < sz; i++) {

      line = "";

      if (mudlist[muds[i]][0] != -1) {
         continue;
      }

      if (sizeof(mudlist[muds[i]]) < 9) {
         continue;
      }

      if (str && (strlen(str) > 0)) {
         slen = strlen(str) - 1;
         mlen = strlen(muds[i]) - 1;

         if (slen < mlen) {
            len = slen;
         } else {
            len = mlen;
         }

         if (("" + mudlist[muds[i]][1] != str)
            && ("" + uppercase(muds[i][..len]) != uppercase(str[..len]))) {
            continue;
         }
      }
      count++;

      tmp = "U   ";
      line += tmp[..2];

      tmp = muds[i] + "                   ";
      line += tmp[..17] + " ";

      tmp = mudlist[muds[i]][1] + "                ";
      line += tmp[..15];

      tmp = "" + mudlist[muds[i]][2] + "      ";
      line += tmp[..4] + " ";

      tmp = mudlist[muds[i]][5] + "              ";
      line += tmp[..13] + " ";

      tmp = mudlist[muds[i]][9] + "                      ";
      line += tmp[..19];

      lines += ({ line });
   }

   lines = ({ "" + count + " of " + sizeof(muds) + " muds listed.\n" }) + 
      lines;

   this_player()->more(lines);
}
