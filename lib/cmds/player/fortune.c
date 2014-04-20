inherit M_COMMAND;
inherit "/std/modules/m_fortune";

#define FORTUNES_DIR "/data/fortunes/"

void usage() {
   string *lines;

   lines = ({ "Usage: fortune [fortunes|literature|riddles|random]",
    "", "leave parameter blank for default (fortunes)."
   });
   this_player()->more(lines);
}

static void main(string str) {
    string f;
    f = str;
   if (empty_str(str)) {
      str = "random";
   }
   if (str == "-h") {
      usage();
      return;
   }
   str = give_fortune(str);
   if (nilp(str)) {
      write("fortune: no such fortune file as '" + f + "'.");
      usage();
      return;
   }
   write(str);
}

