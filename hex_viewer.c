#include <stdio.h>
#include <stdlib.h>

void dump_hex(FILE *file) {
    unsigned char buffer[16];
    size_t bytes_read;
    long offset = 0;

    // Read file in chunks of 16 bytes
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        // Print offset in 8-digit hexadecimal format
        printf("%08lX: ", offset);

        // Print byte values in hex
        for (size_t i = 0; i < 16; i++) {
            if (i < bytes_read) {
                printf("%02X ", buffer[i]);
            } else {
                printf("   ");
            }
            
            // Add an extra space in the middle for readability (after 8 bytes)
            if (i == 7) {
                printf(" ");
            }
        }

        printf(" | ");

        // Print ASCII representation
        for (size_t i = 0; i < bytes_read; i++) {
            if (buffer[i] >= 32 && buffer[i] <= 126) {
                printf("%c", buffer[i]);
            } else {
                printf(".");
            }
        }

        printf("\n");
        offset += bytes_read;
    }
}

int main(int argc, char *argv[]) {
    // Check command-line arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    // Open file in binary read mode
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("Error: Could not open the specified file");
        return 1;
    }

    printf("=== Binary File Content Analysis: %s ===\n", argv[1]);
    dump_hex(file);

    // Close the file safely
    fclose(file);
    return 0;
}