#include<iostream>
#include<cstdlib>
#include"BitString.hpp"

using namespace std;

// -Initializes size as 0 and bitsting as {0}.
BitString::BitString() {
    bit_string = new char[1];
    bit_string[0] = 0;
    size = 0;
}

// -bit_str <- str; size <- sz;
BitString::BitString(char *bit_str, int sz) {
    if(bit_str == NULL) {
        bit_string = new char[1];
        bit_string[0] = 0;
        size = 0;
    } else {
        bit_string = new char[sz + 1];
        int i = 0; // -Coping the hole array, not the reference.
        while(i < sz) {
            bit_string[i] = bit_str[i];
            i++;
        }
        if(i == 0) {
            delete [] bit_string;
            bit_string = new char[1];
            bit_string[0] = 0;
            size = 0;
        } else {
            bit_string[i] = 0;
        }
        size = sz;
    }
}

// -Print
void BitString::print() {
    // ---------- size in bytes. size & (FFFFFFFF << 3) == size / 8.
    int i, j = 0, k = 0;
    char bit8 = 0x80, tmp = bit_string[0];
    for(i = 0; i < size; i++) {
        if(j == 8) {
            j = 0;
            tmp = bit_string[++k];
        }
        if((tmp & bit8 >> j) != 0) cout << '1';
        else cout << '0';
        j++;
    }
}

// -Prints the bit string and a jump line.
void BitString::println() {
    print();
    cout << '\n';
}

int BitString::find(char *bit_str, int sz) {
    if(bit_str == NULL || sz <= 0) throw "Invalid arguments string.";

    int dif_size = size - sz;
    // -The bit string that we are looking for is bigger that the one we are
    //  looking in; returning -1.
    if(dif_size < 0) return -1;

    // -Using the naive approach for pattern matching.
    char bit8 = 0x80; // 1000,0000.
    int i = 0, j = 0, size_bytes, padding_size;

    // -Smallest amount of bytes that can contain the bit string.
    // -Equivalent to size / 8 + 1.
    size_bytes = size & (0xFFFFFFFF << 3) + 1;
    // -Smallest non-negative integer k that makes size + k a multiple of 8.
    // -Equivalent to 8 - size % 8.
    padding_size = 8 - (size & 7);

    while(i < dif_size) {
        // -Comparing the strings starting at the index i.
        for(j = 0; j < sz; j++) {
            // -If the bits are different, stop comparing
            //  and increment i.
            if(get_bit(i + j) != get_bit(j, bit_str)) {
                i++;
                break;
            }
        }
        // -Full coincidence, returning i.
        if(j == sz) return i;
    }
    // -Impossible to find the desired string.
    return -1;
}

BitString::~BitString() {
    if(bit_string != NULL) delete[] bit_string;
}

// -Returns the bit of bit_string at the given index.
char BitString::get_bit(int index) {
    if(index < 0 || index  >= size)throw "Invalid index";

    int bit8 = 0x80; // 1000,0000.
    char bit;

    // -Extracting the bit.
    // -Isolating the byte where the bit is. Notice that
    //  index & (0xFFFFFFFF << 3) == index / 8;
    bit = bit_string[index & (0xFFFFFFFF << 3)];
    // -Getting the bit. Notice that index & 7 == index % 8.
    bit &= bit8 >> (char)(index & 7);

    if(bit != 0) return 1;
    return 0;
}

// -Returns the bit of bit_str at the given index.
char BitString::get_bit(int index, char *bit_str) {
    // -For now we don't have range checking.
    int bit8 = 0x80; // 1000,0000.
    char bit;

    // -Extracting the bit.
    // -Isolating the byte where the bit is. Notice that
    //  index & (0xFFFFFFFF << 3) == index / 8;
    bit = bit_str[index & (0xFFFFFFFF << 3)];
    // -Getting the bit. Notice that index & 7 == index % 8.
    bit &= bit8 >> (char)(index & 7);

    if(bit != 0) return 1;
    return 0;
}

