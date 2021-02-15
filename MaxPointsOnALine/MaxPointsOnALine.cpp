#include <iostream>
#include <vector>
#include <map>
#include <utility>+

using namespace std;

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        map<std::pair<int, int>, bool> map;

    	//Input
    	for(int i = 0; i < points.size(); ++i)
    	{
            map[{points[i][0], points[i][1]}] = true;
    	}

        int topScore = 1;
    	for(int i = 0; i < points.size() - 1; ++i)
    	{
            int score = 1;
    		for(int j = i + 1; j < points.size(); ++j)
    		{
                int x1 = points[i][0];
                int y1 = points[i][1];
    			
                int x2 = points[j][0];
                int y2 = points[j][1];

                int diffX = std::max(x1, x2) - min(x1, x2);
                int diffY = std::max(y1, y2) - min(y1, y2);

                int slope;
                int dots = 1;
    			
    			if(diffX != 0)
    			{
                    slope = diffY / diffX;
    				while(diffX > 0)
    				{
                        x1 += 1;
                        y1 += slope;
                        diffX--;
                        if (map[make_pair(x1, y1)])dots++;
    				}
    			}else
                    if(diffY != 0)
    			{
                    slope = diffX / diffY;
                    while (diffY > 0)
                    {
                        y1 += 1;
                        x1 += slope;
                        diffY--;
                        if (map[make_pair(x1, y1)])dots++;
                    }
    			}
                if (dots > score)score = dots;
    		}

            if (score > topScore)topScore = score;
    	}
    	
        return topScore;
    }
};

void Test(vector<vector<int>>& points, int result)
{
    Solution solution;

    cout << solution.maxPoints(points) << "Expected result: " << result << "\n";
}

int main()
{
	
    vector<vector<int>> v = { {1,1}, {3,2}, {5,3}, {4,1}, {2,3}, {1,4} };
	
    Test(v, 5);
}
