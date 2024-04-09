#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <string.h>

void i_cmd(const char* dirname);
void l_cmd(const char* dirname);
void mode_to_string(mode_t, char[]);