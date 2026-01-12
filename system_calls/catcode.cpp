#include <iostream>
#include <cstdio>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    fclose(fp);
    return 0;
}



// #include <iostream>
// #include <cstdio>
// using namespace std;

// int main(int argc, char *argv[])
// {
//     if (argc < 2) {
//         cerr << "Usage: " << argv[0] << " <filename>\n";
//         return 1;
//     }
// 
//     FILE *fp = fopen(argv[1], "r");
//     if (fp == NULL) {
//         perror("fopen");
//         return 1;
//     }
// 
//     char buffer[1024];
//     size_t bytes;
// 
//     while ((bytes = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
//         fwrite(buffer, 1, bytes, stdout);
//    }
// 
//     fclose(fp);
//    return 0;
//}
