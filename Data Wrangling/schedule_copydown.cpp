// this code copies down the schedule
#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false);
	vector<string> v;
	string s;
    int sch_colno;
	//reading data from the file in which already has route number copied down(route atlas)
	cout<<"Enter your schedule column number in your file from end(0-based-index):";
	cin>>sch_colno;
	ifstream myfile("routenocopydown.txt");
	if(myfile.is_open())
	{
		while(getline(myfile,s))
		{
			v.push_back(s);		
		}
		myfile.close();
	}
	string prev_w;
	// if schedule is missing it copies it down
	for(int i=0;i<v.size();i++)
	{
		int count=0,u;
		string w;
		for(int j=v[i].size()-1;j>=0;j--)
		{
			if(v[i][j]==',')
			{
				count++;
			}
			if(count==sch_colno&&v[i][j]!=',')
			{
				w.insert(w.begin(),v[i][j]);
			}
			if(count==sch_colno+1)
			{
				u=j;
				break;
			}
		}
		if(w.empty())
		{
			string first=v[i].substr(0,u+1);
			string second=v[i].substr(u+1,v[i].size()-u-1);
			for(int j=0;j<prev_w.size();j++)
			{
				first.insert(first.end(),prev_w[j]);
			}
			first=first+""+second;
			v[i].clear();
			v[i]=first;
		}
		else
		{
			prev_w=w;
		}
	}
	//writing the data in a file
	ofstream tyfile("schcopydown.txt");
	if(tyfile.is_open())
	{
		for(int i=0;i<v.size();i++)
		{
			tyfile<<v[i]<<"\n";
		}
		tyfile.close();
	}
}
