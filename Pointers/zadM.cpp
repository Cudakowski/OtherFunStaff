#include <iostream>
#include <vector>
#include <unordered_map>

//

void printVec(std::vector<int> &vec)
{
    for (auto &&i : vec)
    {
        std::cout<<i<<", ";
    }
    std::cout<<"\n";
}



int fun(std::vector<int> &vec, int k)
{
    if(vec.size()<k || k<=0)
        return 0;
    if(k==1)
        return vec.size();

    int przesuwacDo{k-1};
    int ans{};

    std::unordered_map<int,int> mp;

    for(int i{};i<vec.size();i++)
    {
        if(mp[vec[i]]+k-1>przesuwacDo)
        {
            przesuwacDo=mp[vec[i]]+k;
        }


        mp[vec[i]]=i;

        if(i>=przesuwacDo)
        {
            ans++;
        }
    }

    return ans;
}


int main(int argc, char const *argv[])
{
    std::vector<int> A{1,2,5,3,4,4,1,2,7,1};

    int B = fun(A,3);

    printVec(A);
    std::cout<<B<<'\n';

    return 0;
}
