// Text based rpg
// location.h

#ifndef location_h
#define location_h

extern void command_look(const char * subject, Player *player);
extern void command_go(const char *subject, Player *player);
extern void command_talk(const char * subject, Player *player);
extern int command_fight(const char * subject, Player *player);
extern void check_questlog(Player *player);
extern void tutorial_event(void);
extern void help_command(void);
extern Location locations[];
extern Quest quests[];


#define cemetery (locations + 0)
#define field (locations + 1)
#define forest (locations + 2)
#define end_of_locations  (locations + 3)





#endif