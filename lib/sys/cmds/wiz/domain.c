/*
 * domain is a wizard command, not an admin command.
 *
 * 1. people can leave a domain without needing admin
 * 2. wizards can be admin of their own domain, and can add/remove members
 * 3. only mud/game admins can promote/demote domain admins
 *
 * As a consequence, there are some explicit access checks in here.
 *
 */

inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: domain [-h] [list] [<domain> <command> [arg]]" });
   lines += ({ "This command is used to manage domains." });
   lines += ({ "If you call it with list it will print all registered " +
      "domains." });
   lines += ({ "To create a new domain, just call the add command with " +
      "your domain admin as arg." });
   lines += ({ "If your not listing domains you will use a domain command" });
   lines += ({ "\tadd [name] : adds 'name' as a member to the domain." });
   lines += ({ "\tdel [name] : removes 'name' as a member from the domain." });

   if (query_admin(this_player())) {
      lines += ({ "\tpro [name] : promote 'name' to admin for the domain." });
      lines += ({ "\tdem [name] : demote 'name' from admin to normal member " +
         "of the domain." });
   }
   lines += ({ "\tlist       : list members of the domain." });
   lines += ({ "\tleave      : leave the named domain (if you are a member)" });

   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tdomain boothill list" });
   lines += ({ "\tdomain boothill add sirdude" });
   lines += ({ "\tdomain boothill pro sirdude" });
   lines += ({ "\tdomain boothill del sirdude" });
   lines += ({ "\tdomain boothill list sirdude" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "alias");
   add_also("player", "emote");
   add_also("player", "help");

   add_also("wiz", "aliasadm");
   add_also("wiz", "emoteadm");

   add_also("admin", "cmdadm");
   add_also("admin", "coloradm");
   add_also("admin", "emotediff");
   add_also("admin", "rehash");
}

static int action_list_domains(void) {
   string *dn, name;
   int i, sz;

   dn = DOMAIN_D->query_domains();
   name = this_player()->query_name();

   write("We know about the following domains:\n");

   sz = sizeof(dn);
   for (i = 0; i < sz; i++) {
      string opt;
      if (DOMAIN_D->query_domain_admin(dn[i], name)) {
         opt = " (admin)";
      } else if (DOMAIN_D->query_domain_member(dn[i], name)) {
         opt = " (member)";
      } else {
         opt = "";
      }
      write(dn[i] + opt + "\n");
   }
   return 1;
}

static string format_member_display(string member, string domain) {
   if (DOMAIN_D->query_domain_admin(domain, member)) {
      member += "(admin)";
   }
   return member;
}

static int action_list_members(string domain) {
   if (!domain) {
      notify_fail("No domain given.");
   } else if (!DOMAIN_D->is_domain(domain)) {
      notify_fail("No such domain:" + domain);
   } else {
      string *members;

      members = DOMAIN_D->query_domain_members(domain);
      if (sizeof(members)) {
         write("Domain " + domain + " has the following members:\n" +
            implode(map_array(members, "format_member_display",
                  this_object(), domain), ", ") + ".\n");
      } else {
         write("Domain " + domain + " has no members.\n");
      }
      return 1;
   }
   return 0;
}

static int action_del_member(string domain, string member) {
   if (!domain || !strlen(domain)) {
      notify_fail("Domain name missing");
   } else if (!member || !strlen(member)) {
      notify_fail("Member name missing");
   } else if (!DOMAIN_D->is_domain(domain)) {
      notify_fail("Domain " + domain + " does not exist");
   } else if (!DOMAIN_D->query_domain_member(domain, member)) {
      notify_fail(member + " is not a member of " + domain);
   } else {
      int i;
      string str;

      str = catch(i = DOMAIN_D->remove_domain_member(domain, member));
      if (str) {
         notify_fail(str);
      } else {
         notify_fail("Unknown error");
      }
      return i;
   }
   return 0;
}

static int action_add_member(string domain, string member) {
   if (!domain || !strlen(domain)) {
      notify_fail("Domain name missing");
   } else if (!member || !strlen(member)) {
      notify_fail("Member name missing");
   } else if (!DOMAIN_D->is_domain(domain)) {
      notify_fail("Domain " + domain + " does not exist");
   } else if (!query_wizard(member)) {
      notify_fail(member + " is not a wizard");
   } else if (DOMAIN_D->query_domain_member(domain, member)) {
      notify_fail(member + " is already a member of " + domain);
   } else {
      int i;
      string str;

      str = catch(i = DOMAIN_D->add_domain_member(domain, member));
      if (str) {
         notify_fail(str);
      } else {
         notify_fail("Unknown error");
      }
      return i;
   }
   return 0;
}

static int action_promote_member(string domain, string name) {
   if (DOMAIN_D->query_domain_member(domain, name)) {
      DOMAIN_D->promote_domain_member(domain, name);
      return 1;
   } else {
      notify_fail(name + " is not a member of " + domain + "\n");
      return 0;
   }
}

static int action_demote_member(string domain, string name) {
   if (DOMAIN_D->query_domain_admin(domain, name)) {
      DOMAIN_D->demote_domain_member(domain, name);
      return 1;
   } else {
      notify_fail(name + " is not a domain admin for " + domain + "\n");
      return 0;
   }
}

static int query_domain_admin(string domain, object player) {
   return (query_admin(player) ||
      DOMAIN_D->query_domain_admin(domain, player->query_name()));
}

static void main(string arg) {
   string dname, cmd, uname;
   int r;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(arg) || sscanf(arg, "-%s", cmd)) {
      this_player()->more(usage());
      return;
   }

   if ((sscanf(arg, "%s %s %s", dname, cmd, uname) != 3) &&
      (sscanf(arg, "%s %s", dname, cmd) != 2)) {
      if (arg == "list") {
         action_list_domains();
      } else {
         this_player()->more(usage());
      }
      return;
   }

   if (!DOMAIN_D->is_domain(dname)) {
      if (cmd[..2] == "add") {
         if (query_admin(this_player())) {
            string path;
            path = DOMAINS_DIR + "/" + dname;

            if (file_exists(path) != 0) {
                  notify_fail("Directory for domain " + dname +
                     " does not exist.");
                  r = 0;
            }

            if (DOMAIN_D->add_domain(dname)) {
               r = unguarded("action_add_member", dname, uname);
               if (!r) {
                  r = action_promote_member(dname, uname);
               } else {
                  notify_fail("Error adding " + uname + " to domain " +
                     dname);
                  r = 0;
               }
            } else {
              notify_fail("Error trying to create domain: " + dname);
              r = 0;
            }
         } else {
            notify_fail("You are not an admin you can not add that domain.");
            r = 0;
         }
      } else {
         notify_fail("Domain " + dname + " does not exist, use 'domain list' " +
            "for a list of domains.\n");
         r = 0;
      }
   } else if (strlen(cmd) < 3) {
      notify_fail("Unknown command " + cmd);
      r = 0;
   } else {
      switch (cmd[..2]) {
         case "add":
            if (query_domain_admin(dname, this_player())) {
               r = unguarded("action_add_member", dname, uname);
            } else {
               notify_fail("You are not an admin for that domain.");
               r = 0;
            }
            break;
         case "del":
            if (query_domain_admin(dname, this_player())) {
               r = unguarded("action_del_member", dname, uname);
            } else {
               notify_fail("You are not an admin for that domain.");
               r = 0;
            }
            break;
         case "lis":
            r = action_list_members(dname);
            if (r) {  /* No need to continue so lets return */
               return;
            }
            break;
         case "lea":
            r = action_del_member(dname, this_player()->query_name());
            break;
         case "pro":
            if (query_admin(this_player())) {
               r = action_promote_member(dname, uname);
               break;
            }
         case "dem":
            if (query_admin(this_player())) {
               r = action_demote_member(dname, uname);
               break;
            }
         default:
            notify_fail("Unknown command " + cmd);
            r = 0;
            break;
      }
   }

   if (!r) {
      string *err, str;

      str = query_notify_fail();

      if (!empty_str(str)) {
         err = ({ ANSI_D->parse_colors("%^RED%^BOLD%^Error: " + str + 
            "%^RESET%^") });
      } else {
         err = ({ });
      }
      this_player()->more(err);
   } else {
      write("Ok.\n");
   }
}
