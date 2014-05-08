inherit M_COMMAND;

void usage() {
   string *lines;
   lines = ({ "Usage: killedby [-h]" });
   lines += ({ "" });
   lines += ({ "Summarise your deaths.." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tkilledby" });
   this_player()->more(lines);
}

static void main(string str) {
	this_player()->more(this_player()->summarise_killers());
}

