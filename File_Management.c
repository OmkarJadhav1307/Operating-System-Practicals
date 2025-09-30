#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        write(2, "Usage: ./copy <source> <destination>\n", 37);
        return 1;
    }

    int src = open(argv[1], O_RDONLY);
    if (src < 0) {
        write(2, "Error opening source file\n", 26);
        return 1;
    }

    int dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest < 0) {
        write(2, "Error opening destination file\n", 31);
        close(src);
        return 1;
    }

    char buffer[1024];
    int n;
    while ((n = read(src, buffer, sizeof(buffer))) > 0) {
        write(dest, buffer, n);
    }

    close(src);
    close(dest);
    return 0;
}

