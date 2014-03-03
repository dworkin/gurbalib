#define FORTUNES_DIR "/data/fortunes/"

string give_fortune(string file) {
   mixed  *parsed;
   string  grammar;
   if (empty_str(file)) {
      file = "random";
   }
   if (file == "random") {
      file = ({ "fortunes", "literature", "riddles" })[random(3)];
   }
   if (!file_exists(FORTUNES_DIR + file)) {
      return nil;
   }
   parsed = parse_string("whitespace = /[%]/ text = /[^%]*/ " +
    "S: S: S text", read_file(FORTUNES_DIR + file));
   return parsed[random(sizeof(parsed))];
}

