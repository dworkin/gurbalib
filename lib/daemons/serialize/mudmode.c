/*
 *
 * Emulates the MudOS save_variable and restore_variable efunctions.
 *
 * 8 January 1997       Begun           Greg Lewis
 *      # Wrote and tested initial version.  restore_variable needs to do
 *        error checking though (i.e., it works if the string it gets is
 *        right, but crashes and burns otherwise ;).
 *
 * 10 January 1997      Version 1.0     Greg Lewis
 *      # Added error checking to restore_variable, it returns RESTORE_ERROR
 *        (#define'd in save_restore.h) upon errors in the restore process.
 *      # Everything seems to test ok, not that I've been all that thorough.
 *
 * TBD
 *      # Prolly needs some more commenting (doesn't most code?)
 *
 * February 2009        Version 2.0     Bart van Leeuwen
 *      # Rewritten restore_variable()
 *      # Fix implode/explode related bugs in save_variable()
 *
 * August 2013          Version 2.1     Bart van Leeuwen
 *      # New grammar for restore_variable
 */

#include        <type.h>

#define GRAMMAR \
  "whitespace = /[ ]*/\n" + \
  "string = /\"([^\\\\\"\n]*(\\\\.)*)*\"/\n" + \
  "int = /-?[0-9]*/" + \
  "float = /-?[0-9]*\\.[0-9]+/\n" + \
  "float = /-?[0-9]+\\.[0-9]*([eE][-+]?[0-9]+)/\n" + \
  "float = /-?[0-9]*\\.[0-9]+([eE][-+]?[0-9]+)/\n" + \
  "result: data\n" + \
  "data: \n" + \
  "data: var\n" + \
  "var: string ? cnvstring\n" + \
  "var: map\n ? mkmap\n" + \
  "var: array ? mkarray\n" + \
  "var: int ? cnvint\n" + \
  "var: float ? cnvfloat\n" + \
  "map: '(' '[' opt_melements ']' ')'\n" + \
  "array: '(' '{' opt_aelements '}' ')'\n" + \
  "melement: var ':' var\n" + \
  "opt_melements: \n" + \
  "opt_melements: melements\n" + \
  "opt_melements: melements ','\n" + \
  "melements: melement\n" + \
  "melements: melements ',' melement\n" + \
  "opt_aelements: \n" + \
  "opt_aelements: aelements\n" + \
  "opt_aelements: aelements ','\n" + \
  "aelements: var\n" + \
  "aelements: aelements ',' var\n"

/*
 * Conversion functions used by the above grammar
 */

/* convert int litteral into an int */
static int * cnvint(mixed * data) {
   int r;

   sscanf(data[0], "%d", r);
   return ({ r });
}

/* convert float litteral into a float */
static float * cnvfloat(mixed * data) {
   float r;

   sscanf(data[0], "%f", r);
   return ({ r });
}

/* Convert string encoded object reference into an object */
static object * cnvobj(mixed * data) {
   string n;
   int i;

   n = "";
   for (i = 0; i < sizeof(data[0]); i++) {
      n += data[0][i];
   }
   return ({ find_object(n) });
}

/* Convert string litteral into a string */
static string * cnvstring(mixed * data) {
   string r;

   r = data[0];

   r = implode(explode(r, "\\\""), "\"");
   r = implode(explode(r, "\\\\"), "\\");

   return ({ r[1..strlen(r)-2] });
}

/* Convert array litteral into an array */
static mixed * mkarray(mixed * data) {
   int i;
   mixed *stuff;

   stuff = ({ });
   for (i = 2; i < sizeof(data) - 2; i += 2) {
      stuff += ({ data[i] });
   }
   return ({ stuff });
}

/* Convert mapping litteral into a mapping */
static mixed * mkmap(mixed * data) {
   int i;
   mapping stuff;
   mixed key, val;

   stuff = ([ ]);
   for (i = 2; i < sizeof(data) - 1 && ((data[i] + data[i + 1]) != "])");
      i += 4) {
      key = data[i];
      val = data[i + 2];
      stuff[key] = val;
   }
   return ({ stuff });
}

mixed restore_value(string str) {
   mixed * result;

   result = parse_string(GRAMMAR, str);

   if ( !result || sizeof(result) < 1 ) {
      return nil;
   } else {
      return result[0];
   }
}

string save_value(mixed var) {
   string result;
   int i, s;
   mixed *keys, *values;
   string pref, post;

   if (!var) {
      return "0";
   }
   switch (typeof(var)) {
      case T_INT : case T_FLOAT :
         result = "" + var;
         break;
      case T_STRING :
         if (strlen(var) > 0) {
            if (var[0..0] == "\\") {
               pref = "\\\\";
            } else if (var[0..0] == "\"") {
               pref = "\\\"";
            } else {
               pref = "";
            }

            if (var[strlen(var)-1] == '\\') {
               post = "\\\\";
            } else if (var[strlen(var)-1] == '\"') {
               post = "\\\"";
            } else {
               post = "";
            }

            result = implode(explode(var, "\\"), "\\\\");
            result = implode(explode(result, "\""), "\\\"");
            result = "\"" + pref + result + post + "\"";
         } else {
            result = "\"\"";
         }
         break;
      case T_OBJECT :
         result = object_name(var);
         break;
      case T_ARRAY :
         result = "({";
         for (i = 0, s = sizeof(var); i < s; i++) {
            result += save_value(var[i]) + ",";
         }
         result += "})";
         break;
      case T_MAPPING :
         keys = map_indices(var);
         values = map_values(var);
         result = "([";

         for (i = 0, s = map_sizeof(var); i < s; i++) {
            result += save_value(keys[i]) + ":" + save_value(values[i]) + ",";
         }

         result += "])";
         break;
      default :
         result = nil;
         break;
   }
   return result;
}
