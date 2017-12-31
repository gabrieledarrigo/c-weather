#include <stdio.h>
#include <stdlib.h>

char * read_file() {
    FILE * file;
    char * buffer = NULL;
    int size = 0;

    file = fopen("./data/city.list.json", "r+");

    if (file) {
        char temp;

        while ((temp = fgetc(file)) != EOF) {
            size++;
        }
    
        buffer = (char *) malloc((size + 1) * sizeof(char));
        rewind(file);
        fread(buffer, size, 1, file);
    } else {
        perror("Error: ");
    }

    fclose(file);
    return buffer;
}

int main() {
    char * data;
    data = read_file();

    printf("%s", data);

    return 0;
}
