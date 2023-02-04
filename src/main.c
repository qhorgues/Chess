#include "log/log.h"


int main(void)
{
    open_log();

    int a = 12;
    test(STATUS, a == 12, "");

    close_log();
    return 0;
}