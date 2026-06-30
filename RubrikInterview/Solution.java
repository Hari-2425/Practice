import java.util.HashMap;
import java.util.Map;

class Solution {

    public static void main(String[] args) {
        // Test case 1: Simple terminating decimal
        System.out.println("1/2 = " + fractionToDecimal(1, 2)); // Expected: "0.5"
        
        // Test case 2: Repeating decimal
        System.out.println("1/6 = " + fractionToDecimal(1, 6)); // Expected: "0.1(6)"
        
        // Test case 3: Long repeating cycle
        System.out.println("1/7 = " + fractionToDecimal(1, 7)); // Expected: "0.(142857)"
        
        // Test case 4: Negative numerator
        System.out.println("-1/2 = " + fractionToDecimal(-1, 2)); // Expected: "-0.5"
        
        // Test case 5: Negative denominator
        System.out.println("1/-2 = " + fractionToDecimal(1, -2)); // Expected: "-0.5"
        
        // Test case 6: Both negative
        System.out.println("-1/-2 = " + fractionToDecimal(-1, -2)); // Expected: "0.5"
        
        // Test case 7: Integer result
        System.out.println("2/1 = " + fractionToDecimal(2, 1)); // Expected: "2"
        
        // Test case 8: Zero numerator
        System.out.println("0/5 = " + fractionToDecimal(0, 5)); // Expected: "0"
        
        // Test case 9: Large numbers (overflow risk)
        System.out.println("1/3 = " + fractionToDecimal(1, 3)); // Expected: "0.(3)"
        System.out.println("-2147483648/1 = " + fractionToDecimal(-2147483648, 1)); // Expected: "-2147483648"
        
        // Test case 10: Complex repeating
        System.out.println("4/333 = " + fractionToDecimal(4, 333)); // Expected: "0.(012)"
    }

    public static String fractionToDecimal(int numerator, int denominator) {
        StringBuilder ans = new StringBuilder();
        
        // Handle sign
        if ((numerator < 0) ^ (denominator < 0)) {
            ans.append("-");
        }
        
        long num = Math.abs((long) numerator);
        long den = Math.abs((long) denominator);
        
        // Integer part
        ans.append(num / den);
        
        long remainder = num % den;
        if (remainder == 0) {
            return ans.toString();
        }
        
        // Decimal part
        ans.append(".");
        Map<Long, Integer> remainderMap = new HashMap<>();
        
        while (remainder != 0) {
            if (remainderMap.containsKey(remainder)) {
                // Found repeating cycle - insert opening paren at first occurrence
                int repeatStart = remainderMap.get(remainder);
                ans.insert(repeatStart, "(");
                ans.append(")");
                break;
            }
            
            remainderMap.put(remainder, ans.length());
            remainder *= 10;
            ans.append(remainder / den);
            remainder %= den;
        }
        
        return ans.toString();
    }
}

