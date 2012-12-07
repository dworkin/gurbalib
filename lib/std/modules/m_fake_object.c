mapping fake_desc;

void set_items(string id, varargs mixed args ...) {
   string description;
   int i;

   if (!fake_desc)
      fake_desc = ([]);

   description = args[sizeof(args) - 1];
   fake_desc[id] = description;

   if (sizeof(args) > 1) {
      for (i = 0; i < sizeof(args) - 1; i++) {
	 fake_desc[args[i]] = description;
      }
   }
}

void add_item(string id, varargs mixed args ...) {

   string description;
   int i;

   if (!fake_desc)
      fake_desc = ([]);

   description = args[sizeof(args) - 1];
   fake_desc[id] = description;

   if (sizeof(args) > 1) {
      for (i = 0; i < sizeof(args) - 1; i++) {
	 fake_desc[args[i]] = description;
      }
   }
}

void remove_item(string id) {
   mapping temp_desc;
   int size;
   string *values;
   string *indices;
   string description;
   int i;

   if (!fake_desc) {
      fake_desc = ([]);
   }
   temp_desc = ([]);
   description = fake_desc[id];
   size = map_sizeof(fake_desc);
   values = map_values(fake_desc);
   indices = map_indices(fake_desc);

   for (i = 0; i <= size - 1; i++) {
      if (description != values[i]) {
	 temp_desc[indices[i]] = values[i];
      }
   }
   fake_desc = ([]);
   fake_desc = temp_desc;
}

string *query_fake_ids(void) {
   if (!fake_desc)
      fake_desc = ([]);
   return (map_indices(fake_desc));
}

string *query_items(void) {
   if (!fake_desc)
      fake_desc = ([]);
   return (map_indices(fake_desc));
}

string query_item(string item) {
   if (!fake_desc)
      fake_desc = ([]);
   return (fake_desc[item]);
}
