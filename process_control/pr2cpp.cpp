#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
    int i;
    for (i = 0; i < 4; i++){
        fork();
	cout<<i;
    }
    return 0;
}

