#include "copy.h"

void showHelp()
{
    printf("syntax: [command] folder-to-copy [additional args]\n");
    printf("-l [path]\t\tlocation where to copy\n");
    printf("-c\t\t\tit will only copy its contents (dir will be excluded)\n");
    printf("-h\t\t\tshows this help\n");
}

int main(int argc, char *argv[])
{
    switch (argc) {
        case 1:
            showHelp();
            return SUCCES;
        case 2:
            if (argv[1][0] == '-') {
                if (argv[1][1] != 'g') {
                    showHelp();
                    if (argv[1][1] == 'h' && !argv[1][2])
                        return SUCCES;
                    else
                        return error("WRONG SYNTAX", "", WRONG_SYNTAX);
                }
                return error("OPTION UNAVAILABLE", "GUI NOT READY YET", NOT_READY);
            }
            return copy(argv[1], NULL, true);
        case 3:
            if (argv[2][0] == '-' && argv [2][1] == 'c') {
                return copy(argv[1], argv[2], false);
            }
            showHelp();
            return error("WRONG SYNTAX", "", WRONG_SYNTAX);
        case 4:
            if (argv[1][0] != '-') {
                if (argv[2][0] == '-' && argv[2][1] == 'l' && !argv[2][2]) {
                    if (argv[3][0] != '-') {
                        return copy(argv[1], argv[3], true);
                    }
                }
            }
            showHelp();
            return error("WRONG SYNTAX", "", WRONG_SYNTAX);
        case 5:
            if (argv[1][0] != '-') {
                if (argv[2][0] == '-' && argv[2][1] == 'l' && !argv[2][2]) {
                    if (argv[3][0] != '-') {
                        if (argv[4][0] == '-' && argv[4][1] == 'c' && !argv[2][2]) {
                            return copy(argv[1], argv[3], false);
                        }
                    }
                }
            }
            showHelp();
            return error("WRONG SYNTAX", "", WRONG_SYNTAX);
    }
    return 0;
}
