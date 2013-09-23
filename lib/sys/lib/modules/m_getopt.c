/*
 * getopt module
 *
 * Aidil@Way of the Force.
 *
 *
 * Usage:
 * 
 * first call set_options to define options the parser
 * should recognize. set_options requires a mapping as argument:
 *
 * ([ "option name" : ({ "short option", "long option", ARG }) ])
 *
 * When arg is something other then 0, the option will require an
 * argument.
 *
 * To parse your input:
 *
 * str = parse_for_options(str);
 *
 * str will contain the remainder of input, will all options and
 * their arguments removed.
 *
 * To see if an option was set:
 *
 * test_option("option name")
 *
 * To query the argument provided for an option:
 *
 * query_option("option name")
 *
 * To request a map of all options and the values
 * they were set to:
 * query_options()
 * 
 */

#define SHORT 0
#define LONG  1
#define VALUE 2
#define MULTI 3
#define NAME 0
#define VREQ 1
#define VMUL 2

private mapping longopts;
private mapping shortopts;

static void set_options(mapping m) {
   int i,sz, oi, osz;
   string *opt;

   if (!m) {
      longopts = nil;
      shortopts = nil;
      return;
   }

   opt = map_indices(m);
   shortopts = ([ ]);
   longopts = ([ ]);

   for (i=0, sz=sizeof(opt); i<sz; i++) {
      int vreq;
      int multi;
      mixed sopt;
      mixed lopt;

      if (sizeof(m[opt[i]]) > 2) {
         vreq = (1 && m[opt[i]][VALUE]);
      }

      if (sizeof(m[opt[i]]) > 3) {
         multi = (1 && m[opt[i]][MULTI]);
      }

      sopt = m[opt[i]][SHORT];
      lopt = m[opt[i]][LONG];

      if (sopt) {
         if (arrayp(sopt)) {
            for (oi=0,osz=sizeof(sopt); oi<osz; oi++) {
               shortopts[sopt[oi]] = ({ opt[i], vreq, multi });
            }
         } else {
            shortopts[sopt] = ({ opt[i], vreq, multi });
         }
      }
      if (lopt) {
         if (arrayp(lopt)) {
            for (oi=0, osz=sizeof(lopt); oi<osz; oi++) {
               longopts[lopt[oi]] = ({ opt[i], vreq, multi });
            }
         } else {
            longopts[m[opt[i]][LONG]] = ({ opt[i], vreq, multi });
         }
      }
   }
}

private mixed *parse_long_option(string opt, string str) {
   string r;
   string err;
   string val;
   int end;
   mixed m;

   m = get_otlvar("options");

   if (opt == "") {
      end = 1;
   } else if (sscanf(opt, "%s=%s", r, val) == 2) {
      if (!longopts[r]) {
         err = "--" + r + " is not a recognized (long) option.";
         end = 1;
      } else if (!longopts[r][VREQ]) {
         err = "--" + r + " does not take an argument.";
         end = 1;
      } else {
         mixed m;

         m = get_otlvar("options");

         if (longopts[r][VMUL]) {
            if (!m[longopts[r][NAME]]) {
               m[longopts[r][NAME]] = ({ val });
            } else {
               m[longopts[r][NAME]] += ({ val });
            }
         } else {
            m[longopts[r][NAME]] = val;
         }
      }
   } else {
      if (!longopts[opt]) {
         err = "--" + opt + " is not a recognized (long) option.";
         end = 1;
      } else if (longopts[opt][VREQ]) {
         err = "--" + opt + " requires an argument.";
         end = 1;
      } else {
         if (!m[longopts[opt][NAME]]) {
            m[longopts[opt][NAME]] = 1;
         } else {
            m[longopts[opt][NAME]]++;
         }
      }
   }
   set_tlvar("options",m);
   return ({ end, str, err });
}

private mixed *parse_short_option(string opt, string str) {
   string r;
   string err;
   string val;
   int end;
   mixed m;

   m = get_otlvar("options");

   if (opt == "-") {
      end = 1;
   } else if (shortopts[opt]) {
      if (shortopts[opt][VREQ]) {
         if (str && strlen(str)) {
            if (sscanf(str, "%s %s", val, r) == 2) {
               str = r;
            } else {
               val = str;
               end = 1;
               str = "";
            }
            if (!shortopts[opt][VMUL]) {
               m[shortopts[opt][NAME]] = val;
            } else { 
               if (!m[shortopts[opt][NAME]]) {
                  m[shortopts[opt][NAME]] = ({ val });
               } else {
                  m[shortopts[opt][NAME]] += ({ val });
               }
            }
         } else {
            err = "option " + shortopts[opt][NAME] + " requires a value";
            end = 1;
         }
      } else {
         if (!m[shortopts[opt][NAME]]) {
            m[shortopts[opt][NAME]] = 1;
         } else {
            m[shortopts[opt][NAME]]++;
         }
      }
   } else {
      end = 1;
      err = "Option " + opt + " is not a recognized (short) option.";
   }

   if (!str) {
      str = "";
   }
   set_tlvar("options",m);
   return ({ end, str, err });
}

private mixed *parse_option(string str) {
   mapping options;
   string opt;
   string err;
   string r;
   int end;
   int i,sz;

   if (sscanf(str, "--%s %s", opt, r) == 2 || sscanf(str, "--%s", opt) == 1) {
      return parse_long_option(opt, r);
   }

   if (sscanf(str, "-%s %s", opt, r) == 2) {
      str = r;
   } else if(sscanf(str, "-%s", opt) == 1) {
      str = nil;
   } else {
      return ({ 1, str, nil });
   }

   for (i=0,sz=strlen(opt); i<sz && !end; i++) {
      ({ end, str, err }) = parse_short_option(opt[i..i], str);
   }

   if (str == "") {
      end = 1;
   }

   return ({ end, str, err });
}

static string parse_for_options(string str) {
   int end;
   string err;

   set_otlvar("options", ([ ]));

   while (str && !end) {
     ({ end, str, err }) = parse_option(str);
   }

   set_otlvar("parse_error", err);

   return str;
}

static string query_parse_error() {
   return get_otlvar("parse_error");
}

static mapping query_options() {
   return get_otlvar("options");
}

static mixed query_option(string n) {
   mapping opts;

   opts = get_otlvar("options");

   if (opts) {
      return opts[n];
   }
}

static int test_option(string n) {
   return 1 && query_option(n);
}

