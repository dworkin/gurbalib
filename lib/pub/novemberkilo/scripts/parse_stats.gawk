#!/usr/bin/gawk -f

# N.B.: requires gawk
# usage: ./scripts/parse_stats.gawk ./lib/logs/stats.raw

BEGIN {
	FS = ":";
}

/enter:/ {
	enter_data[$2]++;
}

END {
	print "Last run on", strftime("%d/%m/%Y at %H:%M:%S", systime());
	print_enter_data();
}

function print_enter_data() {
	PROCINFO["sorted_in"] = "@val_num_desc";
	asort(enter_data, sorted_data);
	print_simple_data(enter_data);
}

function print_simple_data(data) {
	for (element in data) {
		printf("%s: %s\n", element, data[element]);
	}
}

