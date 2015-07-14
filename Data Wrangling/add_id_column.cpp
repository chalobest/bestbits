// this code adds a dummy column named id to the atlas
#include <bits/stdc++.h>
using namespace std;
int main()
{
ios_base::sync_with_stdio(false);
vector<string> v;
string s;
ifstream myfile("AtlasAPRIL2015.txt");
if(myfile.is_open())
{
while(getline(myfile,s))
{
v.push_back(s);
}
myfile.close();
}
//vector v contains all rows of atlas
//so adding one more column id which contains row number of atlas
for(int i=0;i<v.size();i++)
{
v[i].insert(v[i].end(),',');
int p=i+1;
string w=to_string(p);
for(int j=0;j<w.size();j++)
{
v[i].insert(v[i].end(),w[j]);
}
}
//writing the data again in a file named atlasatlas.txt
ofstream tyfile("atlas.txt");
if(tyfile.is_open())
{
for(int i=0;i<v.size();i++)
{
tyfile<<v[i]<<"\n";
}
tyfile.close();
}
}
