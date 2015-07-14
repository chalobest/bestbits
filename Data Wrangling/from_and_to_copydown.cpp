// this code copies down the from and to stops
// int his code also make sure that route number is your first column and route number are already copied down
#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false);
	vector<string> v;
	string s;
	int from_colno,to_colno;
	cout<<"Enter your from stop column number in atlas(0-based-index):";
	cin>>from_colno;
	cout<<"Enter your to stop column number in atlas(0-based-index):";
	cin>>to_colno;
	ifstream myfile("schcopydown.txt");
	if(myfile.is_open())
	{
		while(getline(myfile,s))
		{
			v.push_back(s);
		}
		myfile.close();
	}
	// vector v contains all rows of atlas
	//below loop extract from and to stops and checks if route number is same as some previous row
	//then it checks if from and to stops are missing then it inserts the previous from and to there
	string prev_w,prev_x,prev_y;
	for(int i=0;i<v.size();i++)
	{
		string w;
		for(int j=0;j<v[i].size();j++)
		{
			if(v[i][j]==',')
			{
				break;
			}
			w.insert(w.end(),v[i][j]);
		}
		int count=0;
		string x,y;
		for(int j=0;j<v[i].size();j++)
		{
			if(v[i][j]==',')
			{
				count++;
			}
			if(count==from_colno&&v[i][j]!=',')
			{
				x.insert(x.end(),v[i][j]);
			}
			if(count==to_colno&&v[i][j]!=',')
			{
				y.insert(y.end(),v[i][j]);
			}
		}
		if(x.empty())
		{
			if(prev_w==w)
			{
				if(!prev_x.empty())
				{
					count=0;
					int u;
					for(int j=0;j<v[i].size();j++)
					{
						if(v[i][j]==',')
						{
							count++;
						}
						if(count==from_colno)
						{
							u=j;
							break;
						}
					}
					string h=v[i].substr(u+1,v[i].size()-u-1);
					string k=v[i].substr(0,u+1);
					for(int j=0;j<prev_x.size();j++)
					{
						k.insert(k.end(),prev_x[j]);
					}
					v[i].clear();
					v[i]=k+""+h;
				}
			}
		}
		else
		{
			prev_x=x;
		}
		if(y.empty())
		{
			if(prev_w==w)
			{
				if(!prev_y.empty())
				{
					count=0;
					int u;
					for(int j=0;j<v[i].size();j++)
					{
						if(v[i][j]==',')
						{
							count++;
						}
						if(count==to_colno)
						{
							u=j;
							break;
						}
					}
					string h=v[i].substr(u+1,v[i].size()-u-1);
					string k=v[i].substr(0,u+1);
					for(int j=0;j<prev_y.size();j++)
					{
						k.insert(k.end(),prev_y[j]);
					}
					v[i].clear();
					v[i]=k+""+h;
				}
			}
		}
		else
		{
			prev_y=y;
		}
		prev_w=w;
	}
	//writing data again in a file
	ofstream tyfile("fromcopydown.txt");
	if(tyfile.is_open())
	{
		for(int i=0;i<v.size();i++)
		{
			tyfile<<v[i]<<"\n";
		}
		tyfile.close();
	}
}
