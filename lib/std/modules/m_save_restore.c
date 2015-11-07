/*
 * save_restore.c
 *
 * Emulates the MudOS save_variable and restore_variable efunctions.
 * 
 * 8 January 1997       Begun         Greg Lewis
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
 */

#include <type.h>

#define GRAMMAR \
  "escaped=/\\\\/\n" + \
  "quote=/\"/\n" + \
  "floats=/[\-]?[0-9]*[.][0-9]+/\n" + \
  "arraystart=/[(][{][ ]*/\n" + \
  "arrayend=/[ ]*[}][)]/\n" + \
  "arraysep=/[ ]*,[ ]*/\n" + \
  "mapstart=/[(][[][ ]*/\n" + \
  "mapend=/[ ]*][)]/\n" + \
  "mapsep=/[ ]*:[ ]*/\n" + \
  "ints=/[\-]?[0-9]+/\n" + \
  "char=/./\n" + \
  "var: float\n" + \
  "var: int\n" + \
  "var: string\n" + \
  "var: array\n" + \
  "var: map\n" + \
  "string: quote quote ? emptystring\n" + \
  "string: quote chars quote ? concatstring\n" + \
  "array: arraystart arrayend ? mkemptyarray\n" + \
  "array: arraystart arrayelements arrayend ? mkarray\n" + \
  "map: mapstart mapend ? mkemptymap\n" + \
  "map: mapstart mapelements mapend ? mkmap\n" + \
  "arrayelements: element\n" + \
  "arrayelements: arrayelements arraysep element\n" + \
  "arrayelements: arrayelements arraysep\n" + \
  "element: int\n" + \
  "element: float\n" + \
  "element: string\n" + \
  "element: array\n" + \
  "element: map\n" + \
  "mapelements: element mapsep element\n" + \
  "mapelements: mapelements arraysep element mapsep element\n" + \
  "mapelements: mapelements arraysep\n" + \
  "chars: char\n" + \
  "chars: escaped escaped\n" + \
  "chars: escaped quote\n" + \
  "chars: arraystart\n" + \
  "chars: arrayend\n" + \
  "chars: mapstart\n" + \
  "chars: mapend\n" + \
  "chars: arraysep\n" + \
  "chars: mapsep\n" + \
  "chars: floats\n" + \
  "chars: ints\n" + \
  "chars: chars char\n" + \
  "chars: chars escaped escaped\n" + \
  "chars: chars escaped quote\n" + \
  "chars: chars arraystart\n" + \
  "chars: chars arrayend\n" + \
  "chars: chars mapstart\n" + \
  "chars: chars mapend\n" + \
  "chars: chars arraysep\n" + \
  "chars: chars mapsep\n" + \
  "chars: chars floats\n" + \
  "chars: chars ints\n" + \
  "int: ints ? cnvint\n" + \
  "float: floats ? cnvfloat\n"

/* Conversion functions used by the restore_variable grammar */
int *cnvint(mixed * data) {
   int r;

   sscanf(data[0], "%d", r);
   return ({ r });
}

float *cnvfloat(mixed * data) {
   float r;

   sscanf(data[0], "%f", r);
   return ({ r });
}

object *cnvobj(mixed * data) {
   string n;
   int i;

   n = "";
   for (i = 0; i < sizeof(data[0]); i++) {
      n += data[0][i];
   }
   return ({ find_object(n) });
}

string *emptystring(mixed * data) {
   return ({ "" });
}

string *concatstring(mixed * data) {
   int i, maxi;
   string r;

   r = "";

   maxi = sizeof(data);
   for (i = 0; i < maxi; i++) {
      if (data[i] == "\\") {
        i++;
      }
      r += data[i];
   }

   return ({ r[1..strlen(r) - 2] });
}

mixed *mkemptyarray(mixed * data) {
   return ({ ({ }) });
}

mixed *mkarray(mixed * data) {
   int i, maxi;
   mixed *stuff;

   stuff = ({ });
   maxi = sizeof(data);
   for (i = 1; i < maxi && data[i] != "})"; i += 2) {
      stuff += ({ data[i] });
   }
   return ({ stuff });
}

mixed *mkemptymap(mixed * data) {
   return ({ ([]) });
}

mixed *mkmap(mixed * data) {
   int i, maxi;
   mapping stuff;
   mixed key, val;

   stuff = ([]);
   maxi = sizeof(data);
   for (i = 1; i < maxi && data[i] != "])"; i += 4) {
      key = data[i];
      val = data[i + 2];
      stuff[key] = val;
   }
   return ({ stuff });
}

mixed restore_variable(string str) {
   mixed *result;

   result = parse_string(GRAMMAR, str);

   if (!result || sizeof(result) < 1) {
      return nil;
   } else {
      return result[0];
   }
}

string save_variable(mixed var) {
   string result;
   int i, s;
   mixed *keys, *values;
   string pref, post;

   if (!var) {
      return "0";
   }
   switch (typeof(var)) {
      case T_INT:
      case T_FLOAT:
         result = "" + var;
         break;
      case T_STRING:
         if (strlen(var) > 0) {
            if (var[0..0] == "\\") {
               pref = "\\\\";
            } else if (var[0..0] == "\"") {
               pref = "\\\"";
            } else {
               pref = "";
            }

            if (var[strlen(var) - 1] == '\\') {
               post = "\\\\";
            } else if (var[strlen(var) - 1] == '\"') {
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
      case T_OBJECT:
         result = object_name(var);
         break;
      case T_ARRAY:
         result = "({";
         s = sizeof(var);
         for (i = 0; i < s; i++) {
            result += save_variable(var[i]) + ",";
         }
         result += "})";
         break;
      case T_MAPPING:
         keys = map_indices(var);
         values = map_values(var);
         result = "([";
         s = map_sizeof(var);
         for (i = 0; i < s; i++) {
            result += save_variable(keys[i]) + ":" +
               save_variable(values[i]) + ",";
         }
         result += "])";
         break;
      default:
         result = nil;
         break;
   }

   return result;
}
