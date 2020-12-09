#include <iostream>
#include <vector>

class Solution {
public:
    int myAtoi(std::string s) {
        int result = 0;
        int decimal = 0;
        bool sign = false;

        const char* char_array = s.c_str();

        bool sneakySign = false;

        for (int i = 0; i < s.size(); ++i)
        {
            if (char_array[i] > '0' && char_array[i] <= '9' || (char_array[i] == '0' && decimal != 0))
            {
                decimal++;

                //Check sign if it's the first decimal
                if (decimal == 0 && char_array[i] == '0')
                {
                    continue;
                }

                if (result > 214748364)
                {
                    if (sign)return INT_MIN;
                    return INT_MAX;
                }
                if (result == 214748364)
                {
                    int interloper = char_array[i] - '0';
                    if (sign && interloper >= 8)return INT_MIN;
                    if (!sign && interloper >= 7)return INT_MAX;
                }

                result *= 10;

                result += char_array[i] - '0';

            }
            else if (decimal == 0)
            {
                if (char_array[i] == ' ' && !sneakySign)continue;

                if ((char_array[i] == '-' || char_array[i] == '+') && !sneakySign)
                {
                    if (char_array[i] == '-')sign = true;
                    sneakySign = true;
                    continue;
                }
                if (char_array[i] == '0')
                {
                    continue;
                }
                break;
            }
            else break;
        }

        if (sign) return -result;
        return result;
    }
};

void Test(std::string s, int result)
{
    Solution solution;

    std::cout << "Extracted value is: " << solution.myAtoi(s) << " Expected result was: " << result << " Input: " << s << "\n";
}

int main()
{
	Test("     21474836460 asdjm asd aksd -32  1 asdasd ", 2147483647);
    Test("-0000000000012345678", -12345678);
    Test("+-12", 0);
    Test("00000-42a1234", 0);
    Test("2147483646", 2147483646);//-2147483648~2147483647
    Test("-2147483648", -2147483648);
    Test("-2147483647", -2147483647);
    Test("123-", 123);
    Test("3.14159", 3);
    Test("123  456", 123);
    Test("   +0 123", 123);
	
    return 0;
}