string *a_banned_sites; /*   A class subnet 1.*.*.*    */
string *b_banned_sites; /*   B class subnet 1.2.*.*    */
string *c_banned_sites; /*   C class subnet 1.2.3.*    */

void create(void) {
   mixed *list;

   list = get_dir("/data/banned/a/*");
   a_banned_sites = list[0];
   list = get_dir("/data/banned/b/*");
   b_banned_sites = list[0];
   list = get_dir("/data/banned/c/*");
   c_banned_sites = list[0];
}

string *query_a_banned_sites(void) {
   return a_banned_sites;
}

string *query_b_banned_sites(void) {
   return b_banned_sites;
}

string *query_c_banned_sites(void) {
   return c_banned_sites;
}

string *query_banned_sites(void) {
   string *tmp;

   tmp = a_banned_sites + b_banned_sites + c_banned_sites;
   return tmp;
}

int is_a_banned(string name) {
   string *tmp;
   string tmp_name;

   if (strlen(name) == 0) {
      return 0;
   }
   tmp = explode(name, ".");
   if (!sizeof(tmp)) {
      return 0;
   }
   tmp_name = tmp[0] + ".*.*.*";

   if (member_array(tmp_name, a_banned_sites) != -1) {
      return 1;
   }
   return 0;
}

int is_a_newbanned(string name) {
   string *tmp;
   string tmp_name;

   if (member_array("new.new.new.new", a_banned_sites) != -1) {
      return 1;
   }
   tmp = explode(name, ".");
   if (!sizeof(tmp)) {
      return 0;
   }
   tmp_name = tmp[0] + ".new.new.new";

   if (member_array(tmp_name, a_banned_sites) != -1) {
      return 1;
   }
   return 0;
}

int is_b_banned(string name) {
   string *tmp;
   string tmp_name;

   if (!name) {
      return 0;
   }
   tmp = explode(name, ".");
   if (sizeof(tmp) < 2) {
      return 0;
   }
   tmp_name = tmp[0] + "." + tmp[1] + ".*.*";
   if (member_array(tmp_name, b_banned_sites) != -1) {
      return 1;
   }
   return 0;
}

int is_b_newbanned(string name) {
   string *tmp;
   string tmp_name;

   tmp = explode(name, ".");
   if (sizeof(tmp) < 2) {
      return 0;
   }
   tmp_name = tmp[0] + "." + tmp[1] + ".new.new";
   if (member_array(tmp_name, b_banned_sites) != -1) {
      return 1;
   }
   return 0;
}

int is_c_banned(string name) {
   string *tmp;
   string tmp_name;

   tmp = explode(name, ".");
   if (sizeof(tmp) < 3) {
      return 0;
   }
   tmp_name = tmp[0] + "." + tmp[1] + "." + tmp[2] + ".*";
   if (member_array(tmp_name, c_banned_sites) != -1) {
      return 1;
   }
   return 0;
}

int is_c_newbanned(string name) {
   string *tmp;
   string tmp_name;

   tmp = explode(name, ".");
   if (sizeof(tmp) < 3) {
      return 0;
   }
   tmp_name = tmp[0] + "." + tmp[1] + "." + tmp[2] + ".new";
   if (member_array(tmp_name, c_banned_sites) != -1) {
      return 1;
   }
   return 0;
}

int is_banned(string name) {
   if (is_a_banned(name)) {
      return 1;
   } else if (is_b_banned(name)) {
      return 1;
   } else if (is_c_banned(name)) {
      return 1;
   } else {
      return 0;
   }
}

int is_newbanned(string name) {
   if (is_a_newbanned(name)) {
      return 1;
   } else if (is_b_newbanned(name)) {
      return 1;
   } else if (is_c_newbanned(name)) {
      return 1;
   } else {
      return 0;
   }
}

int siteban(string str) {
   string *tmp;
   string tmp_name;
   int flag;

   flag = 0;
   tmp = explode(str, ".");
   if (sizeof(tmp) != 4) {
      return 0;
   }

   if ((tmp[1] == "new") && (tmp[2] == "new") && (tmp[3] == "new")) {
      /* A class siteban */
      write_file("/data/banned/a/" + str,
         ctime(time()) + "\tnewban by:  " + this_user()->query_name() + "\n");
      flag = 1;
      a_banned_sites += ({ str });
   } else if ((tmp[2] == "new") && (tmp[3] == "new")) {
      /* B class siteban */
      write_file("/data/banned/b/" + str,
         ctime(time()) + "\tnewban by:  " + this_user()->query_name() + "\n");
      flag = 1;
      b_banned_sites += ({ str });
   } else if (tmp[3] == "new") {
      /* C class siteban */
      write_file("/data/banned/c/" + str,
         ctime(time()) + "\tnewban by:  " + this_user()->query_name() + "\n");
      flag = 1;
      c_banned_sites += ({ str });
   } else if ((tmp[1] == "*") && (tmp[2] == "*") && (tmp[3] == "*")) {
      /* A class siteban */
      write_file("/data/banned/a/" + str,
         ctime(time()) + "\tby:  " + this_user()->query_name() + "\n");
      flag = 1;
      a_banned_sites += ({ str });
   } else if ((tmp[2] == "*") && (tmp[3] == "*")) {
      /* B class siteban */
      write_file("/data/banned/b/" + str,
         ctime(time()) + "\tby:  " + this_user()->query_name() + "\n");
      flag = 1;
      b_banned_sites += ({ str });
   } else if (tmp[3] == "*") {
      /* C class siteban */
      write_file("/data/banned/c/" + str,
         ctime(time()) + "\tby:  " + this_user()->query_name() + "\n");
      flag = 1;
      c_banned_sites += ({ str });
   } else {
      flag = 0;
   }

   return flag;
}

int unsiteban(string str) {
   string *tmp;
   string tmp_name;
   int flag;

   flag = 0;
   tmp = explode(str, ".");

   if (sizeof(tmp) != 4) {
      return 0;
   }
   if ((tmp[1] == "*") && (tmp[2] == "*") && (tmp[3] == "*")) {
      /* A class siteban */
      remove_file("/data/banned/a/" + str);
      flag = 1;
      a_banned_sites -= ({ str });
   } else if ((tmp[2] == "*") && (tmp[3] == "*")) {
      /* B class siteban */
      remove_file("/data/banned/b/" + str);
      flag = 1;
      b_banned_sites -= ({ str });
   } else if (tmp[3] == "*") {
      /* C class siteban */
      remove_file("/data/banned/c/" + str);
      flag = 1;
      c_banned_sites -= ({ str });
   } else if ((tmp[0] == "new") && (tmp[1] == "new") && (tmp[2] == "new") &&
      (tmp[3] == "new")) {
      /* A class siteban */
      remove_file("/data/banned/a/" + str);
      flag = 1;
      a_banned_sites -= ({ str });
   } else if ((tmp[1] == "new") && (tmp[2] == "new") && (tmp[3] == "new")) {
      /* A class siteban */
      remove_file("/data/banned/a/" + str);
      flag = 1;
      a_banned_sites -= ({ str });
   } else if ((tmp[2] == "new") && (tmp[3] == "new")) {
      /* B class siteban */
      remove_file("/data/banned/b/" + str);
      flag = 1;
      b_banned_sites -= ({ str });
   } else if (tmp[3] == "new") {
      /* C class siteban */
      remove_file("/data/banned/c/" + str);
      flag = 1;
      b_banned_sites -= ({ str });
   } else {
      flag = 0;
   }
   create();
   return flag;
}

string get_banned_info(string str) {
   string filename, info;

   if (is_a_banned(str) || is_a_newbanned(str)) {
      filename = "/data/banned/a/";
   } else if (is_b_banned(str) || is_b_newbanned(str)) {
      filename = "/data/banned/b/";
   } else if (is_c_banned(str) || is_c_newbanned(str)) {
      filename = "/data/banned/c/";
   } else {
      write("Unable to find site: " + str + "\n");
      return "";
   }
   info = unguarded("read_file", filename + str);
   if (!info) {
      return "Sorry cannot read file: " + filename + str + "\n";
   }
   filename = info + "\n";
   return filename;
}
