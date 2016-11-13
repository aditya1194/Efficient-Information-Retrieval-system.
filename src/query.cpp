#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(i=a;i<b;i++)
#define REP(i,a) for(i=0;i<a;i++)
#define LLD long long int
#define MOD 1000000007
#define si(n) scanf("%d",&n);
#define si2(n,m) scanf("%d%d",&n,&m);
#define sl(n) scanf("%lld",&n);
#define TR(container,it) for(typeof(container.begin()) it=container.begin();it!=container.end();it++)
#define F first
#define S second
#define pb push_back
#define mp make_pair
typedef pair<int,int> PII;

map<int,string> idToName;		
vector<string> query;
set<PII> results;		//results is a pair where 2nd term indicates id of the document and first term indicates score of that document
set<PII>::reverse_iterator it;
void calculate()
{
	int i,l=query.size(),j;
	vector<PII> list;
	for(i=0;i<l;i++)
	{
		string qi=query[i];
		//Open the corresponding related and read the posting list into list vector
		//Iterate over the posting list and update the score of each document
		int l1=list.size();
		for(j=0;j<l1;j++)
		{
			int x=list[j].F,y=list[j].S;

		}
	}
}

int main()
{
	ifstream in;
	in.open("../Index/name");
	string line;
	while(getline(in,line))
	{
		int i,l=line.size(),x=0;
		for(i=0;i<l && line[i]!=' ';i++)
			x=x*10+(line[i]-'0');
		i++;
		string k="";
		for(;i<l;i++)
			k+=line[i];
		idToName[x]=k;
	}
	int q;
	cin>>q;
	while(q--)
	{
		string x,y="";
		getline(cin,x);
		int i,l=x.size();
		for(i=0;i<l;i++)			//Breaking the query into individual words
		{
			if(x[i]==' ')
			{
				query.pb(y);
				y="";
			}
			else
				y+=x[i];
		}
		calculate();
		query.clear();
		for(it=results.rbegin();it=results.rend();it++)			//Top 10 results
			cout<<idToName[it->S]<<endl;
	}	
	return 0;
}
