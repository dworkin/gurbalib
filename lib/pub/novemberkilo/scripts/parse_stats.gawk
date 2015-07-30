#!/usr/bin/gawk -f

# N.B.: requires gawk
# usage: ./scripts/parse_stats.gawk ./lib/logs/stats.raw

BEGIN {
	FS = ":";
}

/enter:/ {
	enter_data[$2]++;
}

/killed:/ {
	killers_data[$2]++;
}

END {
	PROCINFO["sorted_in"] = "@val_num_desc";
	print "Last run on", strftime("%d/%m/%Y at %H:%M:%S", systime());
	print "\nMOST ENTERED";
	print_data(enter_data);
	print "\nKILLERS";
	print_data(killers_data);
}

function print_data(data) {
	asort(data, sorted_data);
	print_simple_data(data);
}

function print_simple_data(data) {
	for (element in data) {
		printf("%s: %s\n", element, data[element]);
	}
}

