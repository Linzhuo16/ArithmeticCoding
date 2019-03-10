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
		float *probilities; // 可能性
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
		void encode(char *outputFile);
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
    float a;
    probilities = new float[size];
    for(j = 0; j < len; j++){
        for(i = 0; i < size; i++){

            if(content[j] == symbols[i].symbol){
                symbols[i].frequency ++;

            }
        }
    }
    for(i = 0; i< size; i++){
        probilities[i] = (float)symbols[i].frequency * 1.0/ len ;
    }
    //probilities = Probilities;
}



void ArithmeticCoding::encode(char *inputFile, char *outputFile){
    readFile(inputFile);
    probilitiesInit();


}

int main() {
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
	return 0;
}
