#include <stdio.h>
#include <unistd.h>

int main() {
    if (access("/bin/ls", X_OK) == 0) {
        printf("/bin/ls is accessible and executable\n");
    } else {
        perror("access");
    }
    return 0;
}
