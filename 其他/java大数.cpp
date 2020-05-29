//！！！！提交JAVA的时候一定要去掉package
//创建大数类
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.Scanner;

        Scanner cin=new Scanner(System.in);

        BigInteger num1=new BigInteger("12345");
        BigInteger num2=cin.nextBigInteger();

        BigDecimal num3=new BigDecimal("123.45");
        BigDecimal num4=cin.nextBigDecimal();
//整数
import java.math.BigInteger;

public class Main {
    public static void main(String[] args) {
        BigInteger num1=new BigInteger("12345");
        BigInteger num2=new BigInteger("45");
        //加法
        System.out.println(num1.add(num2));
        //减法
        System.out.println(num1.subtract(num2));
        //乘法
        System.out.println(num1.multiply(num2));
        //除法(相除取整)
        System.out.println(num1.divide(num2));
        //取余
        System.out.println(num1.mod(num2));
        //最大公约数GCD
        System.out.println(num1.gcd(num2));
        //取绝对值
        System.out.println(num1.abs());
        //取反
        System.out.println(num1.negate());
        //取最大值
        System.out.println(num1.max(num2));
        //取最小值
        System.out.println(num1.min(num2));
        //是否相等
        System.out.println(num1.equals(num2));
    }
}
//浮点数
import java.math.BigDecimal;

public class Main {
    public static void main(String[] args) {
        BigDecimal num1=new BigDecimal("123.45");
        BigDecimal num2=new BigDecimal("4.5");
        //加法
        System.out.println(num1.add(num2));
        //减法
        System.out.println(num1.subtract(num2));
        //乘法
        System.out.println(num1.multiply(num2));
        //除法（在divide的时候就设置好要精确的小数位数和舍入模式）
        System.out.println(num1.divide(num2,10,BigDecimal.ROUND_HALF_DOWN));
        //取绝对值
        System.out.println(num1.abs());
        //取反
        System.out.println(num1.negate());
        //取最大值
        System.out.println(num1.max(num2));
        //取最小值
        System.out.println(num1.min(num2));
        //是否相等
        System.out.println(num1.equals(num2));
        //判断大小( > 返回1, < 返回-1)
        System.out.println(num2.compareTo(num1));
    }
}
//hdu1715 求第N项斐波那契数
import java.util.Scanner;
import java.math.BigInteger;
public class Main {
    static BigInteger a[] = new BigInteger[1001];   //开全局变量的数组
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        a[1] = a[2] = new BigInteger("1");   //大数赋值
        for(int i = 3; i <= 1000 ; i ++) a[i] = a[i - 1].add(a[i - 2]); //大数加
        while(cin.hasNext()) {            //读到文件尾
            int N = cin.nextInt();
            for(int i = 1; i <= N ; i ++) {
                int p = cin.nextInt();
                System.out.println(a[p]);
            }
        }
    }
}
//POJ1001高精度幂 浮点数幂次 + 去掉前导后导0
import java.math.BigDecimal;
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext()) {
            BigDecimal a = cin.nextBigDecimal();
            int t = cin.nextInt(); 
            a = a.pow(t);
            String ans = a.stripTrailingZeros().toPlainString();  //去掉结尾的0
            if(ans.startsWith("0")) ans = ans.substring(1);  //去掉开头的0
            System.out.println(ans);
        }
    }
}
//HDU1042 N!
import java.math.BigInteger;
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext()) {
            int x = cin.nextInt();
            BigInteger a = BigInteger.ONE;
            for(int i = 1; i <= x; i ++) a = a.multiply(BigInteger.valueOf(i));
            System.out.println(a);
        }
    }
}
//hdu1753 浮点数相加 去结尾0
import java.util.Scanner;
import java.math.BigDecimal;
public class Main {
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext()) {
            BigDecimal a = cin.nextBigDecimal(),b = cin.nextBigDecimal();
            a = a.add(b);
            String ans = a.stripTrailingZeros().toPlainString();
            System.out.println(ans);
        }
    }
}
//hdu1023 大数卡特兰数
import java.util.Scanner;
import java.math.BigInteger;
public class Main {
    static BigInteger a[] = new BigInteger[110];
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        a[1] = BigInteger.ONE;
        for(int i = 2; i <= 100; i ++) {
            a[i] = a[i - 1].multiply(BigInteger.valueOf(4 * i - 2)).divide(BigInteger.valueOf(i + 1));
        }
        while(cin.hasNext()) {
            int t = cin.nextInt();
            System.out.println(a[t]);
        }
    }
}
