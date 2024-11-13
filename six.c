#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAME_COUNT 10
#define MAX_PAGE_COUNT 100

int pageReferences[MAX_PAGE_COUNT];
int frames[MAX_FRAME_COUNT];
int pageCount, frameCount;

void printFrames(int frames[], int frameCount) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == -1) {
            printf("  ");
        } else {
            printf("%d ", frames[i]);
        }
    }
    printf("| ");
}

int findIndex(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;
}

int fcfsPageReplacement() {
    int pageFaults = 0;
    printf("FCFS Page Replacement Algorithm:\n");
    for (int i = 0; i < pageCount; i++) {
        int pageIndex = findIndex(frames, frameCount, pageReferences[i]);
        if (pageIndex == -1) {
            frames[pageFaults % frameCount] = pageReferences[i];
            pageFaults++;
        }
        printFrames(frames, frameCount);
    }
    return pageFaults;
}

int lruPageReplacement() {
    int pageFaults = 0;
    int time[MAX_FRAME_COUNT];
    printf("LRU Page Replacement Algorithm:\n");
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
        time[i] = 0;
    }
    for (int i = 0; i < pageCount; i++) {
        int pageIndex = findIndex(frames, frameCount, pageReferences[i]);
        if (pageIndex == -1) {
            int leastRecentlyUsedIndex = 0;
            int leastRecentlyUsedTime = time[0];
            for (int j = 1; j < frameCount; j++) {
                if (time[j] < leastRecentlyUsedTime) {
                    leastRecentlyUsedIndex = j;
                    leastRecentlyUsedTime = time[j];
                }
            }
            frames[leastRecentlyUsedIndex] = pageReferences[i];
            time[leastRecentlyUsedIndex] = i;
            pageFaults++;
        }
        time[pageIndex] = i;
        printFrames(frames, frameCount);
    }
    return pageFaults;
}

int optimalPageReplacement() {
    int pageFaults = 0;
    int nextUse[MAX_FRAME_COUNT];
    printf("Optimal Page Replacement Algorithm:\n");
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }
    for (int i = 0; i < pageCount; i++) {
        int pageIndex = findIndex(frames, frameCount, pageReferences[i]);
        if (pageIndex == -1) {
            int farthestReferenceIndex = 0;
            int farthestReferenceTime = -1;
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    farthestReferenceIndex = j;
                    break;
                }
                int nextReferenceTime = -1;
                for (int k = i + 1; k < pageCount; k++) {
                    if (pageReferences[k] == frames[j]) {
                        nextReferenceTime = k;
                        break;
                    }
                }
                if (nextReferenceTime == -1) {
                    farthestReferenceIndex = j;
                    break;
                }
                if (nextReferenceTime > farthestReferenceTime) {
                    farthestReferenceIndex = j;
                    farthestReferenceTime = nextReferenceTime;
                }
            }
            frames[farthestReferenceIndex] = pageReferences[i];
            nextUse[farthestReferenceIndex] = i;
            pageFaults++;
        }
        printFrames(frames, frameCount);
    }
    return pageFaults;
}

int main() {
    printf("Enter the number of pages: ");
    scanf("%d", &pageCount);

    if (pageCount <= 0 || pageCount > MAX_PAGE_COUNT) {
        printf("Invalid number of pages. Please enter a value between 1 and %d.\n", MAX_PAGE_COUNT);
        return 1;
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frameCount);

    if (frameCount <= 0 || frameCount > MAX_FRAME_COUNT) {
        printf("Invalid number of frames. Please enter a value between 1 and %d.\n", MAX_FRAME_COUNT);
        return 1;
    }

    printf("Enter the page reference string (space-separated): ");
    for (int i = 0; i < pageCount; i++) {
        scanf("%d", &pageReferences[i]);
    }

    int pageFaultsFCFS = fcfsPageReplacement();
    printf("\nTotal Page Faults (FCFS): %d\n\n", pageFaultsFCFS);

    int pageFaultsLRU = lruPageReplacement();
    printf("\nTotal Page Faults (LRU): %d\n\n", pageFaultsLRU);

    int pageFaultsOptimal = optimalPageReplacement();
    printf("\nTotal Page Faults (Optimal): %d\n", pageFaultsOptimal);

    return 0;
}

