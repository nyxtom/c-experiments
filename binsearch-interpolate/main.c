#include <stdio.h>
#include <assert.h>

size_t find(int *arr, int len, int item) {
    size_t l = 0;
    size_t r = len - 1;

    while (l <= r) {
        double percent = 0.5; // augment for interpolate search
        size_t mid = l + (r - l) * percent;
        if (arr[mid] == item) {
            return mid;
        } else if (arr[mid] < item) {
            l = mid + 1;
        } else if (arr[mid] > item) {
            r = mid - 1;
        }
    }

    return -1;
}

size_t interpolate(int *arr, int len, int item) {
    size_t l = 0;
    size_t r = len - 1;

    while (l <= r) {
        if (item < arr[l] || item > arr[r]) {
            break;
        }
        // calculate percent through r-l
        // y - y1 = (x-x1) * (y2-y1)/x2-x1

        double dy = item - arr[l];
        double dx = arr[r] - arr[l];
        double percent = dy / dx;

        size_t mid = l + (r - l) * percent;
        if (arr[mid] == item) {
            return mid;
        } else if (arr[mid] < item) {
            l = mid + 1;
        } else if (arr[mid] > item) {
            r = mid - 1;
        }
    }

    return -1;
}

int main() {
    int arr[] = { 1, 2, 3, 4, 5 };
    assert(find(arr, 5, 4) == 3);
    assert(find(arr, 5, 2) == 1);
    assert(find(arr, 5, 5) == 4);
    assert(find(arr, 5, 8) == -1);

    assert(interpolate(arr, 5, 4) == 3);
    assert(interpolate(arr, 5, 2) == 1);
    assert(interpolate(arr, 5, 5) == 4);
    assert(interpolate(arr, 5, 8) == -1);
}

