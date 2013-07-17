#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <set>
#include <stack>

using namespace std;

int main()
{
  string ipfile, opfile, rrfile;
	ipfile = "input.txt";
	opfile = "sonali_output.txt";
	rrfile = "meta.RRF";
	ifstream ip(ipfile), meta(rrfile);
	ofstream to(opfile);
	char ipline[35], metaline[150];
	string token, cui;
	stack<string> children;
	set<string> uniques;
	pair<set<string>::iterator,bool> pa;

	// index
	streampos index[500];

	for(;;)
	{
		// get the input line
		if(ip.eof())
			break;
		ip.getline(ipline, 35);
		char *pch = strtok(ipline, "\t");
		cui = string(pch);
		to<<pch<<"\t";
		pch = strtok(0, "\n");
		to<<pch<<"\t";

		children.push(cui);
		uniques.clear();
		uniques.insert(cui);

		while(!children.empty())
		{
			string cui1 = children.top();
			//if(cui1 == "C0032285")
			//	__asm int 3;
			children.pop();
			meta.clear();
			meta.seekg(0, ios::beg);
			bool flag = false;
			for(;;)
			{
				if(meta.eof())
					break;
				meta.getline(metaline, 150);
				pch = strtok(metaline, "|");
				if(pch)
					token = pch;
				else
					continue;
				if(token != cui1)
				{
					if(!flag)
						continue;
					else break;
				}
				flag = true;
				for(int i = 0;i < 3;i++)
					pch = strtok(0, "|");
				if(!strcmp(pch, "CHD"))
				{
					pch = strtok(0, "|");
					pa = uniques.insert(string(pch));
					if(pa.second)
						children.push(string(pch));
					to<<pch<<";";
				}
			}// end inner for
		}// end while
		to<<endl;
	}// end outer for

	ip.close();
	meta.close();
	to.close();
}
