#include <cstdlib>
#include <cstdio>
#include <iostream>

#define  ll long long 

class LinearAllocator
{
public:
    LinearAllocator(size_t maxSize) {
        if (maxSize < 0) {
            std::cout << "Unexpected argument\n";
            buf =  nullptr;
        } else if (!maxSize) {
            buf = nullptr;
        } else {
            buf = (char*)malloc(maxSize * sizeof(char));
        }

        totalSize = maxSize;
        offset = 0;
    }

    char *alloc(size_t size) {
        char *res;
        if (!buf || offset + size > totalSize) {
            std::cout << "Failed to allocate memory: ";
            if (!buf) std::cout << "your block does not exist\n";
            else std::cout << "out of limit\n";
            return nullptr;
        }

        res = buf + offset;
        offset += size;
        return res;
    }

    void reset() {
        offset = 0;
    }

    ~LinearAllocator() {
        if (buf) {
            free(buf);
        }
    }
private:
    char *buf;
    unsigned ll offset;
    unsigned ll totalSize;
};

int main(int argc, char *argv[]) {
    int i = 1;
    int n;
    std::sscanf(argv[i], "%d", &n);
    i++;
    LinearAllocator allocator(n);
    while(i < argc) {
        char *op = argv[i];
        i++;
        if (!strcmp(op, "alloc")) {
            int m;
            std::sscanf(argv[i], "%d", &m);
            allocator.alloc(m);
        }

        if (!strcmp(op, "reset")) {
            allocator.reset();
        }
    }
    return 0;
}