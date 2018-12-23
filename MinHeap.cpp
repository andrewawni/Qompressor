#include "../include/MinHeap.hpp"

MinHeap::MinHeap() {
    m_root = new MinHeapNode();
}

void MinHeap::GenerateMinHeap(map<int,string> mp)
{
    MinHeapNode* temp = m_root;
    for(auto current : mp)
    {
        int key = current.first;
        std::string code = current.second;

        temp = m_root;
        for(int i = 0; i<code.size(); i++)
        {
            
            temp->isLeaf = false;
            int val;
            if(i==code.size()-1)
                val = key;
            else
            {
                val = -1;
            }
    
            MinHeapNode* newNode = new MinHeapNode(val);
                
            if(code[i] == '0')
            {   
                if(temp->left == 0)
                    temp->left = newNode;
                temp = temp->left;
            }
            else
            {
                if(temp->right == 0)
                    temp->right = newNode;
                temp = temp->right;
            }
        }
    }
}

void MinHeap::Traverse(MinHeapNode* root)
{
    if(root == 0)
        return;
    
    cout << root->m_data << " " << root->isLeaf<<'\n';
    Traverse(root->left);
    Traverse(root->right); 

}
void MinHeap::Get(string temp)
{
    MinHeapNode* n = m_root;
    for(int i = 0; i<temp.size(); i++)
    {
        if(temp[i] == '0')
            n = n->left;
        else
            n = n->right;
    }
    // if(n!=0)
     cout << n->m_data;
}

MinHeapNode* MinHeap::GetRoot()
{
    return m_root;
}

MinHeap::~MinHeap() {

}