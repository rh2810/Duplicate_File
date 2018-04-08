#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_COPIES 100 // maximum # of files that a user can duplicate at a time

int file_copies = 0; // keep track of the number of copies in the current folder

void copy_file(FILE *fp, long characters, char *output); // initializer function

/**
 * Take an input file, an output file, and optionally,
 * the number of copies to be made of the output file.
 * The result of running the program should be 1 or more
 * copies of the input file under the same or a different
 * name (output file)
 *
 * @param argc number of arguments taken from command line
 * @param argv arguments taken from the command line:
 *          [] - required fields
 *          ** - optional fields
 *        ./[program_executable] [input_file] [output_file] *number_of_copies*
 *        e.g. ./clone_multi input.txt output.txt 5
 * @return 0 if successful, -1 otherwise
 */
int main(int argc, char *argv[]) {
    FILE *fp = NULL;      // used to open file streams
    char c;               // used for keeping track of the current character in the input file
    long cnum = 0;        // total number of characters in the input file
    char base_name[1000]; // the name of the original output file, passed by user
    char confirm[50];     // used for prompting the user for confirmation to run the program
    int copies = 1;       // base number of copies

    // the user must give at least two arguments through the command line
    if (argc < 3) {
        printf("Error: Not enough arguments\n");
        return -1;
    }

    // the user must provide an existing, valid input file
    if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("Error: input file does not exist.\n");
        return -1;
    }

    // for multiple copies
    if (argc >= 4) {
        // converts a string to a long and stores it in a variable
        copies = strtol(argv[3], (char **) NULL, 10);
    }

    // count the number of characters in the file
    while ((c = fgetc(fp)) != EOF) {
        cnum++;
    }

    // prompt the user until a valid input is entered ('yes' or 'no')
    while (1) {
        printf("WARNING: Any files in this directory with the same name as your "
                       "output file will be OVERWRITTEN.\n");
        printf("Do you wish to continue? [yes, no]\n");
        fgets(confirm, 20, stdin);

        // remove new line characters
        confirm[strcspn(confirm, "\n")] = '\0';

        // break out of the loop if the user enters 'yes'
        if (strcmp(confirm, "yes") == 0 || strcmp(confirm, "Yes") == 0) {
            break;
        }
        // exit the program if the user enters 'no'
        if (strcmp(confirm, "no") == 0 || strcmp(confirm, "No") == 0) {
            fclose(fp);
            printf("Exiting program.\n");
            return 0;
        }
    }

    // create copies of the input file
    for (int i = 0; i < copies; ++i) {
        // it's good to have a limit so that the user doesn't
        // do anything crazy (like making 10,000+ copies of a file)
        if (i >= MAX_COPIES) {
            break;
        }
        // seek to the beginning of the file (offset 0)
        fseek(fp, 0, SEEK_SET);
        // save the output file as the original output filename
        strcpy(base_name, argv[2]);
        // determine if the name of the input file is the same as the output file
        // if so, generate a filename with a modified name (<filename>(1).<ext>)
        if((strcmp(argv[1], argv[2]) == 0) && file_copies < 1) {
            file_copies++;
        }
        // call the helper function, which copies the file
        copy_file(fp, cnum, base_name);
    }

    // close the file stream
    fclose(fp);

    return 0;
}

/**
 * Function makes a copy of the file passed to it.
 *
 * @param fp_in the file stream of the output file
 * @param characters the number of characters in the input file
 * @param output the name of the output file
 */
void copy_file(FILE *fp_in, long characters, char *output) {
    char line[characters]; // store each line from the output file
    FILE *fp_out = NULL; // generate file descriptor
    char *name = output; // the name of the output file
    char buf[200]; // buffer for output file
    char file_ext[50] = ""; // output file extension
    int k = 0; // incrementation variable

    // copy name into buffer
    strcpy(buf, name);

    // check that at least one copy needs to be made
    if (file_copies > 0) {
        // check each character in the file name
        for (int i = 0; i < strlen(name); ++i) {
            // typically indicates extension
            if (name[i] == '.') {
                // store the file extension in a new variable (char array/ string)
                for (int j = i; j < strlen(name); ++j, ++k) {
                    file_ext[k] = name[j];
                }
                // null terminate
                name[i] = '\0';
                file_ext[k] = '\0';

                break;
            }
        }

        // generate the new output file name
        // number given according to number of copies
        sprintf(buf, "(%d)%s", file_copies, file_ext);
        strcat(name, buf);
    }

    // number of copies currently made
    file_copies++;

    // open/create a file with the output file name
    // along with writing privileges
    fp_out = fopen(name, "w+");

    // copy the contents of the input file into the output file
    while (fgets(line, characters, fp_in) != NULL) {
        fwrite(line, strlen(line), 1, fp_out);
    }

    // close the output file
    fclose(fp_out);
}
