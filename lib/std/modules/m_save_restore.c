/*
 * save_restore.c
 *
 * Emulates the MudOS save_variable and restore_variable efunctions.
 * 
 * 8 January 1997	Begun		Greg Lewis
 *	# Wrote and tested initial version.  restore_variable needs to do
 *	  error checking though (i.e., it works if the string it gets is 
 *	  right, but crashes and burns otherwise ;).
 * 
 * 10 January 1997	Version 1.0	Greg Lewis
 *	# Added error checking to restore_variable, it returns RESTORE_ERROR
 *	  (#define'd in save_restore.h) upon errors in the restore process.
 *	# Everything seems to test ok, not that I've been all that thorough.
 *
 * TBD
 *	# Prolly needs some more commenting (doesn't most code?)
 *
 * February 2009        Version 2.0     Bart van Leeuwen
 *      # Rewritten restore_variable()
 *      # Fix implode/explode related bugs in save_variable()
 */

/* Includes */

#include	<type.h>
#include	<m_save_restore.h>

/*
 * Conversion functions used by the restore_variable grammar
 */
int * cnvint(mixed * data) {
  int r;

  sscanf(data[0],"%d",r);
  return ({ r });
}

float * cnvfloat(mixed * data) {
  float r;

  sscanf(data[0],"%f",r);
  return ({ r });
}

object * cnvobj(mixed * data) {
  string n;
  int i;

  n = "";
  for(i=0;i<sizeof(data[0]);i++) {
    n += data[0][i];
  }
  return ({ find_object(n) });
}

string * emptystring(mixed * data) {
  return ({ "" });
}

string * concatstring(mixed * data) {
  int i;

  string r;
  r = "";

  for(i=0;i<sizeof(data);i++) {
    if(data[i] == "\\") i++;
    r += data[i];
  }

/*
 * It seems this is not needed
 *
  r = implode(explode(r,"\\\""),"\"");
  r = implode(explode(r,"\\\\"),"\\");
*/
  return ({ r[1..strlen(r)-2] });
}

mixed * mkemptyarray(mixed * data) {
  return ({ ({ }) });
}

mixed * mkarray(mixed * data) {
  int i;
  mixed * stuff;
  stuff = ({ });
  for(i=1; i<sizeof(data) && data[i] != "})"; i += 2) {
    stuff += ({ data[i] });
  }
  return ({ stuff });
}

mixed * mkemptymap(mixed * data) {
  return ({ ([ ]) });
}

mixed * mkmap(mixed * data) {
  int i;
  mapping stuff;
  mixed key,val;

  stuff = ([ ]);
  for(i=1; i<sizeof(data) && data[i] != "])"; i += 4) {
    key = data[i];
    val = data[i+2];
    stuff[key] = val;
  }
  return ({ stuff });
}

mixed restore_variable(string str) {
  mixed * result;

  result = parse_string(GRAMMAR, str);

  if(!result || sizeof(result) < 1) {
    return nil;
  } else {
    return result[0];
  }
}

string save_variable(mixed var) {
   string       result;
   int          i, s;
   mixed        *keys, *values;
   string pref,post;

   if (!var) {
      return "0";
   }
   switch (typeof(var)) {
      case T_INT : case T_FLOAT :
         result = ""+var;
         break;
      case T_STRING :

         if(strlen(var) > 0) {
           if(var[0..0] == "\\") {
             pref = "\\\\";
           } else if(var[0..0] == "\"") {
             pref = "\\\"";
           } else {
             pref = "";
           }

           if(var[strlen(var)-1] == '\\') {
             post = "\\\\";
           } else if(var[strlen(var)-1] == '\"') {
             post = "\\\"";
           } else {
             post = "";
           }

           result = implode(explode(var, "\\"), "\\\\");
           result = implode(explode(result, "\""), "\\\"");
           result = "\""+pref+result+post+"\"";
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
            result += save_variable(var[i]) + ",";
         }
         result += "})";
         break;
      case T_MAPPING :
         keys = map_indices(var);
         values = map_values(var);
         result = "([";
         for (i = 0, s = map_sizeof(var); i < s; i++) {
            result += save_variable(keys[i]) + ":" + save_variable(values[i])
                      + ",";
         }
         result += "])";
         break;
      default :
         result = nil;
         break;
   }
   return result;
}
