#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct State {
    int* buckets;
    int lastEpochSecs;
    int lastBucket;
    int total;
} State;

void timestep(State* state, bool increment) {
    int secs = (int)time(NULL);
    int bucket = secs % 60;

    if (state->lastBucket > -1) {
        int diff = secs - state->lastEpochSecs;
        if (diff >= 60) {
            // reset the memory block to all zeros
            memset((void*)state->buckets, 0, sizeof(state->buckets));
            state->total = 0;
        } else if (diff > 0) {
            if (state->lastBucket < bucket) {
                // reset zeros from lastBucket -> bucket/
                // only when diff is < 60 and lastBucket < bucket
                for (int i = state->lastBucket + 1; i <= bucket; i++) {
                    int item = state->buckets[i];
                    state->buckets[i] = 0;
                    // alternatively use vector intrinsics to speed up accumulator here
                    // combined with a memset from the pointer offsets
                    // then subtract the total (8 x 32bit ints = accumulator)
                    state->total -= item;
                }
            } else {
                // otherwise, continue from lastBucket to end, 0 to new bucket
                for (int i = 0; i <= bucket; i++) {
                    int item = state->buckets[i];
                    state->buckets[i] = 0;
                    // similar alternative use of intrinsics could be done here
                    state->total -= item;
                }
                // from lastbucket to end
                for (int i = state->lastBucket + 1; i < 60; i++) {
                    int item = state->buckets[i];
                    state->buckets[i] = 0;
                    state->total -= item;
                }
            }
        }
    }

    if (increment) {
        state->buckets[bucket]++;
        state->total++;
    }
    state->lastBucket = bucket;
    state->lastEpochSecs = secs;

    printf("total %d\n", state->total);
    printf("bucket %d\n", state->lastBucket);
    printf("lastEpochSecs %d\n", state->lastEpochSecs);
}

void request(State* state) {
    timestep(state, true);
}

int total(State* state) {
    timestep(state, false);
    return state->total;
}

int main() {
    State* state = (State*)malloc(sizeof(State));
    state->total = 0;
    state->lastEpochSecs = -1;
    state->lastBucket = -1;
    state->buckets = (int*)calloc(60, sizeof(int));

    request(state);

    free(state->buckets);
    free(state);
    return 0;
}
