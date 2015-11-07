/* return a string describing a value */
static string dump_value(mixed value, varargs mapping seen) {
   string str;
   int i, sz;
   mixed *indices, *values;

   if (!seen) {
      seen = ([]);
   }

   switch (typeof(value)) {
      case T_INT:
      case T_FLOAT:
         return (string) value;

      case T_STRING:
         str = value;
         if (sscanf(str, "%*s\\") != 0) {
            str = implode(explode("\\" + str + "\\", "\\"), "\\\\");
         }
         if (sscanf(str, "%*s\"") != 0) {
            str = implode(explode("\"" + str + "\"", "\""), "\\\"");
         }
         if (sscanf(str, "%*s\n") != 0) {
            str = implode(explode("\n" + str + "\n", "\n"), "\\n");
         }
         if (sscanf(str, "%*s\t") != 0) {
            str = implode(explode("\t" + str + "\t", "\t"), "\\t");
         }
         return "\"" + str + "\"";

      case T_OBJECT:
         return "<" + object_name(value) + ">";

      case T_ARRAY:
         if (seen[value]) {
            return "#" + (seen[value] - 1);
         }

         seen[value] = map_sizeof(seen) + 1;
         sz = sizeof(value);
         if (sz == 0) {
            return "({ })";
         }

         str = "({ ";
         for (i = 0, --sz; i < sz; i++) {
            str += dump_value(value[i], seen) + ", ";
         }

         return str + dump_value(value[i], seen) + " })";

      case T_MAPPING:
         if (seen[value]) {
            return "@" + (seen[value] - 1);
         }

         seen[value] = map_sizeof(seen) + 1;
         sz = map_sizeof(value);
         if (sz == 0) {
            return "([ ])";
         }

         str = "([ ";
         indices = map_indices(value);
         values = map_values(value);

         for (i = 0, --sz; i < sz; i++) {
            str += dump_value(indices[i], seen) + ":" +
               dump_value(values[i], seen) + ", ";
         }
         return str + dump_value(indices[i], seen) + ":" +
            dump_value(values[i], seen) + " ])";
      case T_NIL:
         return "<NIL>";
   }
}
