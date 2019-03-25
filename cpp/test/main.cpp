#include <iostream>
#include <bitset>
using namespace std;

int main()
{
    uint32_t a;
    uint32_t b;
    a = static_cast<uint32_t>(1)<<10 - 1 ;
    uint32_t state = a;
    b = 0;
    uint16_t c = 13;
    uint16_t d = 15;
    uint16_t total = 20;
    uint32_t newA = b + c * (a-b + 1) / total;
    uint32_t newB = b + d * (a-b + 1) / total;
    uint32_t index = 19;
    index += 1;
    uint32_t index_ = index - (index & ( - index));
    cout<< bitset<32>(index)<<endl << bitset<32>(index_);
    //cout << bitset<32>(newA)<< "  " <<newA<<endl;
    //cout << bitset<32>(newB)<< "  " <<newB<<endl;
}
