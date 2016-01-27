/* inheritable for commands */

string *alsos, *wizalsos, *admalsos, *usage;

static void main( string arg );

static nomask string query_command(void) {
  return get_otlvar( "command" );
}

nomask void _main(string arg, string cmd) {
  if (previous_program() == COMMAND_D) {
    set_otlvar("command", cmd);
    main(arg);
  }
}

string *get_alsos() {
   string *lines, tmp;
   int i, sz, done, tmplen, width;

   lines = ({ "See also:" });

   done = 0;
   width = this_player()->query_width() - 8;

   if (alsos) {
      sz = sizeof(alsos);

      for (i = 0; i < sz; i++) {
         if (!done) {
             tmp = "\t" + alsos[i];
             tmplen = strlen(tmp);
             done = 1;
         } else {
            tmplen += strlen(alsos[i] + 2);
	    if (tmplen < width) {
               tmp += ", " + alsos[i]; 
            } else {
               lines += ({ tmp });
               tmp = "\t" + alsos[i];
               tmplen = strlen(tmp);
            }
         }
      }
   }
   if (query_wizard(this_player()) && wizalsos) {
      sz = sizeof(wizalsos);

      for (i = 0; i < sz; i++) {
         if (!done) {
            tmp = "\t" + wizalsos[i];
            tmplen = strlen(tmp);
            done = 1;
         } else {
            tmplen += strlen(wizalsos[i] + 2);
	    if (tmplen < width) {
               tmp += ", " + wizalsos[i]; 
            } else {
               lines += ({ tmp });
               tmp = "\t" + wizalsos[i];
               tmplen = strlen(tmp);
            }
         }
      }
   }
   if (query_admin(this_player()) && admalsos) {
      sz = sizeof(admalsos);

      for (i = 0; i < sz; i++) {
         if (!done) {
            tmp = "\t" + admalsos[i];
            tmplen = strlen(tmp);
            done = 1;
         } else {
            tmplen += strlen(admalsos[i] + 2);
	    if (tmplen < width) {
               tmp += ", " + admalsos[i]; 
            } else {
               lines += ({ tmp });
               tmp = "\t" + admalsos[i];
               tmplen = strlen(tmp);
            }
         }
      }
      lines += ({ tmp });
   }

   return lines;
}

int add_also(string type, string value) {
	if (type == "admin") {
		if (!admalsos) {
			admalsos = ({ value });
		} else {
			admalsos += ({ value });
		}
	} else if ((type == "wiz") || (type == "wizard")) {
		if (!wizalsos) {
			wizalsos = ({ value });
		} else {
			wizalsos += ({ value });
		}
	} else if (type == "player") {
		if (!alsos) {
			alsos = ({ value });
		} else {
			alsos += ({ value });
		}
	} else {
		return 0;
	}
}
