#include <stdio.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int minMax(int depth, int nodeIndex, int isMax, int values[], int height) {
    // If we reach a leaf node
    if (depth == height)
        return values[nodeIndex];

    if (isMax)
        return MAX(minMax(depth + 1, nodeIndex * 2, 0, values, height),
                   minMax(depth + 1, nodeIndex * 2 + 1, 0, values, height));
    else
        return MIN(minMax(depth + 1, nodeIndex * 2, 1, values, height),
                   minMax(depth + 1, nodeIndex * 2 + 1, 1, values, height));
}

int main() {
    int height;
    
    printf("Enter the height of the tree: ");
    scanf("%d", &height);
    
    int leafCount = 1 << height;  // Total number of leaf nodes = 2^height
    int values[leafCount];
    
    printf("Enter the values of the %d leaf nodes:\n", leafCount);
    for (int i = 0; i < leafCount; i++) {
        printf("Value of leaf node %d: ", i + 1);
        scanf("%d", &values[i]);
    }

    int result = minMax(0, 0, 1, values, height);
    
    printf("The optimal value is: %d\n", result);
    return 0;
}
