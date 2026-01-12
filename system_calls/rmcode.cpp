#include <iostream>
#include <unistd.h>
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    if (unlink(argv[1]) == 0) {
        cout << "File deleted successfully\n";
    } else {
        perror("unlink");
        return 1;
    }

    return 0;
}






// #include <iostream>
// #include <cstdio>
// using namespace std;

// int main(int argc, char *argv[])
//{
// if (argc < 2) {
//  cerr << "Usage: " << argv[0] << " <filename>\n";
//   return 1;
// }

// if (remove(argv[1]) == 0) {
//   cout << "File deleted successfully\n";
// } else {
//  perror("remove");
//    return 1;
// }
//
//  return 0;
//}
