/*
 * JSON message generator and parser
 * This module was created as part of a framework to support
 * 'railsgame', a modular web based mud server (gurbalib acts as
 * gameserver component in the railsgame framework)
 *
 * By Aidil of Way of the Force, august 2009
 *
 * This code is in the public domain.
 *
 * Current limitations: No unicode support (\u00e9)
 *
 */

#include <type.h>

#define TOKENS  "whitespace=/[ 	]*/\n" + \
                "string=/\"([^\\\\\"\n]*(\\\\.)*)*\"/\n" + \
                "int=/-?[0-9]+/\n" + \
                "kvsep=/:/\n" + \
                "vsep=/,/\n" + \
                "e=/e[+\-]?/\n" + \
                "e=/E[+\-]?/\n"

#define RULES   "msg : value\n" + \
                "jsmap : '{' pairs '}' ? collect_mapping\n" + \
                "jslist : '[' values ']' ? wrap_list\n" + \
                "values : value\n" + \
                "values : values vsep value\n" + \
                "pairs : pair\n" + \
                "pairs : pairs vsep pair\n" + \
                "pair : key kvsep value ? wrap_kvpair\n" + \
                "key : ustring\n" + \
                "value: ustring\n" + \
                "value: number\n" + \
                "value: jsmap\n" + \
                "value: jslist\n" + \
                "number: int ? to_int\n" + \
                "number: int frac ? to_float\n" + \
                "number: int exp ? to_float\n" + \
                "number: int frac exp ? to_float\n" + \
                "exp: e int ? normalize_exp\n" + \
                "frac: '.' int\n" + \
                "ustring: string ? unquote_string"

string save_value(mixed data) {
   string service, action, result;
   string *keys;
   int count, size;

   argcheck(data != nil, 1, "non nil value");

   switch (typeof(data)) {
      case T_STRING:
         data = replace_string(data, "\"", "\\\"");
         data = replace_string(data, "\\", "\\\\");
         data = replace_string(data, "\n", "\\n");
         data = replace_string(data, "\t", "\\t");
         data = replace_string(data, "\r", "\\r");
         data = replace_string(data, "\f", "\\f");
         data = replace_string(data, "\b", "\\b");
         result = "\"" + data + "\"";
         break;
      case T_FLOAT:
      case T_INT:
         result = (string) data;
         break;
      case T_ARRAY:
         result = "[";
         for (count = 0, size = sizeof(data); count < size; count++) {
            if (count > 0) {
               result += ", ";
            }
            result += save_value(data[count]);
         }
         result += "]";
         break;
      case T_MAPPING:
         result = "{";
         keys = map_indices(data);
         for (count = 0, size = sizeof(keys); count < size; count++) {
            if (count > 0) {
               result += ", ";
            }
            result += save_value(keys[count]);
            result += ":";
            result += save_value(data[keys[count]]);
         }
         result += "}";
         break;
      default:
         error("Unhandled value for save_value: " + dump_value(data));
         break;
   }
   return result;
}

mixed restore_value(string message) {
   int count, size;
   mapping result;
   mixed *parse_tree;

   parse_tree = parse_string(TOKENS + RULES, message);

   if (!parse_tree) {
      error("Bad message format");
   }

   return parse_tree[0];
}

static mixed *collect_mapping(mixed * data) {
   int count, size;

   mapping result;

   result = ([]);

   for (count = 0, size = sizeof(data); count < size; count++) {
      if (mappingp(data[count])) {
         result += data[count];
      }
   }
   return ( { result } );
}

static mixed *wrap_kvpair(mixed * data) {
   return ( { ([data[0]:data[2]]) } );
}

static mixed *wrap_list(mixed * data) {
   int count, size;

   mixed *result;

   result = allocate((sizeof(data) - 1) / 2);
   for (count = 1, size = sizeof(data); count < size; count += 2) {
      result[count / 2] = data[count];
   }
   return ( { data } );
}

static mixed *unquote_string(mixed * data) {
   data[0] = replace_string(data[0], "\\\"", "\"");
   data[0] = replace_string(data[0], "\\\\", "\\");
   data[0] = replace_string(data[0], "\\n", "\n");
   data[0] = replace_string(data[0], "\\t", "\t");
   data[0] = replace_string(data[0], "\\r", "\r");
   data[0] = replace_string(data[0], "\\f", "\f");
   data[0] = replace_string(data[0], "\\b", "\b");
   return ( { data[0][1..strlen(data[0]) - 2] } );
}

static mixed *to_float(mixed * data) {
   float f;

   string v;

   v = implode(data, "");
   if (sscanf(v, "%f", f) == 1) {
      return ( { f } );
   }
}

static mixed *to_int(mixed * data) {
   int i;

   if (sscanf(data[0], "%d", i) == 1) {
      return ( { i } );
   }
}

static mixed *normalize_exp(mixed * data) {
   if (strlen(data[0]) == 1) {
      data[0] += "+";
   }
   data[0] = lowercase(data[0]);
   return data;
}
