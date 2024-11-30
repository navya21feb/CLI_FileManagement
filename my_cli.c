#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

void log_command(const char *command) {
    FILE *history_fp = fopen("command_history.txt", "a");
    if (history_fp != NULL) {
        fprintf(history_fp, "%s\n", command);
        fclose(history_fp);
    } else {
        perror("Error logging command");
    }
}

void create_file(const char *filename) {
    FILE *test_fp = fopen(filename, "r");
    if (test_fp != NULL) {
        fclose(test_fp); // Close the file if it exists
        printf("Error: File '%s' already exists.\n", filename);
        return;
    }

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error creating file");
        exit(1);
    }
    fclose(fp);
    printf("File created successfully: %s\n", filename);
    log_command("create");
}

void delete_file(const char *filename) {
    if (remove(filename) != 0) {
        perror("Error deleting file");
    } else {
        printf("File deleted successfully: %s\n", filename);
        log_command("delete");
    }
}

void view_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    fclose(fp);
    log_command("view");
}

void write_file(const char *filename) {
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return;
    }

    char content[256];
    printf("Enter content to add to the file (end with a newline):\n");
    fgets(content, sizeof(content), stdin);

    fprintf(fp, "%s", content);
    fclose(fp);
    printf("Content added to file: %s\n", filename);
    log_command("write");
}

void rename_file(const char *oldname, const char *newname) {
    if (rename(oldname, newname) == 0) {
        printf("File renamed successfully from %s to %s\n", oldname, newname);
        log_command("rename");
    } else {
        perror("Error renaming file");
    }
}

void move_file(const char *filename, const char *new_location) {
    char destination[512];
    snprintf(destination, sizeof(destination), "%s/%s", new_location, filename);

    // Open source file
    FILE *src = fopen(filename, "rb");
    if (src == NULL) {
        perror("Error opening source file");
        return;
    }

    // Open destination file
    FILE *dest = fopen(destination, "wb");
    if (dest == NULL) {
        perror("Error opening destination file");
        fclose(src);
        return;
    }

    // Copy file contents from src to dest
    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    // Close files
    fclose(src);
    fclose(dest);

    // Remove the original file
    if (remove(filename) == 0) {
        printf("File moved successfully to %s\n", new_location);
        log_command("move");
    } else {
        perror("Error deleting original file after moving");
    }
}
void search_file(const char *filter) {
    char command[512];
    snprintf(command, sizeof(command), "find . -name \"%s\"", filter);
    system(command);
    log_command("search");
}

void view_file_metadata(const char *filename) {
    char command[512];
    snprintf(command, sizeof(command), "stat %s", filename);
    system(command);
    log_command("view_metadata");
}

void copy_file(const char *filename, const char *new_location) {
    char command[512];
    snprintf(command, sizeof(command), "cp %s %s", filename, new_location);
    if (system(command) == 0) {
        printf("File copied successfully to %s\n", new_location);
        log_command("copy");
    } else {
        perror("Error copying file");
    }
}

void show_creation_date(const char *filename) {
    struct stat file_stat;
    if (stat(filename, &file_stat) == 0) {
        printf("File created on: %s", ctime(&file_stat.st_ctime));
    } else {
        perror("Error retrieving file creation date");
    }
    log_command("show_creation_date");
}

void count_words_in_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    int word_count = 0;
    char word[256];
    while (fscanf(fp, "%255s", word) == 1) {
        word_count++;
    }

    fclose(fp);
    printf("The file contains %d words.\n", word_count);
    log_command("count_words");
}

void parse_command(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <command> <filename> [<newname>/<new_location>]\n", argv[0]);
        return;
    }

    const char *command = argv[1];
    const char *filename = argv[2];

    if (strcmp(command, "create") == 0) {
        create_file(filename);
    } else if (strcmp(command, "delete") == 0) {
        delete_file(filename);
    } else if (strcmp(command, "view") == 0) {
        view_file(filename);
    } else if (strcmp(command, "write") == 0) {
        write_file(filename);
    } else if (strcmp(command, "rename") == 0 && argc == 4) {
        const char *newname = argv[3];
        rename_file(filename, newname);
    } else if (strcmp(command, "move") == 0 && argc == 4) {
        const char *new_location = argv[3];
        move_file(filename, new_location);
    } else if (strcmp(command, "search") == 0) {
        search_file(filename);
    } else if (strcmp(command, "view_metadata") == 0) {
        view_file_metadata(filename);
    } else if (strcmp(command, "copy") == 0) {
        const char *new_location = argv[3];
        copy_file(filename, new_location);
    } else if (strcmp(command, "show_creation_date") == 0) {
        show_creation_date(filename);
    } else if (strcmp(command, "count_words") == 0) {
        count_words_in_file(filename);
    } else {
        printf("Invalid command.\n");
    }
}

int main(int argc, char *argv[]) {
    parse_command(argc, argv);
    return 0;
}
