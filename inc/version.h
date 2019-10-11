#include "_git.h"

#define RC_NUM_VERSION_MAJOR   0
#define RC_NUM_VERSION_MINOR   1
#define RC_NUM_VERSION_RELEASE 0
#define RC_NUM_VERSION_BUILD   GIT_COMMIT_COUNT

#define XSTR(s) STR(s)
#define STR(s)  #s

#define RC_STR_VERSION     XSTR(RC_NUM_VERSION_MAJOR) \
                       "." XSTR(RC_NUM_VERSION_MINOR) \
                       "." XSTR(RC_NUM_VERSION_RELEASE) \
                       "-" GIT_COMMIT_HASH
