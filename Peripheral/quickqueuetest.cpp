#include <queue>
#include "QuickQueue.h"
#include <unistd.h>

using namespace std;

#define TEST_PORTION 2

int main(int argc, char* argv[]) {
    const int m = 1024*1024*256; // 256MB of data

#if TEST_PORTION == 1
    QuickQueue qq;

    // 4 bytes / iteration
    for(int i = 0; i < m; i++) {
        qq << i;
        qq >> i;
    }
#elif TEST_PORTION == 2

    queue<char> q;
    char c = 'A';

    for(int i = 0; i < m; i++) {
        q.push(c);
        q.pop();
    }

#endif // TEST_PORTION


}
