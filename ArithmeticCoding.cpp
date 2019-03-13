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
    if(!infile.is_open()){
        //cerr<<"can't find file "<<argv[i+1]<<endl;
        cerr<<"ERRCODE:"<<errno<<" "<<strerror(errno)<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    len = infile.tellg();
    cout << len << endl;
    infile.seekg(0,ios::beg);

    infile >> Content;
    infile.close();

    //len = strlen(Content);
    //cout << len << endl;

    content = new char[len];
    for(i = 0; i < len; i++){
        content[i] = Content[i];
    }

}

void ArithmeticCoding::probilitiesInit(){
    int i, j;
    double a;
    double Probilities[size];
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
    double down_x, up_x;
    int index;
    char* binaryCharBuf = new char[100];
    char* p, q = binaryCharBuf;
    int E3;

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

        E3 = 0;
        while(true){
            if(up==0 && down == 0){
                if(E3){
                    up = up_x;
                    down =down_x;
                    break;
                }
                else{
                    break;
                }

            }
            if(E3 == 0){
                if(down<0.5&&up<0.5){
                    *p = 0;
                    p++;
                    up = up * 2;
                    down = down * 2;
                }
                else if(down >= 0.5 && up >= 0.5){
                    *p = 1;
                    p++;
                    up = (up - 0.5) * 2;
                    down = (down - 0.5) * 2;
                }else{
                    E3 = 1;
                    q = p;
                    p++;
                    down = down * 2;
                    up = (up - 0.5) * 2;
                }
            }else{
                if(down<0.5&&up<0.5){
                    *q = 0;
                    q++;
                    while(p != q){
                        *q = 1;
                        q++;
                    }

                    *p = 0;
                    p++;
                    up = up * 2;
                    down = down * 2;

                    E3 = 0;
                }
                else if(down >= 0.5 && up >= 0.5){
                    *q = 1;
                    q++;

                    while(p != q){
                        *q = 0;
                        q++;

                    }
                    *p = 1;
                    p++;
                    up = (up - 0.5) * 2;
                    down = (down - 0.5) * 2;

                    E3 = 0;
                }else{
                    p++;
                    down = down>0.5?(down - 0.5) *2:down * 2;
                    up = up>0.5?(up - 0.5) *2:up * 2;
                }
            }

        }
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
	start();

}
