inherit "/std/body/experience";
inherit "/std/body/size";
inherit "/std/body/money";
inherit "/std/body/stats"; 
inherit "/std/body/hit_points"; 
inherit "/std/body/skills";
inherit hb "/std/body/heart_beat"; 
inherit "/std/body/armor"; /* Added by Fudge */
inherit "/std/body/weapon";   /* Added by Fudge */
inherit "/std/combat";
inherit "/std/body/gender";
inherit "/std/body/race";
inherit "/std/body/snoop"; /* Added by Fudge */

void create( void )
{
  hb::create();
  equipment = ([ ]);
  wielding = ({ });
}

