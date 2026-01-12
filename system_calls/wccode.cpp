#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cctype>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    int fd;
    char ch;
    int lines = 0, words = 0, chars = 0;
    bool inWord = false;

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    while (read(fd, &ch, 1) > 0)
    {
        chars++;

        // Count lines
        if (ch == '\n')
            lines++;

        // Word detection logic
        if (isspace(ch)) {
            if (inWord) {
                words++;
                inWord = false;
            }
        } else {
            inWord = true;
        }
    }

    // If file ends while still in a word
    if (inWord)
        words++;

    close(fd);

    cout << "Lines: " << lines << endl;
    cout << "Words: " << words << endl;
    cout << "Characters: " << chars << endl;

    return 0;
}
