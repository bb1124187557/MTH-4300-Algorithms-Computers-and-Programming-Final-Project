#include<vector>
#include<random>

bool isMatch(const vector<int>& mainV, const vector<int>& vec)
{
	for(int i=0; i<vec.size(); i++)
	{
		if(vec[i]!=mainV[i])
			return false;
	}
	return true;
}

double exactExpectedValue(double p,int n,vector<int>tempV){
	vector< vector<int> > v;

	double toss=0;
	int input;
	v.push_back(tempV);
	for(int i=0; i<n-1; i++)
	{
		tempV.erase(tempV.begin());
		v.push_back(tempV);
	}

	for(int i=0; i<v.size(); i++)
	{
		if(isMatch(v[0], v[i]))
		{
			int h=0;
			for(int j=0; j<v[i].size(); j++)
			{
				if(v[i][j]==1)
					h++;
			}
			toss+=(pow(1/p, h)*pow(1/(1-p), v[i].size()-h));
		}
	}
	return toss;
}

int coinValue(int p){
  std::random_device device;
  std::mt19937 generator(device());
  std::uniform_int_distribution<int> distribution(1,100);
  int n;
  n=distribution(generator);
  if(n<=p){
    return 1;
  }
  else{
    return 0;
  }
}

int countLen(int* seq,int p,int n){
  int newn;
  vector<int> vec;
  for(int i=0;i<n;++i){
    newn=coinValue(p);
    vec.push_back(newn);
  }
  int indicator=0;
  while(indicator==0){
    int size=vec.size();
    for(int j=0;j<n;++j){
      if(seq[j]!=vec[size-n+j]){
				//int total=0;
        indicator=1;
      }
    }
    if(indicator==1){
      newn=coinValue(p);
      vec.push_back(newn);
      indicator=0;
    }
    else{
      indicator=1;
    }

  }
  return vec.size();
}
