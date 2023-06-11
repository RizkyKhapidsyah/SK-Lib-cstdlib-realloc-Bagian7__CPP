#include <cassert>
#include <cstdlib>
#include <new>
#include <conio.h>

/*
    Source by CPPReference (https://en.cppreference.com)
    Modified For Learn by RK
    I.D.E : VS2022
*/

class MallocDynamicBuffer {
    char* p;
public:
    explicit MallocDynamicBuffer(std::size_t initial = 0) : p(nullptr) {
        resize(initial);
    }

    ~MallocDynamicBuffer() { std::free(p); }

    void resize(std::size_t newSize) {
        if (newSize == 0) { // pemeriksaan ini tidak benar-benar diperlukan,
            std::free(p); // tetapi realloc ukuran nol tidak digunakan lagi di C
            p = nullptr;
        } else {
            if (void* mem = std::realloc(p, newSize)) {
                p = static_cast<char*>(mem);
            } else {
                throw std::bad_alloc();
            }   
        }
    }

    char& operator[](size_t n) { return p[n]; }
    char operator[](size_t n) const { return p[n]; }
};

int main() {
    MallocDynamicBuffer buf1(1024);
    buf1[5] = 'f';
    buf1.resize(10); // menyusut
    assert(buf1[5] == 'f');
    buf1.resize(1024); // tumbuh
    assert(buf1[5] == 'f');

    _getch();
    return 0;
}