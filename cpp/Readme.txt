程序执行（Linux）
执行格式：
main inputfile outputfile

算术编解码：
ArithmeticCompress
ArithmeticDecompress

自适应算术编解码：
AdaptiveArithmeticCompress
AdaptiveArithmeticDecompress


程序框架构成：
ArithmetcCoder
算术编解码的基本的fields和methods

Bitlostream
对bit和读入字节流进行相互转换

FrequencyTable
频率表，其中
SimpleFrequencyTable为ArithmeticCoder使用的简单的静态的频率表
FlatFrequencyTable为AdaptiveArithmeticCoder中使用的动态的频率表实现方式见word：实现.docx
BITreeFrequencyTable是对应AdaptiveArithmeticCoder中使用Bit Index Tree的实现方式

ArithmeticCompress
ArithmeticDecompress
AdaptiveArithmeticCompress
AdaptiveArithmeticDecompress
相应的程序的具体实现
