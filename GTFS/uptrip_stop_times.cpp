// this code generates the stop_times
//uptrip contains all source to destination trips from atlas
//from copy down is same as route_atlas with id dummy column added which contains row no of atlas
//uptrip also contains id
#include <bits/stdc++.h>
using namespace std;
struct pree
{
	string aa,bb,cc,dd,ee,ff,gg,hh,ii,jj,kk,ll,stop1,stop2,rid;
};
struct nree
{
	string sp,f2,f3,f4,f5;
};
vector<string> v,v1,v2;
vector<int> startwork;
vector<vector<string> > ans;
//make sure that your maximum route id is less than 10000 else increase the size of array a
vector<pair<string,string> > a[10000];
int main()
{
	ios_base::sync_with_stdio(false);
	int stopcd_colno,stopsr_colno,routeid_routedet_colno,sfirst_colno,slast_colno,h1_colno,h2_colno,h3_colno,h4_colno,h5_colno,t1_colno,t2_colno,t3_colno,t4_colno,t5_colno,id_uptrip_colno,routeid_uptrip_colno,srfirst_colno,srlast_colno,span_colno,r2_colno,r3_colno,r4_colno,r5_colno,id_atlas_colno;
	cout<<"Enter your stop code column number in route details file(0-based-index):";
	cin>>stopcd_colno;
	cout<<"Enter your stop serial column number in route details file(0-based-index):";
	cin>>stopsr_colno;
	cout<<"Enter your route id column number in route details file(0-based-index):";
	cin>>routeid_routedet_colno;
	cout<<"Enter your start time column number in uptrips file(0-based-index):";
	cin>>sfirst_colno;
	cout<<"Enter your end time column number in uptrips file(0-based-index):";
	cin>>slast_colno;
	cout<<"Enter your first headway column number in uptrips file(0-based-index):";
	cin>>h1_colno;
	cout<<"Enter your second headway column number in uptrips file(0-based-index):";
	cin>>h2_colno;
	cout<<"Enter your third headway column number in uptrips file(0-based-index):";
	cin>>h3_colno;
	cout<<"Enter your fourth headway column number in uptrips file(0-based-index):";
	cin>>h4_colno;
	cout<<"Enter your fifth headway column number in uptrips file(0-based-index):";
	cin>>h5_colno;
	cout<<"Enter your first trips(i.e number of trips corr. to first headway) column number in uptrips file(0-based-index):";
	cin>>t1_colno;
	cout<<"Enter your second trips column number in uptrips file(0-based-index):";
	cin>>t2_colno;
	cout<<"Enter your third trips column number in uptrips file(0-based-index):";
	cin>>t3_colno;
	cout<<"Enter your fourth trips column number in uptrips file(0-based-index):";
	cin>>t4_colno;
	cout<<"Enter your fifth trips column number in uptrips file(0-based-index):";
	cin>>t5_colno;
	cout<<"Enter your id column number in uptrips file(0-based-index):";
	cin>>id_uptrip_colno;
	cout<<"Enter your route id column number in uptrips file(0-based-index):";
	cin>>routeid_uptrip_colno;
	cout<<"Enter your start stop serial number column number in uptrips file(0-based-index):";
	cin>>srfirst_colno;
	cout<<"Enter your end stop serial number column number in uptrips file(0-based-index):";
	cin>>srlast_colno;
	cout<<"Enter your id column number in atlas file(0-based-index):";
	cin>>id_atlas_colno;
	cout<<"Enter your second running time(corr. to second headway) column number in atlas file(0-based-index):";
	cin>>r2_colno;
	cout<<"Enter your third running time column number in atlas file(0-based-index):";
	cin>>r3_colno;
	cout<<"Enter your fourth running time column number in atlas file(0-based-index):";
	cin>>r4_colno;
	cout<<"Enter your fifth running time column number in atlas file(0-based-index):";
	cin>>r5_colno;
	cout<<"Enter your span column number in atlas file(0-based-index):";
	cin>>span_colno;
	string s;
	int max_number;
	cout<<"Enter the maximum id in your file(i.e maximum row number of atlas:";
	cin>>max_number;
	//tree stores the data required from file uptrip
	pree tree[max_number+4];
	//sree stores the data reuquired from file atlas
	nree sree[max_number+4];
	//tm stores the start time of a trip as hrs,minutes and seconds format as its first,second and third column resp.
	int tm[max_number+4][3];
	//pm stores the last time of a trip as hrs,minutes and seconds format as its first,second and third column resp.
	int pm[max_number+4][3];
	//opening all the files for reading
	ifstream myfile("uptrip.txt");
	ifstream myfile1("fromcopydown.txt");
	ifstream myfile2("route_details.txt");
	ofstream tyfile("uptrip_stop_times.txt");
	// taking the data from all the three files in three vectors v,v1 and v2 resp.
	if(myfile.is_open())
	{
		while(getline(myfile,s))
		{
			v.push_back(s);
		}
		myfile.close();
	}
	if(myfile1.is_open())
	{
		while(getline(myfile1,s))
		{
			v1.push_back(s);
		}
		myfile1.close();
	}
	if(myfile2.is_open())
	{
		while(getline(myfile2,s))
		{
			v2.push_back(s);
		}
		myfile2.close();
	}
	// in the next for loop we fill array a whose indexes are route ids
	// it stores two things in it first is stop serial number and next is stop code
	// all this data is taken from route details 
	for(int i=0;i<v2.size();i++)
	{
		int count=0;
		string stopcd,routeid,stopsr;
		for(int j=0;j<v2[i].size();j++)
		{
			if(v2[i][j]==',')
			{
				count++;
			}
			if(count==stopcd_colno)
			{
				if(v2[i][j]!=' ')
				stopcd.insert(stopcd.end(),v2[i][j]);
			}
			if(count==routeid_routedet_colno&&v2[i][j]!=',')
			{
				if(v2[i][j]!=' ')
				routeid.insert(routeid.end(),v2[i][j]);
			}
			if(count==stopsr_colno&&v2[i][j]!=',')
			{
				if(v2[i][j]!=' ')
				stopsr.insert(stopsr.end(),v2[i][j]);
			}
		}
		int x=atoi(&routeid[0]);
		a[x].push_back(make_pair(stopsr,stopcd));
	}
	//this loop stores everything required from uptrip into array tree and the indexes of the tree are ids from the route atlas which are also present in uptrip
	for(int i=0;i<v.size();i++)
	{
		int count=0;
		string sfirst,slast,h1,h2,h3,h4,h5,t1,t2,t3,t4,t5,id,routeid,srfirst,srlast;
		for(int j=0;j<v[i].size();j++)
		{
			if(v[i][j]==',')
			{
				count++;
			}
			if(count==sfirst_colno&&v[i][j]!=',')
			{
				sfirst.insert(sfirst.end(),v[i][j]);
			}
			if(count==slast_colno&&v[i][j]!=',')
			{
				slast.insert(slast.end(),v[i][j]);
			}
			if(count==h1_colno&&v[i][j]!=',')
			{
				h1.insert(h1.end(),v[i][j]);
			}
			if(count==h2_colno&&v[i][j]!=',')
			{
				h2.insert(h2.end(),v[i][j]);
			}
			if(count==h3_colno&&v[i][j]!=',')
			{
				h3.insert(h3.end(),v[i][j]);
			}
			if(count==h4_colno&&v[i][j]!=',')
			{
				h4.insert(h4.end(),v[i][j]);
			}
			if(count==h5_colno&&v[i][j]!=',')
			{
				h5.insert(h5.end(),v[i][j]);
			}
			if(count==id_uptrip_colno&&v[i][j]!=',')
			{
				id.insert(id.end(),v[i][j]);
			}
			if(count==t1_colno&&v[i][j]!=',')
			{
				t1.insert(t1.end(),v[i][j]);
			}
			if(count==t2_colno&&v[i][j]!=',')
			{
				t2.insert(t2.end(),v[i][j]);
			}
			if(count==t3_colno&&v[i][j]!=',')
			{
				t3.insert(t3.end(),v[i][j]);
			}
			if(count==t4_colno&&v[i][j]!=',')
			{
				t4.insert(t4.end(),v[i][j]);
			}
			if(count==t5_colno&&v[i][j]!=',')
			{
				t5.insert(t5.end(),v[i][j]);
			}
			if(count==routeid_uptrip_colno&&v[i][j]!=',')
			{
				routeid.insert(routeid.end(),v[i][j]);
			}
			if(count==srfirst_colno&&v[i][j]!=',')
			{
				srfirst.insert(srfirst.end(),v[i][j]);
			}
			if(count==srlast_colno&&v[i][j]!=',')
			{
				srlast.insert(srlast.end(),v[i][j]);
			}
		}
		int x=atoi(&id[0]);
		startwork.push_back(x);
		tree[x].aa=sfirst;tree[x].hh=t1;tree[x].ii=t2;
		tree[x].jj=t3;tree[x].kk=t4;tree[x].ll=t5;tree[x].rid=routeid;
		if(!slast.empty())
		{
			tree[x].bb=slast;
		}
		else
		{
			tree[x].bb="-1";
		}
		if(!h1.empty())
		{
			tree[x].cc=h1;
		}
		else
		{
			tree[x].cc="-1";
		}
		if(!h2.empty())
		{
			tree[x].dd=h2;
		}
		else
		{
			tree[x].dd="-1";
		}
		if(!h3.empty())
		{
			tree[x].ee=h3;
		}
		else
		{
			tree[x].ee="-1";
		}
		if(!h4.empty())
		{
			tree[x].ff=h4;
		}
		else
		{
			tree[x].ff="-1";
		}
		if(!h5.empty())
		{
			tree[x].gg=h5;
		}
		else
		{
			tree[x].gg="-1";
		}
		tree[x].stop1=srfirst;
		tree[x].stop2=srlast;
		count=0;
		string fpart,spart;
		for(int j=0;j<sfirst.size();j++)
		{
			if(sfirst[j]=='.')
			{
				count++;
			}
			if(count==0)
			{
				fpart.insert(fpart.end(),sfirst[j]);
			}
			if(count==1&&sfirst[j]!='.')
			{
				spart.insert(spart.end(),sfirst[j]);
			}
		}
		if(spart.empty())
		{
			tm[x][1]=0;
		}
		else
		{
			if(spart.size()==2)
			tm[x][1]=atoi(&spart[0]);
			else
			{
				spart.insert(spart.end(),'0');
				tm[x][1]=atoi(&spart[0]);
			}
		}
		tm[x][0]=atoi(&fpart[0]);
		if(tm[x][1]==59)
		{
			tm[x][2]=59;
		}
		else
		{
			tm[x][2]=0;
		}
		if(!slast.empty())
		{
			string f1part,s1part;
			count=0;
			for(int j=0;j<slast.size();j++)
			{
				if(slast[j]=='.')
				{
					count++;
				}
				if(count==0)
				{
					f1part.insert(f1part.end(),slast[j]);
				}
				if(count==1&&slast[j]!='.')
				{
					s1part.insert(s1part.end(),slast[j]);
				}
			}
			if(s1part.empty())
			{
				pm[x][1]=0;
			}
			else
			{
				if(s1part.size()==2)
				pm[x][1]=atoi(&s1part[0]);
				else
				{
					s1part.insert(s1part.end(),'0');
					pm[x][1]=atoi(&s1part[0]);
				}
			}
			pm[x][0]=atoi(&f1part[0]);
			if(pm[x][1]==59)
			{
				pm[x][2]=59;
			}
			else
			{
				pm[x][2]=0;
			}
		}
	}
	// now we store everything required from route atlas into array called sree and the indexes of sree are also ids from atlas
	for(int i=0;i<v1.size();i++)
	{
		int count=0;
		string span,r2,r3,r4,r5,id;
		for(int j=0;j<v1[i].size();j++)
		{
			if(v1[i][j]==',')
			{
				count++;
			}
			if(count==span_colno&&v1[i][j]!=',')
			{
				span.insert(span.end(),v1[i][j]);
			}
			if(count==r2_colno&&v1[i][j]!=',')
			{
				r2.insert(r2.end(),v1[i][j]);
			}
			if(count==r3_colno&&v1[i][j]!=',')
			{
				r3.insert(r3.end(),v1[i][j]);
			}
			if(count==r4_colno&&v1[i][j]!=',')
			{
				r4.insert(r4.end(),v1[i][j]);
			}
			if(count==r5_colno&&v1[i][j]!=',')
			{
				r5.insert(r5.end(),v1[i][j]);
			}
			if(count==id_atlas_colno&&v1[i][j]!=',')
			{
				id.insert(id.end(),v1[i][j]);
			}
		}
		int x=atoi(&id[0]);
		if(!span.empty())
		{
			sree[x].sp=span;
		}
		else
		{
			sree[x].sp="-1";
		}
		if(!r2.empty())
		{
			sree[x].f2=r2;
		}
		else
		{
			sree[x].f2="-1";
		}
		if(!r3.empty())
		{
			sree[x].f3=r3;
		}
		else
		{
			sree[x].f3="-1";
		}
		if(!r4.empty())
		{
			sree[x].f4=r4;
		}
		else
		{
			sree[x].f4="-1";
		}
		if(!r5.empty())
		{
			sree[x].f5=r5;
		}
		else
		{
			sree[x].f5="-1";
		}
	}
	// now we come to the main loop which will generate the stop_times.txt
	for(int i=0;i<startwork.size();i++)
	{
		int x=startwork[i],flag=0;
		int sec;
		int r_id=atoi(&tree[x].rid[0]);
		float sfirst=stof(tree[x].aa);
		string slast=tree[x].bb;
		string span=sree[x].sp;
		int srfirst=atoi(&tree[x].stop1[0]);
		int srlast=atoi(&tree[x].stop2[0]);
		//case 1 where there is only a start time and no end time so it means there's only one trip
		if(slast=="-1")
		{
			//checking int which interval start time lies
			if(sfirst<7.00)
			{
				if(span=="-1")
				{
					continue;
				}
				else
				{
					sec=180*(stof(span));
				}
			}
			else if(sfirst<11.00)
			{
				if(sree[x].f2=="-1")
				{
					if(span=="-1")
					{
						continue;
					}
					else
					{
						sec=180*(stof(span));
					}
				}
				else
				{
					sec=60*(atoi(&sree[x].f2[0]));
				}
			}
			else if(sfirst<17.00)
			{
				if(sree[x].f3=="-1")
				{
					if(span=="-1")
					{
						continue;
					}
					else
					{
						sec=180*(stof(span));
					}
				}
				else
				{
					sec=60*(atoi(&sree[x].f3[0]));
				}
			}
			else if(sfirst<20.00)
			{
				if(sree[x].f4=="-1")
				{
					if(span=="-1")
					{
						continue;
					}
					else
					{
						sec=180*(stof(span));
					}
				}
				else
				{
					sec=60*(atoi(&sree[x].f4[0]));
				}
			}
			else
			{
				if(sree[x].f5=="-1")
				{
					if(span=="-1")
					{
						continue;
					}
					else
					{
						sec=180*(stof(span));
					}
				}
				else
				{
					sec=60*(atoi(&sree[x].f5[0]));
				}
			}
			// two cases whether srfirst>srlast or srlast>srfirst
			if(srfirst<srlast)
			{
				int k=2;
				int coocoo=srfirst-1;
				tyfile<<x<<",single,1,"<<a[r_id][coocoo].second<<","<<"1,"<<tm[x][0]<<":"<<tm[x][1]<<":"<<tm[x][2]<<","<<tm[x][0]<<":"<<tm[x][1]<<":"<<tm[x][2]<<"\n";
				for(int j=coocoo+1;j<srlast-1;j++)
				{
					tyfile<<x<<",single,1,"<<a[r_id][j].second<<","<<k<<",,"<<"\n";
					k++;
				}
				int y=(tm[x][2]+sec);
				int z=(tm[x][1]+(y/60));
				int w=(tm[x][0]+(z/60));
				tyfile<<x<<",single,1,"<<a[r_id][srlast-1].second<<","<<k<<","<<w<<":"<<z%60<<":"<<y%60<<","<<w<<":"<<z%60<<":"<<y%60<<"\n";
			}
			else
			{
				int k=2;
				int coocoo=srfirst-1;
				tyfile<<x<<",single,1,"<<a[r_id][coocoo].second<<","<<"1,"<<tm[x][0]<<":"<<tm[x][1]<<":"<<tm[x][2]<<","<<tm[x][0]<<":"<<tm[x][1]<<":"<<tm[x][2]<<"\n";
				for(int j=coocoo-1;j>=srlast;j--)
				{
					tyfile<<x<<",single,1,"<<a[r_id][j].second<<","<<k<<",,"<<"\n";
					k++;
				}
				int y=(tm[x][2]+sec);
				int z=(tm[x][1]+(y/60));
				int w=(tm[x][0]+(z/60));
				tyfile<<x<<",single,1,"<<a[r_id][srlast-1].second<<","<<k<<","<<w<<":"<<z%60<<":"<<y%60<<","<<w<<":"<<z%60<<":"<<y%60<<"\n";
			}
		}
		else
		{
			//case in which both start time and last time are present
			string h1=tree[x].cc;
			string h2=tree[x].dd;
			string h3=tree[x].ee;
			string h4=tree[x].ff;
			string h5=tree[x].gg;
			// case in which all headways are null means there are two trips one at start time and one at end time
			if(h1=="-1"&&h2=="-1"&&h3=="-1"&&h4=="-1"&&h5=="-1")
			{
				sec=-1;
				if(sfirst<7.00)
				{
					if(span=="-1")
					{
						
					}
					else
					{
						sec=180*(stof(span));
					}
				}
				else if(sfirst<11.00)
				{
					if(sree[x].f2=="-1")
					{
						if(span=="-1")
						{
							
						}
						else
						{
							sec=180*(stof(span));
						}
					}
					else
					{
						sec=60*(atoi(&sree[x].f2[0]));
					}
				}
				else if(sfirst<17.00)
				{
					if(sree[x].f3=="-1")
					{
						if(span=="-1")
						{
							
						}
						else	
						{
							sec=180*(stof(span));
						}
					}
					else
					{
						sec=60*(atoi(&sree[x].f3[0]));
					}
				}
				else if(sfirst<20.00)
				{
					if(sree[x].f4=="-1")
					{
						if(span=="-1")
						{
							
						}
						else
						{
							sec=180*(stof(span));
						}
					}
					else
					{
						sec=60*(atoi(&sree[x].f4[0]));
					}
				}
				else
				{
					if(sree[x].f5=="-1")
					{
						if(span=="-1")
						{
							
						}
						else
						{
							sec=180*(stof(span));
						}
					}
					else
					{
						sec=60*(atoi(&sree[x].f5[0]));
					}
				}
				if(sec!=-1){
				if(srfirst<srlast)
				{
					int k=2;
					int coocoo=srfirst-1;
					tyfile<<x<<",double,1,"<<a[r_id][coocoo].second<<","<<"1,"<<tm[x][0]<<":"<<tm[x][1]<<":"<<tm[x][2]<<","<<tm[x][0]<<":"<<tm[x][1]<<":"<<tm[x][2]<<"\n";
					for(int j=coocoo+1;j<srlast-1;j++)
					{
						tyfile<<x<<",double,1,"<<a[r_id][j].second<<","<<k<<",,"<<"\n";
						k++;
					}
					int y=(tm[x][2]+sec);
					int z=(tm[x][1]+(y/60));
					int w=(tm[x][0]+(z/60));
				    tyfile<<x<<",double,1,"<<a[r_id][srlast-1].second<<","<<k<<","<<w<<":"<<z%60<<":"<<y%60<<","<<w<<":"<<z%60<<":"<<y%60<<"\n";
				}
				else
				{
					int k=2;
					int coocoo=srfirst-1;
				    tyfile<<x<<",double,1,"<<a[r_id][coocoo].second<<","<<"1,"<<tm[x][0]<<":"<<tm[x][1]<<":"<<tm[x][2]<<","<<tm[x][0]<<":"<<tm[x][1]<<":"<<tm[x][2]<<"\n";
					for(int j=coocoo-1;j>=srlast;j--)
					{
						tyfile<<x<<",double,1,"<<a[r_id][j].second<<","<<k<<",,"<<"\n";
						k++;
					}
					int y=(tm[x][2]+sec);
					int z=(tm[x][1]+(y/60));
					int w=(tm[x][0]+(z/60));
					tyfile<<x<<",double,1,"<<a[r_id][srlast-1].second<<","<<k<<","<<w<<":"<<z%60<<":"<<y%60<<","<<w<<":"<<z%60<<":"<<y%60<<"\n";
				}
			}
				float s_last=stof(slast);
				sec=-1;
				if(s_last<7.00)
				{
					if(span=="-1")
					{
						
					}
					else
					{
						sec=180*(stof(span));
					}
				}
				else if(s_last<11.00)
				{
					if(sree[x].f2=="-1")
					{
						if(span=="-1")
						{
							continue;
						}
						else
						{
							//cout<<x<<endl;
							sec=180*(stof(span));
						}
					}
					else
					{
						sec=60*(atoi(&sree[x].f2[0]));
					}
				}
				else if(s_last<17.00)
				{
					if(sree[x].f3=="-1")
					{
						if(span=="-1")
						{
							continue;
						}
						else	
						{
							sec=180*(stof(span));
						}
					}
					else
					{
						sec=60*(atoi(&sree[x].f3[0]));
					}
				}
				else if(s_last<20.00)
				{
					if(sree[x].f4=="-1")
					{
						if(span=="-1")
						{
							continue;
						}
						else
						{
							sec=180*(stof(span));
						}
					}
					else
					{
						sec=60*(atoi(&sree[x].f4[0]));
					}
				}
				else
				{
					if(sree[x].f5=="-1")
					{
						if(span=="-1")
						{
							continue;
						}
						else
						{
							sec=180*(stof(span));
						}
					}
					else
					{
						sec=60*(atoi(&sree[x].f5[0]));
					}
				}
				if(sec!=-1){
				if(srfirst<srlast)
				{
					int k=2;
					int coocoo=srfirst-1;
					tyfile<<x<<",double,2,"<<a[r_id][coocoo].second<<","<<"1,"<<pm[x][0]<<":"<<pm[x][1]<<":"<<pm[x][2]<<","<<pm[x][0]<<":"<<pm[x][1]<<":"<<pm[x][2]<<"\n";
					for(int j=coocoo+1;j<srlast-1;j++)
					{
						tyfile<<x<<",double,2,"<<a[r_id][j].second<<","<<k<<",,"<<"\n";
						k++;
					}
					int y=(pm[x][2]+sec);
					int z=(pm[x][1]+(y/60));
					int w=(pm[x][0]+(z/60));
					tyfile<<x<<",double,2,"<<a[r_id][srlast-1].second<<","<<k<<","<<w<<":"<<z%60<<":"<<y%60<<","<<w<<":"<<z%60<<":"<<y%60<<"\n";
				}
				else
				{
					int k=2;
					int coocoo=srfirst-1;
					tyfile<<x<<",double,2,"<<a[r_id][coocoo].second<<","<<"1,"<<pm[x][0]<<":"<<pm[x][1]<<":"<<pm[x][2]<<","<<pm[x][0]<<":"<<pm[x][1]<<":"<<pm[x][2]<<"\n";
					for(int j=coocoo-1;j>=srlast;j--)
					{
						tyfile<<x<<",double,2,"<<a[r_id][j].second<<","<<k<<",,"<<"\n";
						k++;
					}
					int y=(pm[x][2]+sec);
					int z=(pm[x][1]+(y/60));
					int w=(pm[x][0]+(z/60));
					tyfile<<x<<",double,2,"<<a[r_id][srlast-1].second<<","<<k<<","<<w<<":"<<z%60<<":"<<y%60<<","<<w<<":"<<z%60<<":"<<y%60<<"\n";
				}
			}
			}
			else
			{
				//now cases where we have more than one trip in a single time inteval
				//five cases depending on time interval
				if(sfirst<7.00)
				{
					if(h1=="-1")
					{

					}
					else
					{
						if(span=="-1")
						{

						}
						else
						{
							sec=180*(stof(span));
							int t1=atoi(&tree[x].hh[0]);
							int y1=tm[x][2]-(atoi(&h1[0])*60),z1=tm[x][1],w1=tm[x][0];
							if(srfirst<srlast)
							{
								int coocoo=srfirst-1;
								for(int k=1;k<=t1;k++)
								{
									int b=2;
									y1=(y1+(atoi(&h1[0])*60));
									z1=(z1+(y1/60));
									w1=(w1+(z1/60));
									tyfile<<x<<",h1,"<<k<<","<<a[r_id][coocoo].second<<",1,"<<w1<<":"<<z1%60<<":"<<y1%60<<","<<w1<<":"<<z1%60<<":"<<y1%60<<"\n";
									for(int l=coocoo+1;l<srlast-1;l++)
									{
										tyfile<<x<<",h1,"<<k<<","<<a[r_id][l].second<<","<<b<<",,\n";
										b++;
									}
									y1=y1%60;
									z1=z1%60;
									int y=(y1+sec);
									int z=(z1+(y/60));
									int w=(w1+(z/60));
									tyfile<<x<<",h1,"<<k<<","<<a[r_id][srlast-1].second<<","<<b<<","<<w<<":"<<z%60<<":"<<y%60<<","<<w<<":"<<z%60<<":"<<y%60<<"\n";
								}
							}
							else
							{
								int coocoo=srfirst-1;
								for(int k=1;k<=t1;k++)
								{
									int b=2;
									y1=(y1+(atoi(&h1[0])*60));
									z1=(z1+(y1/60));
									w1=(w1+(z1/60));
									tyfile<<x<<",h1,"<<k<<","<<a[r_id][coocoo].second<<",1,"<<w1<<":"<<z1%60<<":"<<y1%60<<","<<w1<<":"<<z1%60<<":"<<y1%60<<"\n";
									for(int l=coocoo-1;l>=srlast;l--)
									{
										tyfile<<x<<",h1,"<<k<<","<<a[r_id][l].second<<","<<b++<<",,\n";
									}
									y1=y1%60;
									z1=z1%60;
									int y=(y1+sec);
									int z=(z1+(y/60));
									int w=(w1+(z/60));
									tyfile<<x<<",h1,"<<k<<","<<a[r_id][srlast-1].second<<","<<b<<","<<w<<":"<<z%60<<":"<<y%60<<","<<w<<":"<<z%60<<":"<<y%60<<"\n";
								}
							}
						}
					}
				}
				int t2=atoi(&tree[x].ii[0]);
				if(t2!=0)
				{
					sec=-1;
					if(sree[x].f2=="-1")
					{
						if(span=="-1")
						{

						}
						else
						{
							sec=180*(stof(span));
						}
					}
					else
					{
						sec=60*atoi(&sree[x].f2[0]);
					}
					if(sec!=-1)
					{
						int y1,z1,w1;
						if(sfirst>7.00)
						{
							y1=tm[x][2]-(atoi(&h2[0])*60),z1=tm[x][1],w1=tm[x][0];
						}
						else
						{
							y1=-(atoi(&h2[0])*60);z1=0;w1=7;
						}

						if(srfirst<srlast)
						{
							int coocoo=srfirst-1;
							for(int k=1;k<=t2;k++)
							{
								int b=2;
								y1=(y1+(atoi(&h2[0])*60));
								z1=(z1+(y1/60));
								w1=(w1+(z1/60));
								tyfile<<x<<",h2,"<<k<<","<<a[r_id][coocoo].second<<",1,"<<w1<<":"<<z1%60<<":"<<y1%60<<","<<w1<<":"<<z1%60<<":"<<y1%60<<"\n";
								for(int l=coocoo+1;l<srlast-1;l++)
								{
									tyfile<<x<<",h2,"<<k<<","<<a[r_id][l].second<<","<<b++<<",,\n";
								}
								y1=y1%60;
								z1=z1%60;
								int y=(y1+sec);
								int z=(z1+(y/60));
								int w=(w1+(z/60));
								tyfile<<x<<",h2,"<<k<<","<<a[r_id][srlast-1].second<<","<<b<<","<<w<<":"<<z%60<<":"<<y%60<<","<<w<<":"<<z%60<<":"<<y%60<<"\n";
							}
						}
						else
						{
							int coocoo=srfirst-1;
							for(int k=1;k<=t2;k++)
							{
								int b=2;
								y1=(y1+(atoi(&h2[0])*60));
								z1=(z1+(y1/60));
								w1=(w1+(z1/60));
								tyfile<<x<<",h2,"<<k<<","<<a[r_id][coocoo].second<<",1,"<<w1<<":"<<z1%60<<":"<<y1%60<<","<<w1<<":"<<z1%60<<":"<<y1%60<<"\n";
								for(int l=coocoo-1;l>=srlast;l--)
								{
									tyfile<<x<<",h2,"<<k<<","<<a[r_id][l].second<<","<<b++<<",,\n";
								}
								y1=y1%60;
								z1=z1%60;
								int y=(y1+sec);
								int z=(z1+(y/60));
								int w=(w1+(z/60));
								tyfile<<x<<",h2,"<<k<<","<<a[r_id][srlast-1].second<<","<<b<<","<<w<<":"<<z%60<<":"<<y%60<<","<<w<<":"<<z%60<<":"<<y%60<<"\n";
							}
						}
					}
				}
				int t3=atoi(&tree[x].jj[0]);
				if(t3!=0)
				{
					sec=-1;
					if(sree[x].f3=="-1")
					{
						if(span=="-1")
						{

						}
						else
						{
							sec=180*(stof(span));
						}
					}
					else
					{
						sec=60*atoi(&sree[x].f3[0]);
					}
					if(sec!=-1)
					{
						int y1,z1,w1;
						if(sfirst>11.00)
						{
							y1=tm[x][2]-(atoi(&h3[0])*60),z1=tm[x][1],w1=tm[x][0];
						}
						else
						{
							y1=-(atoi(&h3[0])*60);z1=0;w1=11;
						}
						if(srfirst<srlast)
						{
							int coocoo=srfirst-1;
							for(int k=1;k<=t3;k++)
							{
								int b=2;
								y1=(y1+(atoi(&h3[0])*60));
								z1=(z1+(y1/60));
								w1=(w1+(z1/60));
								tyfile<<x<<",h3,"<<k<<","<<a[r_id][coocoo].second<<",1,"<<w1<<":"<<z1%60<<":"<<y1%60<<","<<w1<<":"<<z1%60<<":"<<y1%60<<"\n";
								for(int l=coocoo+1;l<srlast-1;l++)
								{
									tyfile<<x<<",h3,"<<k<<","<<a[r_id][l].second<<","<<b<<",,\n";
									b++;
								}
								y1=y1%60;
								z1=z1%60;
								int y=(y1+sec);
								int z=(z1+(y/60));
								int w=(w1+(z/60));
								tyfile<<x<<",h3,"<<k<<","<<a[r_id][srlast-1].second<<","<<b<<","<<w<<":"<<z%60<<":"<<y%60<<","<<w<<":"<<z%60<<":"<<y%60<<"\n";
							}
						}
						else
						{
							int coocoo=srfirst-1;
							for(int k=1;k<=t3;k++)
							{
								int b=2;
								y1=(y1+(atoi(&h3[0])*60));
								z1=(z1+(y1/60));
								w1=(w1+(z1/60));
								tyfile<<x<<",h3,"<<k<<","<<a[r_id][coocoo].second<<",1,"<<w1<<":"<<z1%60<<":"<<y1%60<<","<<w1<<":"<<z1%60<<":"<<y1%60<<"\n";
								for(int l=coocoo-1;l>=srlast;l--)
								{
									tyfile<<x<<",h3,"<<k<<","<<a[r_id][l].second<<","<<b<<",,\n";
									b++;
								}
								y1=y1%60;
								z1=z1%60;
								int y=(y1+sec);
								int z=(z1+(y/60));
								int w=(w1+(z/60));
								tyfile<<x<<",h3,"<<k<<","<<a[r_id][srlast-1].second<<","<<b<<","<<w<<":"<<z%60<<":"<<y%60<<","<<w<<":"<<z%60<<":"<<y%60<<"\n";
							}
						}
					}
				}
				int t4=atoi(&tree[x].kk[0]);
				if(t4!=0)
				{
					sec=-1;
					if(sree[x].f4=="-1")
					{
						if(span=="-1")
						{

						}
						else
						{
							sec=180*(stof(span));
						}
					}
					else
					{
						sec=60*atoi(&sree[x].f4[0]);
					}
					if(sec!=-1)
					{
						int y1,z1,w1;
						if(sfirst>17.00)
						{
							y1=tm[x][2]-(atoi(&h4[0])*60),z1=tm[x][1],w1=tm[x][0];
						}
						else
						{
							y1=-(atoi(&h4[0])*60);z1=0;w1=17;
						}
						if(srfirst<srlast)
						{
							int coocoo=srfirst-1;
							for(int k=1;k<=t4;k++)
							{
								int b=2;
								y1=(y1+(atoi(&h4[0])*60));
								z1=(z1+(y1/60));
								w1=(w1+(z1/60));
								tyfile<<x<<",h4,"<<k<<","<<a[r_id][coocoo].second<<",1,"<<w1<<":"<<z1%60<<":"<<y1%60<<","<<w1<<":"<<z1%60<<":"<<y1%60<<"\n";
								for(int l=coocoo+1;l<srlast-1;l++)
								{
									tyfile<<x<<",h4,"<<k<<","<<a[r_id][l].second<<","<<b<<",,\n";
									b++;
								}
								y1=y1%60;
								z1=z1%60;
								int y=(y1+sec);
								int z=(z1+(y/60));
								int w=(w1+(z/60));
								tyfile<<x<<",h4,"<<k<<","<<a[r_id][srlast-1].second<<","<<b<<","<<w<<":"<<z%60<<":"<<y%60<<","<<w<<":"<<z%60<<":"<<y%60<<"\n";
							}
						}
						else
						{
							int coocoo=srfirst-1;
							for(int k=1;k<=t4;k++)
							{
								int b=2;
								y1=(y1+(atoi(&h4[0])*60));
								z1=(z1+(y1/60));
								w1=(w1+(z1/60));
								tyfile<<x<<",h4,"<<k<<","<<a[r_id][coocoo].second<<",1,"<<w1<<":"<<z1%60<<":"<<y1%60<<","<<w1<<":"<<z1%60<<":"<<y1%60<<"\n";
								for(int l=coocoo-1;l>=srlast;l--)
								{
									tyfile<<x<<",h4,"<<k<<","<<a[r_id][l].second<<","<<b<<",,\n";
									b++;
								}
								y1=y1%60;
								z1=z1%60;
								int y=(y1+sec);
								int z=(z1+(y/60));
								int w=(w1+(z/60));
								tyfile<<x<<",h4,"<<k<<","<<a[r_id][srlast-1].second<<","<<b<<","<<w<<":"<<z%60<<":"<<y%60<<","<<w<<":"<<z%60<<":"<<y%60<<"\n";
							}
						}
					}
				}
				int t5=atoi(&tree[x].ll[0]);
				if(t5!=0)
				{
					sec=-1;
					if(sree[x].f5=="-1")
					{
						if(span=="-1")
						{

						}
						else
						{
							sec=180*(stof(span));
						}
					}
					else
					{
						sec=60*atoi(&sree[x].f5[0]);
					}
					if(sec!=-1)
					{
						int y1,z1,w1;
						if(sfirst>20.00)
						{
							y1=tm[x][2]-(atoi(&h5[0])*60),z1=tm[x][1],w1=tm[x][0];
						}
						else
						{
							y1=-(atoi(&h5[0])*60);z1=0;w1=20;
						}
						if(srfirst<srlast)
						{
							int coocoo=srfirst-1;
							for(int k=1;k<=t5;k++)
							{
								int b=2;
								y1=(y1+(atoi(&h5[0])*60));
								z1=(z1+(y1/60));
								w1=(w1+(z1/60));
								tyfile<<x<<",h5,"<<k<<","<<a[r_id][coocoo].second<<",1,"<<w1<<":"<<z1%60<<":"<<y1%60<<","<<w1<<":"<<z1%60<<":"<<y1%60<<"\n";
								for(int l=coocoo+1;l<srlast-1;l++)
								{
									tyfile<<x<<",h5,"<<k<<","<<a[r_id][l].second<<","<<b<<",,\n";
									b++;
								}
								y1=y1%60;
								z1=z1%60;
								int y=(y1+sec);
								int z=(z1+(y/60));
								int w=(w1+(z/60));
								tyfile<<x<<",h5,"<<k<<","<<a[r_id][srlast-1].second<<","<<b<<","<<w<<":"<<z%60<<":"<<y%60<<","<<w<<":"<<z%60<<":"<<y%60<<"\n";
							}
						}
						else
						{
							int coocoo=srfirst-1;
							for(int k=1;k<=t5;k++)
							{
								int b=2;
								y1=(y1+(atoi(&h5[0])*60));
								z1=(z1+(y1/60));
								w1=(w1+(z1/60));
								tyfile<<x<<",h5,"<<k<<","<<a[r_id][coocoo].second<<",1,"<<w1<<":"<<z1%60<<":"<<y1%60<<","<<w1<<":"<<z1%60<<":"<<y1%60<<"\n";
								for(int l=coocoo-1;l>=srlast;l--)
								{
									tyfile<<x<<",h5,"<<k<<","<<a[r_id][l].second<<","<<b<<",,\n";
									b++;
								}
								y1=y1%60;
								z1=z1%60;
								int y=(y1+sec);
								int z=(z1+(y/60));
								int w=(w1+(z/60));
								tyfile<<x<<",h5,"<<k<<","<<a[r_id][srlast-1].second<<","<<b<<","<<w<<":"<<z%60<<":"<<y%60<<","<<w<<":"<<z%60<<":"<<y%60<<"\n";
							}
						}
					}
				}
			}
		}
	}
	tyfile.close();
}
