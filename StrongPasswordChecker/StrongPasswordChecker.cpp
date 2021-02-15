#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

class Solution {
public:
    int strongPasswordChecker(std::string password) {
        int timesCharactersRepeated = 0;
        int characterBalance = 0;

        int upperCase = 0,
            lowerCase = 0,
            digit = 0;

        //Check if password length is at least 6 and at most 20
        int length = password.length();
    	
        if (length < 6) characterBalance = length - 6;
        else if (length > 20) characterBalance = length - 20;

        const char* char_array = password.c_str();

        for (int i = 0; i < length + 1; ++i) {
            //Check if it's the same as last letter
            if (char_array[i] == lastLetter) {
                repeatingCharCount++;

                if (repeatingCharCount == 2)
                {
                    timesCharactersRepeated++;
                    repeats.push_back(3);
                }
                else if (repeatingCharCount > 2)
                {
                    repeats[timesCharactersRepeated - 1]++;
                }
            }
            else {
                repeatingCharCount = 0;
            }
            lastLetter = char_array[i];

            //Check if password contains upper, lower and a digit
            if (char_array[i] >= 65 && char_array[i] <= 90)upperCase++;
            if (char_array[i] >= 97 && char_array[i] <= 122)lowerCase++;
            if (char_array[i] >= 48 && char_array[i] <= 57)digit++;
        }

        //Evaluation
        int caseDigitCheck = 0;
        caseDigitCheck += !(bool)upperCase;
        caseDigitCheck += !(bool)lowerCase;
        caseDigitCheck += !(bool)digit;

    	if(characterBalance <= 0)
    	{
            int repeatFixes = 0;
            for (int i : repeats)
            {
                repeatFixes += i / 3;
            }
    		
			return std::max(std::max(caseDigitCheck, repeatFixes), -characterBalance);
    	}

    	if(characterBalance > 0)
    	{
            int repeatFixes = 0;
            int adv = 0;         //Opportunity to fix one repeat while reducing budget
            int removeOption = 0;//Opportunity to fix one repeat while reducing budget by two
            for (int i : repeats)
            {
                repeatFixes += i / 3;
                adv += !(bool)(i % 3);
            	
            	if(i == 4)removeOption += 1;
            }
    		
            characterBalance -= adv;
            if (characterBalance < 0) characterBalance = 0;

    		
    		if(int budget = characterBalance / 2 > 0 && removeOption > 0)
    		{
                repeatFixes -= std::min(budget, removeOption);
    		}

    		//Gain moves by removing excess repeats using budget
            repeatFixes -= characterBalance / 3;
            if (repeatFixes < 0) repeatFixes = 0;
    		
            return std::max(repeatFixes, caseDigitCheck + adv) + characterBalance;
    	}
    }
private:
    int repeatingCharCount = 0;
    std::vector<int>repeats;
    char lastLetter = '\0';
};

void Test(std::string s, int result)
{
    Solution solution;
	
    int r = solution.strongPasswordChecker(s);
	
    if (r == result) {
        std::cout << "SUCCESS: " << "Test Case -" << s << "- Returned: " << r << std::endl;
    }
    else
    {
        std::cout <<"FAIL: " <<"Test Case -" << s << "- Returned: " << r << " instead of " << result << " Size: " << s.length() << std::endl;
    }
}

int main()
{
	if(1)
	{	
        Test("1", 5);
        Test("11", 4);
        Test("111", 3);
        Test("a13", 3);
        Test("1111", 2);
        Test("111a", 2);
        Test("a132", 2);
        Test("11111", 2);
        Test("111111", 2);
        Test("1111111111", 3);
        Test("ABABABABABABABABABAB1", 2);
        Test("bbaaaaaaaaaaaaaaacccccc", 8);
        Test("aaaaAAAAAA000000123456", 5);
        Test("aaaabbbbccccddeeddeeddeedd", 8);
        Test("FFFFFFFFFFFFFFF11111111111111111111AAA", 23);
        Test("A1234567890aaabbbbccccc", 4);
        Test("abababababababababaaa", 3);
	}
	
    return 0;
}
