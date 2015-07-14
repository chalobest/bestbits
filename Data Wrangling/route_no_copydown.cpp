// this code copies down the route_number of atlas
#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false);
	vector<string> v;
	cout<<"MAke sure that route_no is your first column\n";
	string s;
	//reading data from route atlas file
	ifstream myfile("atlas.txt");
	if(myfile.is_open())
	{
		while(getline(myfile,s))
		{
			v.push_back(s);		
		}
		myfile.close();
	}
	string w;
	//vector v contains all rows of route_atlas
	//copies down the route_no if there is a missing entry
	for(int i=0;i<v.size();i++)
	{
		if(v[i][0]==',')
		{
			for(int j=w.size()-1;j>=0;j--)
			{
				v[i].insert(v[i].begin(),w[j]);
			}
		}
		else
		{
			int j=0;
			w.clear();
			while(v[i][j]!=',')
			{
				w.insert(w.end(),v[i][j]);
				j++;
			}
		}
	}
	//writing the data again in a file
	ofstream tyfile("routenocopydown.txt");
	if(tyfile.is_open())
	{
		for(int i=0;i<v.size();i++)
		{
			tyfile<<v[i]<<"\n";
		}
		tyfile.close();
	}
}
