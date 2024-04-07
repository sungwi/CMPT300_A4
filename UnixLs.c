#include "UnixLs.h"

// -i
void i_cmd(const char* dirname) {
    DIR* dir; // dirent.h
    struct dirent *dp;
    struct stat buf; // stat.h

    dir = opendir(dirname);
    if(dir == NULL) {
        perror("error: opendir");
        return;
    }

    while ((dp = readdir(dir)) != NULL) {
        char* dName = dp->d_name;
        if (lstat(dName, &buf) == -1) {
            perror("error: lstat");
            return;
        } 
        printf("inonumber: %lu\n", (unsigned long)buf.st_ino);
    }
    closedir(dir);
    return;
}

void mode_to_string(mode_t st_mode, char str[11]) {
    strcpy(str, "-----------");
    
    // file type
    if (S_ISDIR(st_mode)) str[0] = 'd';
    if (S_ISREG(st_mode)) str[0] = '-';
    if (S_ISLNK(st_mode)) str[0] = 'l';

    // owner permission
    if (S_IRUSR & st_mode) str[1] = 'r'; // read
    if (S_IWUSR & st_mode) str[2] = 'w'; // write
    if (S_IXUSR & st_mode) str[3] = 'x'; // execute
    
    // group permission
    if (S_IRGRP & st_mode) str[4] = 'r';
    if (S_IWGRP & st_mode) str[5] = 'w';
    if (S_IXGRP & st_mode) str[6] = 'x';

    // ? other
    if (S_IROTH & st_mode) str[7] = 'r';
    if (S_IWOTH & st_mode) str[8] = 'w';
    if (S_IXOTH & st_mode) str[9] = 'x';

    // last null terminator
    str[10] = '\0';
    
}

// -l
void l_cmd(const char* dirname) {
    DIR* dir; // dirent.h
    struct dirent *dp;
    struct stat buf; // stat.h

    dir = opendir(dirname);
    if(dir == NULL) {
        perror("error: opendir");
        return;
    }

    while ((dp = readdir(dir)) != NULL) { // readdir returns the pointer to the entry of directory. return 0 if sucess, NULL o.w.
        // if (dirname[strlen(dirname) - 1] == '/') {
        //     snprintf(fullPath, sizeof(fullPath), "%s%s", dirname, dp->d_name);
        // } else {
        //     snprintf(fullPath, sizeof(fullPath), "%s/%s", dirname, dp->d_name);
        // }

        // if (lstat(fullPath, &buf) == -1) {
        //     perror("error: lstat");
        //     continue;
        // }
        char* dName = dp->d_name;
        if (lstat(dName, &buf) == -1) {
            perror("error: lstat");
            return;
        } 

        // st_mode: read/write/execte permission of the file
        char st_mode[11];
        mode_to_string(buf.st_mode, st_mode);
        
        // st_uid: the user name of the file owner
        struct passwd* pwd = getpwuid(buf.st_uid); 
        // st_gid: the group name the owner belongs to
        struct group* grp = getgrgid(buf.st_gid);

        // st_mtime: the date and time the when the file was last modified
        char stMtime[20];
        strftime(stMtime, sizeof(stMtime), "%b %d %Y %H:%M", localtime(&buf.st_mtime));

        // print 
        printf("%s %4lu %-8s %-8s %10ld %s %s\n",
                st_mode,
                (unsigned long)buf.st_nlink,
                pwd->pw_name,
                grp->gr_name,
                (long)buf.st_size,
                stMtime,
                dp->d_name);
    }
    closedir(dir);
    return;
}
