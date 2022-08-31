#include <stdbool.h>
#include <stdlib.h>

struct User {
    char *name;
    char *email;
    struct {
        bool subscribed;
        uint64_t updated;
    } settings;
};


int main() {
    struct User user = { "Tom", "nyxtom@gmail.com", { true, 0 } };
}
