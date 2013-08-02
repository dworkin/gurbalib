void usage() {
    string *lines;

    lines = ({ "Usage: wield [-h] [all|obj]" });
    lines += ({ "" });
    lines += ({ "Allows you to equip a given object OBJ." });
    lines += ({ "" });
    lines += ({ "Options:" });
    lines += ({ "\t-h\tHelp, this usage message." });
    lines += ({ "\tall\tEquip all available objects." });
    lines += ({ "Examples:" });
    lines += ({ "\twield sword" });
    lines += ({ "\twield axe" });
    lines += ({ "See also:" });
    lines += ({ "\tget, drop, put, remove, wear" });

    this_player()->more(lines);
}
int do_wield(object obj, int loud) {
    string slot;
    object *wielded;

    if (!obj) {
	if (loud) {
	    write("Maybe you should get one first?");
	}
	return 0;
    }

    if (!obj->is_wieldable()) {
	if (loud) {
	    write("You can't wield that.");
	}
	return 0;
    }

    if (obj->query_wielded() == 1) {
	if (loud) {
	    write("You already are wielding that.");
	}
	return 0;
    }

    wielded = this_player()->query_wielded();

    if (obj->query_wield_type() == "single") {
	if (sizeof(wielded) >= 2) {
	    write("Your hands are full.");
	    return 0;
	}
    } else {
	if (sizeof(wielded) != 0) {
	    write("You are already wielding something else.");
	    return 0;
	}
    }

    this_player()->do_wield(obj);
    this_player()->targetted_action(obj->query_wield_message(), nil, obj);
    return 1;
}

void main(string str) {
    object obj;
    object *inv;
    int i, max, done;

    if (!str || (str == "")) {
	usage();
	return;
    }

    if (sscanf(str, "-%s", str)) {
	usage();
	return;
    }

    if (str == "all") {
	inv = this_player()->query_inventory();
	max = sizeof(inv);
	done = 0;
	for (i = 0; i < max; i++) {
	    if (do_wield(inv[i], 0)) {
		done = 1;
	    }
	}
	if (!done) {
	    write("You have nothing to wield.\n");
	}
	return;
    }

    obj = this_player()->present(lowercase(str));
    do_wield(obj, 1);
}
