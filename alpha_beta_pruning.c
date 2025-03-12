#include <stdio.h>
#include <limits.h>
#include <math.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

// Alpha-Beta Pruning function
int alphaBetaPruning(int depth, int nodeIndex, int isMaximizingPlayer, int values[], int alpha, int beta, int height) {
    // Base case: Leaf node is reached
    if (depth == height)
        return values[nodeIndex];

    if (isMaximizingPlayer) {
        int best = INT_MIN;

        // Recur for left and right children
        for (int i = 0; i < 2; i++) {
            int val = alphaBetaPruning(depth + 1, nodeIndex * 2 + i, 0, values, alpha, beta, height);
            best = max(best, val);
            alpha = max(alpha, best);

            // Alpha Beta Pruning
            if (beta <= alpha)
                break;
        }
        return best;
    } else {
        int best = INT_MAX;

        // Recur for left and right children
        for (int i = 0; i < 2; i++) {
            int val = alphaBetaPruning(depth + 1, nodeIndex * 2 + i, 1, values, alpha, beta, height);
            best = min(best, val);
            beta = min(beta, best);

            // Alpha Beta Pruning
            if (beta <= alpha)
                break;
        }
        return best;
    }
}

int main() {
    int height, numLeafNodes;

    // Taking user input for the height of the tree
    printf("Enter the height of the game tree: ");
    scanf("%d", &height);

    // Calculating the number of leaf nodes (2^height)
    numLeafNodes = pow(2, height);
    int values[numLeafNodes];

    // Taking user input for the leaf node values
    printf("Enter the %d leaf node values: ", numLeafNodes);
    for(int i = 0; i < numLeafNodes; i++) {
        scanf("%d", &values[i]);
    }

    // Performing Alpha-Beta Pruning
    int optimalValue = alphaBetaPruning(0, 0, 1, values, INT_MIN, INT_MAX, height);

    printf("The optimal value is: %d\n", optimalValue);

    return 0;
}
