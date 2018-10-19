#include <iostream>
using namespace std;

class BTreeNode{
  bool leaf;
  int n,t,*keys;
  BTreeNode **childs;
public:
  BTreeNode(int _t, bool _leaf){
    t=_t;
    leaf=_leaf;
    keys=new int[2*t-1];
    childs=new BTreeNode*[2*t];
    n=0;
  }
  void traverse(){
    for(int i=0;i<n;i++){
      if(!leaf)
        childs[i]->traverse();
      cout<<keys[i]<<" ";
    }
    if(!leaf) childs[n]->traverse();
  }
  BTreeNode* search(int val){
    int i=0;
    while(i<n && keys[i]<val) i++;

    if(keys[i]==val) return this;

    if(leaf) return NULL;

    return childs[i]->search(val);
  }
  void splitChild(int i, BTreeNode* y){
    BTreeNode *z=new BTreeNode(y->t,y->leaf);
    z->n=t-1;

    for(int j=0;j<t-1;j++)
      z->keys[j]=y->keys[j+t];

    if(!y->leaf)
      for(int j=0;j<t;j++)
        z->childs[j]=y->childs[j+t];

    y->n=t-1;
    for(int j=n;j>i;j--)
      childs[j+1]=childs[j];
    childs[i+1]=z;

    for(int j=n-1;j>=i;j--)
      keys[j+1]=keys[j];

    keys[i]=y->keys[t-1];
    n++;
  }
  void insertNotFull(int k){
    int i=n-1;

    if(leaf){
      while(i>=0 && keys[i]>k){
        keys[i+1]=keys[i];
        i--;
      }
      keys[i+1]=k;
      n++;
    }else{
      while(i>=0 && keys[i]>k) i--;

      if(childs[i+1]->n==2*t-1){
        splitChild(i+1,childs[i+1]);
        if(keys[i+1]<k) i++;
      }
      childs[i+1]->insertNotFull(k);
    }
  }
  int findKey(int k){
    int i=0;
    while(i<n && keys[i]<k) i++;
    return i;
  }
  void remove(int k){
    int ind=findKey(k);
    if(ind<n && keys[ind]==k){
      if(leaf){
        removeFromLeaf(ind);
      }else{
        removeFromNonLeaf(ind);
      }
    }else{
      if(leaf){
        cout<<k<<" does not exist."<<endl;
        return;
      }

      bool flag = (n == ind);
      if(childs[ind]->n < t) fill(ind);

      if(flag && ind>n)
        childs[ind-1]->remove(k);
      else
        childs[ind]->remove(k);
    }
  }
  void removeFromLeaf(int idx){
    for(int i=idx;i<n-1;i++) keys[i]=keys[i+1];
    n--;
  }
  void removeFromNonLeaf(int idx){
    int k=keys[idx];
    if(childs[idx]->n >= t){
      int pred=getPred(idx);
      keys[idx]=pred;
      childs[idx]->remove(pred);
    }else if(childs[idx+1]->n >= t){
      int succ=getSucc(idx);
      keys[idx]=succ;
      childs[idx+1]->remove(succ);
    }else{
      merge(idx);
      childs[idx]->remove(k);
    }
  }
  int getPred(int idx){
    BTreeNode *cur=childs[idx];

    while(!cur->leaf)
      cur=cur->childs[cur->n];

    return cur->keys[cur->n-1];
  }
  int getSucc(int idx){
    BTreeNode *cur=childs[idx+1];

    while(!cur->leaf)
      cur=cur->childs[0];

    return cur->keys[0];
  }
  void fill(int idx){
    if(idx!=0 && childs[idx-1]->n >= t){
      borrowFromPrev(idx);
    }else if(idx!=n && childs[idx+1]->n >=t){
      borrowFromNext(idx);
    }else{
      if(idx!=n)
        merge(idx);
      else
        merge(idx-1);
    }
  }
  void borrowFromPrev(int idx){
    BTreeNode *child=childs[idx];
    BTreeNode *sibling=childs[idx-1];

    for(int i=child->n-1;i>=0;i--)
      child->keys[i+1]=child->keys[i];

    if(!child->leaf){
      for(int i=child->n;i>=0;i--)
        child->childs[i+1]=child->childs[i];
      child->childs[0]=sibling->childs[sibling->n];
    }

    child->keys[0]=keys[idx-1];

    keys[idx-1]=sibling->keys[sibling->n-1];

    sibling->n--;
    child->n++;
  }
  void borrowFromNext(int idx){
    BTreeNode *child=childs[idx];
    BTreeNode *sibling=childs[idx+1];

    child->keys[child->n]=keys[idx];

    if(!child->leaf){
      child->childs[child->n+1]=sibling->childs[0];
    }

    keys[idx]=sibling->keys[0];

    for(int i=0;i<sibling->n-1;i++){
      sibling->keys[i]=sibling->keys[i+1];
    }

    if(!sibling->leaf){
      for(int i=0;i<sibling->n;i++){
        sibling->childs[i]=sibling->childs[i+1];
      }
    }

    sibling->n--;
    child->n++;
  }
  void merge(int idx){
    BTreeNode *child=childs[idx];
    BTreeNode *sibling=childs[idx+1];

    child->keys[t-1]=keys[idx];

    for(int i=0;i<sibling->n;i++){
      child->keys[i+t]=sibling->keys[i];
    }

    if(!child->leaf){
      for(int i=0;i<=sibling->n;i++){
        child->childs[i+t]=sibling->childs[i];
      }
    }

    for(int i=idx;i<n-1;i++){
      keys[i]=keys[i+1];
    }

    for(int i=idx+1;i<n;i++){
      childs[i]=childs[i+1];
    }

    child->n+=sibling->n+1;
    n--;
    delete(sibling);
  }
  friend class BTree;
};

class BTree{
  BTreeNode* root;
  int t;
public:
  BTree(int _t){
    t=_t;
    root=NULL;
  }
  void traverse(){
    if(root!=NULL) root->traverse();
  }
  BTreeNode* search(int val){
    if(root!=NULL) return root->search(val);
    return NULL;
  }
  void insert(int k){
    if(root==NULL){
      root=new BTreeNode(t, true);
      root->keys[0]=k;
      root->n=1;
    }else{
      if(root->n==2*t-1){
        BTreeNode *z = new BTreeNode(t,false);
        z->childs[0]=root;
        z->splitChild(0,root);
        z->childs[z->keys[0]<k?1:0]->insertNotFull(k);
        root=z;
      }else{
        root->insertNotFull(k);
      }
    }
  }
  void remove(int k){
    if(root==NULL){
      cout<<"Tree is empty"<<endl;
    }else{
      root->remove(k);
      if(root->n==0){
        BTreeNode *tmp=root;
        if(root->leaf){
          root=NULL;
        }else{
          root=root->childs[0];
        }
        delete tmp;
      }
    }
  }
};

int main(){
  BTree t(3);

  t.insert(1);
  t.insert(3);
  t.insert(7);
  t.insert(10);
  t.insert(11);
  t.insert(13);
  t.insert(14);
  t.insert(15);
  t.insert(18);
  t.insert(16);
  t.insert(19);
  t.insert(24);
  t.insert(25);
  t.insert(26);
  t.insert(21);
  t.insert(4);
  t.insert(5);
  t.insert(20);
  t.insert(22);
  t.insert(2);
  t.insert(17);
  t.insert(12);
  t.insert(6);

  cout << "Traversal of tree constructed is\n";
  t.traverse();
  cout << endl;

  t.remove(6);
  cout << "Traversal of tree after removing 6\n";
  t.traverse();
  cout << endl;

  t.remove(13);
  cout << "Traversal of tree after removing 13\n";
  t.traverse();
  cout << endl;

  t.remove(7);
  cout << "Traversal of tree after removing 7\n";
  t.traverse();
  cout << endl;

  t.remove(4);
  cout << "Traversal of tree after removing 4\n";
  t.traverse();
  cout << endl;

  t.remove(2);
  cout << "Traversal of tree after removing 2\n";
  t.traverse();
  cout << endl;

  t.remove(16);
  cout << "Traversal of tree after removing 16\n";
  t.traverse();
  cout << endl;

  return 0;
}
