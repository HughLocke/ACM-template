//bitset<maxn>a
/*
bitset是一种专门用来储存二进制的数组，使用前要先调用函数库。
他的每一个元素只占 1 bit空间，你可以将它当作bool类型的高精度。
他的优点很多，你可将他整体使用，也可单个访问
bitset的原理大概是将很多数压成一个，从而节省空间和时间（暴力出奇迹）
一般来说bitset会让你的算法复杂度 /32
 */
//构造函数
bitset<4> bitset1;  //无参构造，长度为４，默认每一位为０
 bitset<8> bitset2(12);  //长度为８，二进制保存，前面用０补充
string s = "100101";
bitset<10> bitset3(s);  //长度为10，前面用０补充
char s2[] = "10101";
bitset<13> bitset4(s2);  //长度为13，前面用０补充
cout << bitset1 << endl;  //0000
cout << bitset2 << endl;  //00001100
cout << bitset3 << endl;  //0000100101
cout << bitset4 << endl;  //0000000010101

bitset<2> bitset1(12);  //12的二进制为1100（长度为４），但bitset1的size=2，只取后面部分，即00
string s = "100101";  
bitset<4> bitset2(s);  //s的size=6，而bitset的size=4，只取前面部分，即1001
char s2[] = "11101";
bitset<4> bitset3(s2);  //与bitset2同理，只取前面部分，即1110
cout << bitset1 << endl;  //00
cout << bitset2 << endl;  //1001
cout << bitset3 << endl;  //1110

//可用操作符
bitset<4> foo (string("1001"));
bitset<4> bar (string("0011"));
cout << (foo^=bar) << endl;       // 1010 (foo对bar按位异或后赋值给foo)
cout << (foo&=bar) << endl;       // 0010 (按位与后赋值给foo)
cout << (foo|=bar) << endl;       // 0011 (按位或后赋值给foo)
cout << (foo<<=2) << endl;        // 1100 (左移２位，低位补０，有自身赋值)
cout << (foo>>=1) << endl;        // 0110 (右移１位，高位补０，有自身赋值)
cout << (~bar) << endl;           // 1100 (按位取反)
cout << (bar<<1) << endl;         // 0110 (左移，不赋值)
cout << (bar>>1) << endl;         // 0001 (右移，不赋值)
cout << (foo==bar) << endl;       // false (0110==0011为false)
cout << (foo!=bar) << endl;       // true  (0110!=0011为true)
cout << (foo&bar) << endl;        // 0010 (按位与，不赋值)
cout << (foo|bar) << endl;        // 0111 (按位或，不赋值)
cout << (foo^bar) << endl;        // 0101 (按位异或，不赋值)

//下标访问
bitset<4> foo ("1011");
cout << foo[0] << endl;  //1
cout << foo[1] << endl;  //1
cout << foo[2] << endl;  //0

//支持的函数
bitset<8> foo ("10011011");
cout << foo.count() << endl;  //5　　（count函数用来求bitset中1的位数，foo中共有５个１
cout << foo.size() << endl;   //8　　（size函数用来求bitset的大小，一共有８位
cout << foo.test(0) << endl;  //true　　（test函数用来查下标处的元素是０还是１，并返回false或true，此处foo[0]为１，返回true
cout << foo.test(2) << endl;  //false　　（同理，foo[2]为０，返回false
cout << foo.any() << endl;    //true　　（any函数检查bitset中是否有１
cout << foo.none() << endl;   //false　　（none函数检查bitset中是否没有１
cout << foo.all() << endl;    //false　　（all函数检查bitset中是全部为１

//操作函数，相比于运用下标，这些会检查有没有越界
bitset<8> foo ("10011011");
cout << foo.flip(2) << endl;  //10011111　　（flip函数传参数时，用于将参数位取反，本行代码将foo下标２处"反转"，即０变１，１变０
cout << foo.flip() << endl;   //01100000　　（flip函数不指定参数时，将bitset每一位全部取反
cout << foo.set() << endl;　　　　//11111111　　（set函数不指定参数时，将bitset的每一位全部置为１
cout << foo.set(3,0) << endl;  //11110111　　（set函数指定两位参数时，将第一参数位的元素置为第二参数的值，本行对foo的操作相当于foo[3]=0
cout << foo.set(3) << endl;    //11111111　　（set函数只有一个参数时，将参数下标处置为１
cout << foo.reset(4) << endl;  //11101111　　（reset函数传一个参数时将参数下标处置为０
cout << foo.reset() << endl;   //00000000　　（reset函数不传参数时将bitset的每一位全部置为０

//转换类型
bitset<8> foo ("10011011");
string s = foo.to_string();  //将bitset转换成string类型
unsigned long a = foo.to_ulong();  //将bitset转换成unsigned long类型
unsigned long long b = foo.to_ullong();  //将bitset转换成unsigned long long类型
cout << s << endl;  //10011011
cout << a << endl;  //155
cout << b << endl;  //155