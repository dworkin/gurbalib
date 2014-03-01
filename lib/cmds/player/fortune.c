inherit M_COMMAND;

#define FORTUNES_DIR "/data/fortunes/"

void usage() {
   string *lines;

   lines = ({ "Usage: fortune [fortunes|literature|riddles]",
		"", "leave parameter blank for default (fortunes)."
	});
   this_player()->more(lines);
}

string give_fortune(string file) {
	mixed  *parsed;
	string  grammar, str;
	if (empty_str(file)) {
		file = "fortunes";
	}
	if (!file_exists(FORTUNES_DIR + file)) {
		return "";
	}
	grammar = "whitespace = /[%]/ text = /[^%]*/ S: S: S text";
	str = "one\nand done.\n%two\n%three\n%";
	parsed = parse_string(grammar, read_file(FORTUNES_DIR + file));
	return parsed[random(sizeof(parsed)) - 1];
}

static void main(string str) {
   if (empty_str(str)) {
		str = "fortunes";
   }
	if (str == "-h") {
		usage();
		return;
	}
	write(give_fortune(str));
}
