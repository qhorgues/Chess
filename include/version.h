#ifndef VERSION_H
#define VERSION_H

#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 2

typedef struct Chess_version
{
    int major;
    int minor;
    int patch;
} Chess_version;

static inline void getVersion(Chess_version *const version)
{
    version->major = VERSION_MAJOR;
    version->minor = VERSION_MINOR;
    version->patch = VERSION_PATCH;
}

#endif
