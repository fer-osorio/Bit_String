int FFFFFFFF = 0xFFFFFFFF; // -All the 32 bits of the integer are 1.

class BitString {
	// -We'll read bitstring in a similar manner that we reed a conventional
	//  string; the last element of the array will be zero marking the end of
	//  the array.
	// -The interpretation of the array is as a string of bits, not as a string
	//  characters.
	char *bit_string;

	// -Number of bits that the bit string contains.
	// -The size of the array bit_string in bits is always a multiple of eight,
	//  but the size of the bit string that we will consider has a size that is
	//  not necessarily a multiple of eight.
	int  size;

public:
	// -Initializes size as 0 and bitsting as {0}.
	BitString();

	// -bit_str <- str; size <- sz;
	BitString(char *bit_str, int sz);

	// -Print
	void print();

	// -Prints the bit string and a jump line.
	void println();

	// -Finds the first occurrence of bit_str in bit_string. If found returns
	//  the position of the first bit of the occurrence. If not returns -1.
	int find(char *bit_str, int sz);

private:
	~BitString();

	// -Returns the bit of bit_string at the given index.
	char get_bit(int index);

	// -Returns the bit of bit_str at the given index.
	char get_bit(int index, char *bit_str);
};