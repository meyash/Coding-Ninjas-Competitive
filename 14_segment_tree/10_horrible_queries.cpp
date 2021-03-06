/*
World is getting more evil and it's getting tougher to get into the Evil League of Evil. Since the legendary Bad Horse has retired, now you have to correctly answer the evil questions of Dr. Horrible, who has a PhD in horribleness (but not in Computer Science). You are given an array of N elements, which are initially all 0. After that you will be given C commands. They are -
0 p q v - you have to add v to all numbers in the range of p to q (inclusive), where p and q are two indexes of the array.

1 p q - output a line containing a single integer which is the sum of all the array elements between p and q (inclusive)
Input
In the first line you'll be given T, number of test cases.

Each test case will start with N (N <= 100 000) and C (C <= 100 000). After that you'll be given C commands in the format as mentioned above. 1 <= p, q <= N and 1 <= v <= 10^7.
Output
Print the answers of the queries.
Input:
1
8 6
0 2 4 26
0 4 8 80
0 4 5 20
1 8 8 
0 5 7 14
1 4 8
Output:
80  
508
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void update(ll *tree,ll *lazy,ll s,ll e,ll i,ll l,ll r,ll v){
    if(s>e){
        return;
    }
    // if lazy updation remaining
    if(lazy[i]!=0){
        tree[i]+=(e-s+1)*lazy[i];
        if(s!=e){
            lazy[i*2]+=lazy[i];
            lazy[i*2+1]+=lazy[i];
        }
        lazy[i]=0;
    }
    // 3 cases
    // out
    if(l>e||r<s){
        return;
    }
    // in
    if(s>=l&&e<=r){
        tree[i]+=(e-s+1)*v;
        if(s!=e){
            lazy[i*2]+=v;
            lazy[i*2+1]+=v;
        }
        lazy[i]=0;
        return;
    }
    // partial
    ll mid=(s+e)/2;
    update(tree,lazy,s,mid,i*2,l,r,v);
    update(tree,lazy,mid+1,e,i*2+1,l,r,v);
    tree[i]=tree[i*2]+tree[i*2+1];
}

ll query(ll *tree,ll *lazy,ll s,ll e,ll i,ll l,ll r){
    if(s>e){
        return 0;
    }
    // check for lazy updation
    if(lazy[i]!=0){
        tree[i]+=(e-s+1)*lazy[i];
        if(s!=e){
            lazy[i*2]+=lazy[i];
            lazy[i*2+1]+=lazy[i];
        }
        lazy[i]=0;
    }
    // 3 cases
    // out
    if(l>e||r<s){
        return 0;
    }
    // in
    if(s>=l&&e<=r){
        return tree[i];
    }
    // partial
    ll mid=(s+e)/2;
    ll left=query(tree,lazy,s,mid,i*2,l,r);
    ll right=query(tree,lazy,mid+1,e,i*2+1,l,r);
    return left+right;
}

int main(){
    ll t;
    cin>>t;
    while(t--){
        ll n,c;
        cin>>n>>c;
        ll *tree=new ll[3*n]{};
        ll *lazy=new ll[3*n]{};
        while(c--){
            ll qtype;
            cin>>qtype;
            if(qtype==0){
                ll p,q,v;
                cin>>p>>q>>v;
                update(tree,lazy,1,n,1,p,q,v);
            }else{
                ll p,q;
                cin>>p>>q;
                ll ans=query(tree,lazy,1,n,1,p,q);
                cout<<ans<<"\n";
            }
        }
    }
    return 0;
}
