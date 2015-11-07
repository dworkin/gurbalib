/*
 * Module for data to string serialization and string to data deserialization
 *
 * 
 * string serialize( string format, mixed data )
 *
 *   Returns a string with data serialized in the requested format.
 *
 *
 * mixed deserialize( string format, string str )
 *
 *   Returns the deserialized data contained in str according to the
 *   requested format.
 *
 *
 * For each format there must be a parser/generator object located in
 * /daemons/serialize, this object must be loaded also, this module
 * will not attempt to compile and load it if it isn't already.
 *
 * By Aidil @ Way of the Force
 *
 * This code is in the public domain.
 *
 */

#ifndef PARSER_DIR
#define PARSER_DIR "/daemons/serialize/"
#endif

static mapping formats;

private int new_format(string format) {
   object ob;

   if (!formats) {
      formats = ([]);
   }

   console_msg("Trying to add parser " + PARSER_DIR + format + "\n");
   if (ob = find_object(PARSER_DIR + format)) {
      formats[format] = ob;
      return 1;
   } else {
      return 0;
   }
}

private void test_format(string format) {
   if (!formats || !formats[format]) {
      if (!new_format(format)) {
         error("Unknown format: " + format);
      }
   }
}

static string serialize(string format, mixed value) {
   format = lowercase(format);
   test_format(format);
   return formats[format]->save_value(value);
}

static mixed deserialize(string format, string data) {
   format = lowercase(format);
   test_format(format);
   return formats[format]->restore_value(data);
}
