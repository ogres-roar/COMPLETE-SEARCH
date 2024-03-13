#include <iostream>
#include <functional>
#include "dfs.h"

using namespace std;

int main()
{
    function<void(int)> dfs;
    bool success = false;
    dfs = [&](int step)
    {
        if (condation())
        {
            success = true;
            return;
        }

        step += 1;
        for (; loop();)
        {
            process();
            dfs(step);
            if (success)
            {
                return;
            }
        }
        return;
    };

    dfs(0);
    return 0;
}