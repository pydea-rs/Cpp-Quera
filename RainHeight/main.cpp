#include <iostream>

using namespace std;

int min(int a, int b, int c) {
    return a <= b ? (a <= c ? a : c)
                    : (b <= c ? b : c);
}
int main() {
    int n;
    cin >> n;
    int *firstWall = new int[n];
    int *lastWall = firstWall + n - 1, *prevWall = firstWall, *nextWall = lastWall;
    int *wall = firstWall;
    {
        int input = 0;
        while(wall != lastWall + 1) {
            cin >> input;
            *(wall++) = input;

        }
    }
    wall = firstWall + 1; prevWall = firstWall;
    int result = 0;
    while (wall != lastWall) {

        nextWall = wall + 1;
        while(nextWall != lastWall && *nextWall < *wall) nextWall++;
        result += min(*prevWall, *wall, *nextWall);
        int diff = *nextWall - *wall;
        if(diff > 0)
            result += diff;

        if(*prevWall <= *wall)
            prevWall = wall;

        cout << result << endl;
        wall++;
    }
    cout << result;
}