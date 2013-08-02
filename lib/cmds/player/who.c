void usage() {
    string *lines;

    lines = ({ "Usage: who [-h] [PLAYER]" });
    lines += ({ "" });
    lines += ({ "Print out a list of who is on the system." });
    lines += ({ "If PLAYER is specified, give detailed info about the player." 
    });
    lines += ({ "" });
    lines += ({ "Options:" });
    lines += ({ "\t-h\tHelp, this usage message." });
    lines += ({ "Examples:" });
    lines += ({ "\twho" });
    lines += ({ "\twho sirdude" });
    lines += ({ "See also:" });
    if (query_wizard(this_player())) {
	lines += ({ "\tlast, locate, look, mudlist, possess, rwho, " +
	  "snoop, where" });
    } else {
	lines += ({ "\tlook" });
    }

    this_player()->more(lines);
}

/* 'who' command Originally by Fudge Improved by Cerihan 3/15/09 */
void main(string str) {
    object *usr;
    int i, long_flag, hidden;
    mixed idletime;
    string idle;

    if (query_wizard(this_player())) {
	long_flag = 1;
    } else {
	long_flag = 0;
    }

    if (str && (str != "")) {
	if (sscanf(str, "-%s", str)) {
	    usage();
	    return;
	}
	if (USER_D->player_exists(str)) {
	    USER_D->finger(this_player(), str);
	} else {
	    write(capitalize(str) + " exists only in your dreams.\n");
	}
	return;
    }

    usr = players();

    write(MUD_NAME + " currently has " + sizeof(usr) + " users online.");
    write("------------------------------------------------------");
    for (i = 0; i < sizeof(usr); i++) {
	string line;

	line = usr[i]->query_title();

	if (usr[i]->query_env("hidden") == 1) {
	    hidden = 1;
	    line += " %^BOLD%^%^RED%^(hidden)%^RESET%^";
	} else
	    hidden = 0;

	if (query_admin(usr[i])) {
	    line += " %^BOLD%^%^BLUE%^(Admin)%^RESET%^";
	} else if (query_wizard(usr[i])) {
	    line += " %^CYAN%^(Wizard)%^RESET%^";
	}

	idletime = format_time(usr[i]->query_idle());
	if (idletime == "") {
	    idle = "";
	} else {
	    idle = "  (idle " + idletime + ")";
	}
	line += idle;

	if (long_flag == 1) {
	    if (usr[i]->query_environment()) {
		write(line + "\n\t" + usr[i]->query_name() + "'s Location: " +
		  usr[i]->query_environment()->query_short() + "\n");
	    } else {
		write(line + "\n\t" + usr[i]->query_name() + "\n");
	    }
	} else {
	    if (!hidden) {
		write(line + "\n");
	    }
	}
    }
    write("------------------------------------------------------");
}
