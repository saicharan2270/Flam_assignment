class LRUCache {
public:
    queue<int>que;
    
    int capacity,sz;
    
    vector<int>keyVal,freq;

    LRUCache(int cap) {
        sz=0;
        capacity=cap;
        keyVal.resize(10001,-1);
        freq.resize(10001,0);
    }
    
    int get(int key) {
        if(keyVal[key]==-1)
            return -1;
            
        que.push(key);
        
        freq[key]++;
        
        return keyVal[key];
    }
    
    void put(int key, int value) {
        if(keyVal[key]==-1)
        {
            while(sz>=capacity)
            {
                int tp=que.front();
                
                que.pop();
                
                if(freq[tp]==1)
                {
                    keyVal[tp]=-1;
                    sz--;
                }
                
                freq[tp]--;
            }
            
            keyVal[key]=value;
            que.push(key);
            freq[key]=1;
            sz++;
        }
        else
        {
            keyVal[key]=value;
            que.push(key);
            freq[key]++;
        }
    }
};
