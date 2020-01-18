#include <iostream>
using namespace std;

/* https://hackaday.com/2019/06/19/abusing-a-cpus-adders-to-optimize-bit-counting/ */
unsigned char count_set_bits(unsigned int x) {
	unsigned char ret = 0;
	
	while(x) {
		ret++;
		x &= x - 1;
	} 
	
	return ret;
}

int main() {
	cout << "Count the set bits." << endl;
	cout << "value 0b110111000 -> " << (unsigned int)count_set_bits(0b110111000) << endl;
	return 0;
}
