#include<bits/stdc++.h>
using namespace std;

unsigned int numBuffers, bufferSize;
unsigned int inputSize, outputSize;
queue<int> inputBuffer, outputBuffer;

class HashTable
{
	int num_records;
	int num_buckets;
	vector<vector<int>> buckets;
	vector<vector<int>> overflow;

	public:

	HashTable()
	{
		num_records = 0;
		num_buckets = 2;
		buckets = vector<vector<int>>(num_buckets);
		overflow = vector<vector<int>>(num_buckets);
	}

	unsigned int hash(int x)
	{
        return (unsigned int)(x % num_buckets + num_buckets) % num_buckets;
    }

	bool isPresent(int x)
	{
		// cout<<"Entered isPresent\n";
		unsigned int k = hash(x);
        if(k >= buckets.size()) {
            k -= (num_buckets/2);
        }
        for(auto ele:buckets[k])
        {
            if(ele == x)
                return true;
        }
        for(auto ele:overflow[k])
        {
   			if(ele == x)
   				return true;
        }

        return false;
	}

	void insert(int x)
	{
		// cout<<"Entered insert:\n";
		num_records++;
		unsigned int k = hash(x);
        if(k >= buckets.size())
        {
            k -= (num_buckets/2);
        }
        if(buckets[k].size() < (bufferSize))
        {
            buckets[k].push_back(x);
        }
        else
        {
            overflow[k].push_back(x);
        }

        while(100.0*double(num_records)/(double(buckets.size())*double(bufferSize)) >= 75)
        {
            buckets.push_back(vector<int>());
            overflow.push_back(vector<int>());
            num_buckets = pow(2,ceil(log2(double(buckets.size()))));
            k = buckets.size()-1-num_buckets/2;
            vector<int> v;
            for(auto ele:buckets[k]) {
	            v.push_back(ele);
	        }
	        buckets[k].clear();
	        for(auto ele:overflow[k])
	        {
		        v.push_back(ele);
		    }
		    overflow[k].clear();
            for(auto ele:v) {
                buckets[hash(ele)].push_back(ele);
            }
        }
	}

	void print() {
        for(unsigned int i = 0; i < buckets.size(); i++) {
            cout<<i<<" --> ";
	        for(auto ele:buckets[i])
	        {
	            cout<<ele<<' ';
	        }
	        for(auto ele:overflow[i])
	        {
	            cout<<ele<<' ';
	        }
	        cout<<'\n';
        }
        cout<<'\n';
    }
}h;

void clearOutput()
{
    while(!outputBuffer.empty())
    {
    	cout<<outputBuffer.front()<<'\n';
        outputBuffer.pop();
        
    }
}

void clearInput()
{
    while(!inputBuffer.empty())
    {
        if(!h.isPresent(inputBuffer.front()))
        {
        	int ix = inputBuffer.front();
        	outputBuffer.push(ix);
            h.insert(ix);
            if(outputBuffer.size() == outputSize)
            {
                clearOutput();
            }
        }
        inputBuffer.pop();
    }
}

int main(int argc, char *argv[]) {
    if(argc < 4) {
        cout<<"Invalid command line\n";
    }
    else if(atoi(argv[2]) < 2 || atoi(argv[3]) < 4)
    {
    	cout<<"Invalid buffers, should be M>=2 and B>=4\n";
    }
    else
    {	
    	ifstream file(argv[1]);
        numBuffers = atoi(argv[2]);
        bufferSize = atoi(argv[3])/sizeof(int);

        inputSize = (numBuffers - 1)*(bufferSize);
        outputSize = bufferSize;
        inputBuffer = queue<int>();
        outputBuffer = queue<int>();
        int x;
        while(file >> x) {
            if(inputBuffer.size() < inputSize) {
                inputBuffer.push(x);
            }
            else {
                clearInput();
                inputBuffer.push(x);
            }
        }
        clearInput();
        clearOutput();
        // h.print();
        return 0;
    }
}