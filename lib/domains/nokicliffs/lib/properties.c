#include "../domain.h"

inherit "/sys/lib/modules/m_properties";

#define PROPERTIES_LOG NOKICLIFFS_LOG_DIR + "/properties.log"

static mapping tmp_properties;
static string  properties_file_name;
static int     was_warning;

int query_was_warning(void) {
   return was_warning;
}

private void init_tmp_properties(void) {
   if (!tmp_properties) {
      tmp_properties = ([ ]);
   }
}

private void properties_warn(string warning) {
   was_warning = 1;
   write_file(PROPERTIES_LOG,
      ctime(time()) + ":" +
      properties_file_name + ": "
      + warning + "\n");
}

private void read_property_line(string property_line, int line) {
   string key, val;
   int    parse_results;
   if (empty_str(property_line) || property_line[0] == '#') {
      return;
   }
   
   parse_results = sscanf(property_line, "%s=%s", key, val);
   if (parse_results == 2) {
      if (property(key)) {
         properties_warn("Key from file found in object: " + key);
      }
      if (member_map(key, tmp_properties)) {
         properties_warn("Key from file found in file: " + key);
      }
      tmp_properties[key] = val;
      return;
   }
   properties_warn("Invalid line: " + line);
}

private void load_tmp_properties(void) {
   string *keys;
   int     i, dim;

   keys = map_indices(tmp_properties);
   dim = sizeof(keys);
   for (i = 0; i < dim; i++) {
      set_property(keys[i], tmp_properties[keys[i]]);
   }
}

/* set_property_file() is nomasked anyway. */
int load_properties(string file_name) {
   string *lines;
   int     i, dim;

   if (empty_str(file_name)) {
      return -1;
   }
   
   properties_file_name = file_name;
   if (file_exists(file_name) < 1) {
      return -2;
   }

   was_warning = 0;
   tmp_properties = ([ ]);
   dim = file_size(properties_file_name);
   lines = explode(read_file(properties_file_name, 0, dim), "\n");
   dim = sizeof(lines);
   for (i = 0; i < dim; i++) {
      read_property_line(lines[i], (i + 1));
   }
   load_tmp_properties();

   return 1;
}

int write_properties(string file_name) {
   string *keys;
   int     i, dim;

   if (empty_str(file_name)) {
      return -1;
   }

   keys = map_indices(properties);
   dim = sizeof(keys);
   for (i = 0; i < dim; i++) {
      write_file(file_name, keys[i] + "=" +
         property(keys[i]) + "\n");
   }   
   
   return 1;
}
