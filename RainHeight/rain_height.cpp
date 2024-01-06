#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int *firstWall = new int[n], *end = firstWall + n, *lastWall = end - 1;
    for (int *wall = firstWall; wall != end; wall++)
        cin >> *wall;

    int waterTrapped = 0;
    int leftMax = *firstWall;
    for (int *wall = firstWall; wall != lastWall; wall++) {
        int rightMax = 0;
        // Find the maximum height to the left of the current wall
        if(leftMax < *wall)
            leftMax = *wall;
        // Find the maximum height to the right of the current wall
        for (int *r = wall + 1; r != end; r++)
            rightMax = max(rightMax, *r);

        // Calculate the trapped water for the current wall
        int minHeight = min(leftMax, rightMax);
        if (minHeight > *wall) {
            waterTrapped += minHeight - *wall;
        }
    }

    cout << waterTrapped;

    return 0;
}