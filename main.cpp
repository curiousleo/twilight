#include "vector3d.hh"
#include "physics.hh"

using namespace std;

int main(void) {
    unsigned int i;
    System s;

    cin >> i;

    for (unsigned int j = 0; j != i; j++) {
        cin >> s;
    }

    cout << s << endl;
    return 0;
}
