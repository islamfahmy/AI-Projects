#include <bits/stdc++.h>
using namespace std;
set<string> vis ;
int DFSLevel = 0 ;
int ManLevel = 0 ;
int EclLevel = 0;
int BFSLevel = 0 ;
int NodesEcl = 0;
int NodesMan = 0 ;
int NodesBFS = 0;
int NodesDFS = 0;
int dx[] = {0,0,-1,1};
int dy[] = {-1,1,0,0};
struct TreeNode {
    int zero;
    string val ;
    TreeNode *Parent;
    int dist ;
    TreeNode(string s ,TreeNode * par =NULL,int dis=0):val(s){
        Parent = par;
        dist = 0 ;
        for(int i =0;i<s.size();i++)
            if(s[i]=='0')
                zero = i;
    }
};
int goal(string &s)
{
    int match =0;
    for(int i =1;i<9;i++)
        if(s[i]==s[i-1]+1)
            match++;
    if(match==8)
        return 1;
    return 0 ;
}
void print(string s )
{
    for(int i =0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            cout<<s[i*3+j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}
int HeuristicManhattan(string S)
{   int ret = 0 ;
    for (int i=0; i < 9;i++){
        int val = S[i]-'0';
        ret+= abs(val%3-i%3)+abs(val/3-i/3);
    }
    return ret ;
}
int HeuristicEuclidean(string S)
{
    int ret = 0 ;
    for (int i=0; i < 9;i++){
        int val = S[i]-'0';
        ret+= sqrt( (val%3-i%3)*(val%3-i%3)+ (val/3-i/3)*(val/3-i/3) );
    }
    return ret ;
}
struct compare{
public:
    bool operator()(pair < int,TreeNode* > x, pair < int,TreeNode* > y) {
        return x.first>y.first;
    }
};
void AStar(TreeNode *N,int Heurisitc(string s),int man)
{
    priority_queue< pair < int,TreeNode* >, vector< pair < int,TreeNode* > >, compare > pq;
    map<string ,int> mp ;
    mp.insert({N->val,0});
    pair<int,TreeNode *> curr ;
    pq.push({0,N});
    while(!pq.empty())
    {
        curr= pq.top();
        pq.pop();

        N = curr.second;
        if(mp[N->val]!=N->dist)
        {
            continue ;
        }
        if(goal(N->val))
        {
            while(N)
            {if(man)
                    ManLevel++;
                else
                    EclLevel++;
                print(N->val);
                N=N->Parent;
            }
            return ;
        }
        int y = N->zero/3,x = N->zero%3,newX,newY;
        if(man)
            NodesMan++;
        else
            NodesEcl++;
        for(int i =0;i<4;i++)
        {
            int dx[] = {0,0,-1,1};
            int dy[] = {-1,1,0,0};
            newX= x+dx[i];
            newY= y+dy[i];
            if(newX>2||newX<0||newY>2||newY<0)
                continue ;
            string newStr = N->val;
            swap(newStr[y*3+x],newStr[newY*3+newX]);
            int hur = Heurisitc(newStr);
            if( mp.find(newStr)==mp.end() || mp[newStr]> (N->dist+1))
            {
                TreeNode * child = new TreeNode(newStr,N,N->dist+1);
                mp[newStr]=child->dist;
                pq.push({hur+N->dist+1,child});
            }
        }
    }
}
void bfs(TreeNode *N)
{   vis.clear();
    queue <TreeNode *> q ;
    q.push(N);
    while(!q.empty())
    {
        N= q.front();
        q.pop();
        if(vis.find(N->val) != vis.end())
            continue ;
        if(goal(N->val))
        {
            while(N)
            {BFSLevel++;
                print(N->val);
                N=N->Parent;
            }
            return ;
        }
        vis.insert(N->val);
        int y = N->zero/3,x = N->zero%3,newX,newY;
        NodesBFS++;
        for(int i =0;i<4;i++)
        {
            int dx[] = {0,0,-1,1};
            int dy[] = {-1,1,0,0};

            newX= x+dx[i];
            newY= y+dy[i];
            if(newX>2||newX<0||newY>2||newY<0)
                continue ;
            string newStr = N->val;
            swap(newStr[y*3+x],newStr[newY*3+newX]);
            TreeNode * child = new TreeNode(newStr);
            q.push(child);
            child->Parent = N;
        }
    }
}
int  dfs(TreeNode * N)
{
    stack <TreeNode *> s;
    s.push(N);
    while(!s.empty())
    {
        N=s.top();
        s.pop();
        if(vis.find(N->val) != vis.end())
            continue;
        if(goal(N->val))
        {
            print(N->val);
            return  1;
        }
        vis.insert(N->val);
        int y = N->zero/3,x = N->zero%3,newX,newY;
        NodesDFS++;
        for(int i =0;i<4;i++)
        {
            int dx[] = {0,0,-1,1};
            int dy[] = {-1,1,0,0};
            newX= x+dx[i];
            newY= y+dy[i];
            if(newX>2||newX<0||newY>2||newY<0)
                continue ;
            string newStr = N->val;
            swap(newStr[y*3+x],newStr[newY*3+newX]);
            TreeNode * child = new TreeNode(newStr);
            if(dfs(child))
            { DFSLevel++;
                print(N->val);
                return 1 ;
            }
        }
    }
    return 0;
}
string Generate(int n )// it dosn't always work don't count on it check shorturl.at/inJV4
{
    vector<int> arr(n,0);
    string ret  ;
    int found = n ;
    srand(time(NULL));
    while(found){
        int index = rand() % n;
        if(arr[index])
            continue ;
        found -- ;
        ret.push_back(index+'0');
        arr[index]=1 ;
    }
    return ret ;
}
int main()
{
    TreeNode * T = new TreeNode("128354670");
    cout<<"DFS:\n";
    dfs(T);
    cout<<"BFS:\n";
    bfs(T);
    cout<<"AStar:\n";
    AStar(T, HeuristicManhattan, 1);
    AStar(T,HeuristicEuclidean,0);
    cout << "Level DFS: " << DFSLevel << endl;
    cout << "Level Man A*:  " << ManLevel << endl;
    cout << "Level Ecl A*:  " << EclLevel << endl;
    cout << "Level BFS: " << BFSLevel << endl;
    cout << "Nodes BFS: " << NodesBFS << "\nNodes DFS: " << NodesDFS << endl;
    cout << "Nodes Manhattan: " << NodesMan << "\nNodes Euclidean: " << NodesEcl << endl;
}