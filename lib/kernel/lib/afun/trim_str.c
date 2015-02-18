string trim_str(string str) {
   string* parsed;

   argcheck(str, 1, "string");

   if (nilp(str) || str == "") {
      return "";
   }

   parsed = parse_string("whitespace = /[\n\b\r\t ]+/ " + 
      "word = /[^\n\b\r\t ]+/ S: word S: S word", str);
   parsed -= ({ "" });

   return implode(parsed, " ");
}
