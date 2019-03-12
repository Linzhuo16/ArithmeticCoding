#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
struct SYMBOL{
    char symbol;
    int frequency;
};

class ArithmeticCoding {
	private:
		char *alphabet; // 字母表
		double *probilities; // 可能性
		char *content; // 压缩前的内容
		SYMBOL *symbols;
		int size;
		int len;

	public:
		ArithmeticCoding(char alphabet1[], int size1 = 20) {
			int i = 0;
			alphabet = alphabet1;
			size = size1;
            symbols = new SYMBOL[size];
            for(i = 0; i < size; i++){
                symbols[i].symbol = alphabet[i];
                symbols[i].frequency = 0;
            }
		}
		void probilitiesInit();
		void readFile(char *filename);
		void encode(char *inputFile, char *outputFile);
		void decode(char *outputFile, char *decodedFile);
};


void ArithmeticCoding::readFile(char *filename){
    char *Content;
    int i;
    fstream infile;
    infile.open(filename, ios::in);
    infile >> Content;
    infile.close();
    len = strlen(Content);
    content = new char[len];
    for(i = 0; i < len; i++){
        content[i] = Content[i];
    }

}

void ArithmeticCoding::probilitiesInit(){
    int i, j;
    double a;
    double probilities[size];
    int sum;
    probilities = new double[size];
    for(j = 0; j < len; j++){
        for(i = 0; i < size; i++){

            if(content[j] == symbols[i].symbol){
                symbols[i].frequency ++;

            }
        }
    }
    for(i = 0; i< size; i++){
        Probilities[i] = (float)symbols[i].frequency * 1.0/ len ;
    }
    for(i = 0; i< size; i++){
        sum = 0;
        for (j = 0; j<= i; j++){
            sum += probilities[j];
        }
        probilities[i] = sum;
    }
    //probilities = Probilities;
}



void ArithmeticCoding::encode(char *inputFile, char *outputFile){
    int i, j;
    double down = 0.0;
    double up = 1.0;
    int index;
    //char *p = *content;
    char inputchar;
    readFile(inputFile);
    probilitiesInit();

    for(i=0 ; i < len; i++){
        inputchar = content[i];
        for(j = 0; j < size; j ++ ){
            if (inputchar = symbols[j].symbol){
                index = j;
                break;
            }
        }
        down = down + (up - down) * probilities[i];
        up = down + (up - down) * probilities[i+1];

    }

}



void start(){
    int size;
        int i = 0;
        char alphabet[20];
        cout << "请输入字母表的大小：" ;
        cin >> size;//5

        for (i; i < size ; i++) {
            cout << "依次输入字母表：";
            cin >> alphabet[i];

        }//abcde

        ArithmeticCoding a = ArithmeticCoding(alphabet, size);
        a.readFile("originFile.txt");
        a.probilitiesInit();

}


void displayDoubleBits(double f)
{
	int *p = (int *)&f; // 以int的眼光来理解这段内存
	int i;
	int width = 8;
	int len = 64;
	for(i = len - 1 ; i >= 0; i--)
	{
		cout << ((*p >> i) & 1) ;
		if(0 == i % width)
		{
			cout << " ";
		}
	}

	printf(" <---> %lf\n", f); // 此处不用cout,否则将12.0输出为12

}
int main() {
	double a = 0.25;
	//cout << *(&a) ;
	double f = 0.25;
    displayDoubleBits(f);

}
