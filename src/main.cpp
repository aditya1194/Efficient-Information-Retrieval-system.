#include<bits/stdc++.h>
#include<sys/stat.h>
#include "porterStemmer.cpp"
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

unordered_set<string> stopwords;
static char a[100];
FILE * fp;
static char  path[19]="../Index/files/ ";
static char path1[19]="../Index/files/ ";
int cnt;

struct Node
{
	int noOfWords;
	//bool stop;
	Node * nxt[26];
	vector<PII> categories[6];		//6 vectors corresponding to each category
	Node()
	{
		//stop=false;
		noOfWords=0;
		memset(nxt,0,sizeof(nxt));
	}
	Node * getNode(char c)
	{
		int pos=c-'a';
		if(nxt[pos]==NULL)
			nxt[pos]=new Node();
		return nxt[pos];
	}
};

class Trie
{
	public:
		Node * root;
		Trie()
		{
			root=new Node();
		}
		void insert(string s,int index,int category)		//category  here signifies the type of data i.e whether it is title,reference,etc.
		{
			if(s=="")
				return;
			Node * cur=root;
			int i,len=s.size();
			for(i=0;i<len;i++)
				cur=cur->getNode(s[i]);
		//	if(cur->stop==false)
			{
				cur->noOfWords++;
				int l=cur->categories[category].size();
				if(l>0 && cur->categories[category][l-1].S==index)
					cur->categories[category][l-1].F++;
				else
					cur->categories[category].pb(mp(1,index));
				/*if(cur->noOfWords > threshold)
				{
					cur->stop=true;
					//	stopWords.insert(s);
					REP(i,6)
						cur->categories[i].clear();
				}*/
			}
		}
		void trieTraversal(string s,Node * cur)
		{
			int i=0,j;
			if(cur->noOfWords>0)
			{

				REP(i,6)
					sort(cur->categories[i].begin(),cur->categories[i].end());
				//cout<<s<<endl;
				REP(i,6)
				{

					path[15]=s[0];
					int l=cur->categories[i].size();
					if(s.size()>1)
						path[16]=s[1];
					else
						path[16]='a';
					path[17]='/';
					path[18]=(char)('0'+i);
					ofstream outfile;
					outfile.open(path,ios_base::app);
					//fprintf(fp,"%s\n",s.c_str());
					if(l)
					{
						outfile<<s<<"#";
						REP(j,l)
						{
							//	fprintf(fp,"%d %d ",cur->categories[i][j].S,cur->categories[i][j].F);
							outfile<<cur->categories[i][j].S<<" "<<cur->categories[i][j].F<<"#";
						}
						outfile<<endl;
					}
				}
				cur->noOfWords=0;
				REP(i,6)
					cur->categories[i].clear();
			}
			REP(i,26)
			{
				if(cur->nxt[i])
				{
					trieTraversal(s+char('a'+i),cur->nxt[i]);
				//	cur->nxt[i]=NULL;

				}

			}
		}
};


void createFiles()
{
	int i,j,k;
	for(i=0;i<26;i++)
		for(j=0;j<26;j++)
		{
			path[15]=(char)('a'+i);
			path[16]=(char)('a'+j);
			mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		}
}

void sortAndMerge()
{	
	int i,j,k;
	
	path[17]='/';	
	for(i=0;i<26;i++)
	{
		path[15]=(char)('a'+i);
		for(j=0;j<26;j++)
		{
			path[16]=(char)('a'+j);
			for(k=0;k<6;k++)
			{

				//cout<<i<<"	"<<j<<"		"<<k<<endl;
				path[18]=(char)('0'+k);
				vector<pair<string,vector<PII> > > data;
				ifstream infile;
				infile.open(path);
				string line;
				while(getline(infile,line))
				{
					pair<string,vector<PII> > temp;
					stringstream inputStream(line);
					string words;
					getline(inputStream,words,'#');
					temp.F=words;
					while(getline(inputStream,words,'#'))
					{
						//cout<<words<<endl;
						int x=0,l=words.size(),y=0,p;
						for(p=0;p<l;p++)
						{
							if(words[p]==' ')
							{
								y=x;
								x=0;
							}
							else
								x=x*10+(words[p]-'0');
						}
						temp.S.pb(mp(y,x));	
					}
					data.pb(temp);
				}
				infile.close();
				sort(data.begin(),data.end());
				
				ofstream outfile;
				outfile.open(path,ios::out| ios::trunc);
				
				ofstream x;
				path1[15]=(char)('0'+k);
				x.open(path1,ios::out | ios::app);
			//	printf("%s\n",path1);	
				int p,q,len=data.size();

				if(len)
				{
					cnt++;
					long pos=outfile.tellp();
					x<<data[0].F<<" "<<pos<<endl;
			//		outfile<<data[0].F<<"#";
					int len1=data[0].S.size();
					for(q=0;q<len1;q++)
						outfile<<data[0].S[q].F<<" "<<data[0].S[q].S<<"#";
				}
				for(p=1;p<len;p++)
				{
					if(data[p].F!=data[p-1].F)
					{
						outfile<<endl;
						long pos=outfile.tellp();
						//outfile<<data[p].F<<"#";
						x<<data[p].F<<" "<<pos<<endl;
						cnt++;
					}
					int len1=data[p].S.size();
					for(q=0;q<len1;q++)
						outfile<<data[p].S[q].F<<" "<<data[p].S[q].S<<"#";
				}
				x.close();
				outfile.close();
			}
		}
	}
}



string removeSpecialCharacters(string s)
{
	string ret="";
	int i,l=s.size();
	for(i=0;i<l;i++)
	{
		if(s[i]>='a' && s[i]<='z')
			ret+=s[i];
		else if(s[i]>='A' && s[i]<='Z')
			ret+=(char)('a'+s[i]-'A');
		else 
			ret+=' ';
	}
	return ret;
}

string tokenize(string s)
{
	int len=s.size(),i;
	string ret="";
	for(i=0;i<len;i++)
	{
		if(!(s[i]>='a' && s[i]<='z'))
			break;
		ret+=s[i];
	}
	return ret;
}

string processing(string s)
{
	s=removeSpecialCharacters(s);
	s=tokenize(s);
	int i,l=s.size();
	for(i=0;i<l;i++)
		a[i]=s[i];
	l=stem(a,0,l-1);
	string k="";
	for(i=0;i<=l;i++)
		k+=s[i];
	return k;
}

int main()
{
	cout<<"Xml file has now been parsed"<<endl;
	createFiles();
	//std::ios_base::sync_with_stdio( false );
	Trie tr;
	ifstream parse;
	string s;
	string line;

	parse.open("stopwords");			//Taking a list of stopwords from a file
	while(getline(parse,line))
		stopwords.insert(line);
	parse.close();
	//cout<<stopwords.size()<<endl;
			
	parse.open("../parsedFile");
	vector<string> temp;
	int id,cat=0,doc_cnt=0,f=0;		//number of documents in the data given
	bool open=false;
	if(parse.is_open())
	{
		while(getline(parse,line))
		{
			string t;
			if(line.find("&&title&&:")!=-1)
				cat=0;
			else if(line.find("&&pid&&:")!=-1)
				cat=1;
			else if(line.find("&&infobox&&")!=-1)
				cat=2;
			else if(line.find("&&text&&")!=-1)
				cat=3;
			else if(line.find("&&reference&&")!=-1)
				cat=4;
			else if(line.find("&&link&&")!=-1)
				cat=5;
			else if(line.find("&&category&&")!=-1)
				cat=6;
			if(line.find("&&:")!=-1)
			 {
				  open=!open;
				//  continue;
			  }
			stringstream inputStream(line);
			string words;
			while(getline(inputStream,words,' '))
			{

				string word="";
				if(cat==0)
				{
					if(!open && doc_cnt%12000==0 && f)
					{
						//cnt=0;
						cout<<doc_cnt<<endl;
						f=0;
						tr.trieTraversal("",tr.root);
					}
					word=processing(words);
					if(stopwords.find(word)==stopwords.end())
						temp.pb(word);
				}
				else if(cat==1)
				{
					//	cout<<words<<endl;
					int newid=0;
					int l=words.size(),i;
					for(i=0;i<l;i++)
					{
						if(words[i]>='0' && words[i]<='9')
							newid=newid*10+(int)(words[i]-'0');
					}
					if(newid==0)
						continue;
					id=newid;
					f=1;
					doc_cnt++;
					l=temp.size();
					for(i=0;i<l;i++)
						tr.insert(temp[i],id,0);
					temp.clear();
				}
				word=processing(words);
				if(stopwords.find(word)!=stopwords.end())
					continue;
				if(cat==2)
					tr.insert(word,id,1);
				else if(cat==3)
					tr.insert(word,id,2);
				else if(cat==4)
					tr.insert(word,id,3);
				else if(cat==5)
					tr.insert(word,id,4);
				else if(cat==6)
					tr.insert(word,id,5);
			}
		}
	}
	parse.close();
	// fclose(stdout);
	//cout<<cnt<<endl;
	tr.trieTraversal("",tr.root);
	int i,j,k;
	fclose (stdin);
	sortAndMerge();		//sorts the files and merges the duplicate entries
	cout<<doc_cnt<<endl;
	cout<<cnt<<endl;
	return 0;
}
