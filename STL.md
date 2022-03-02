## stack
```
stack<ListNode* > stk;
stk.push()
//压入元素
stk.top()
//返回栈顶
stk.pop()
//删除栈顶，不返回元素


stk.empty()
stk.size()
```


map
```
map<int,int> mapp;
mapp.count(1)
//有没有
mapp.find(1) != mapp.end()
mapp.erase()
mapp[key] = val
//添加或修改元素


```

## set
```
set<char > sett;
sett.insert('a');
sett.erase('a');
sett.count('a') == 0
//判断有没有
```
ref
https://blog.csdn.net/u010183728/article/details/81913729


## queue 

queue<Treenode* > que;
que.push(node);
que.front();
que.pop();
que.size();
que.empty()
que.back()


## priority_queue
//升序队列
priority_queue <int,vector<int>,greater<int> > q;
//降序队列
priority_queue <int,vector<int>,less<int> >q;

q.top()

自定义元素需要重载运算符
struct tmp1 //运算符重载<
{
    int x;
    tmp1(int a) {x = a;}
    bool operator<(const tmp1& a) const
    {
        return x < a.x; //大顶堆
    }
};


https://blog.csdn.net/u010183728/article/details/81913729