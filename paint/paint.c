#include "paint.h"

char* color(char* text, char* color) {
    size_t size = strlen(color) + strlen(text) + strlen(RESET);
    char* result = calloc(size + 1, sizeof(char));

    if (result) {
        strcpy(result, color);
        strcat(result, text);
        strcat(result, RESET);
    }

    return result;
}

//int main() {
    //char* text = "HELLO";
    //char* color_text = color(text, FORE_RED);
    //printf("%s %s\n", color_text, "NORMAL");
    //printf("NEW LINE\n");
    //free(color_text);
    //return 0;
//}
