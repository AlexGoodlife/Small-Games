#ifndef commands_h
#define commands_h


extern void command_look(const char * subject, Location *location);
extern void command_go(const char *subject, Player *player);
extern void command_talk(const char * subject, Player *player);
extern int command_fight(const char * subject, Player *player);
extern void check_questlog(Player *player);
extern void help_command(void);


#endif