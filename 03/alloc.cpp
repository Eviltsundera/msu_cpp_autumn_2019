#include <cstdlib>
#include <cstdio>
#include <iostream>


class LinearAllocator
{
public:
    LinearAllocator(size_t maxSize) {
     if (!maxSize) {
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
    unsigned long long  offset;
    unsigned long long  totalSize;
};

int main(int argc, char *argv[]) {
    int size;
    sscanf(argv[1], "%d", &size);
    LinearAllocator allocator(size);

    int i = 2;
    while(i < argc) {
        std::string op = argv[i];
        i++;

        if (op == "alloc") {
            int n;
            sscanf(argv[i], "%d", &n);
            i++;
            if (!allocator.alloc(n)) {
                std::cout << "Failed to allocate memory\n";
            }
        }

        if (op == "reset") {
            allocator.reset();
        }
    }
    return 0;
}