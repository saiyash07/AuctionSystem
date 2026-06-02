#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <algorithm>
using namespace std;

/* ==========================================================
                        P1
    Arrays + Linked List + File Organization
========================================================== */

struct Item
{
    int id;
    string name;
    int basePrice;
};

vector<Item> items;

struct Bidder
{
    string name;
    Bidder* next;

    Bidder(string n)
    {
        name = n;
        next = NULL;
    }
};

Bidder* head = NULL;

void addBidder(string name)
{
    Bidder* newNode = new Bidder(name);

    if(head == NULL)
    {
        head = newNode;
        return;
    }

    Bidder* temp = head;

    while(temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void displayBidders()
{
    if(head == NULL)
    {
        cout << "No Bidders Found\n";
        return;
    }

    Bidder* temp = head;

    while(temp != NULL)
    {
        cout << temp->name << " -> ";
        temp = temp->next;
    }

    cout << "NULL\n";
}

void saveToFile()
{
    ofstream file("auction.txt");

    for(auto item : items)
    {
        file << item.id << " "
            << item.name << " "
            << item.basePrice << endl;
    }

    file.close();

    cout << "Data Saved Successfully\n";
}

/* ==========================================================
                        P2
                Stack + Queue
========================================================== */

queue<string> bidQueue;
stack<string> undoStack;

void placeBidQueue(string bidder)
{
    bidQueue.push(bidder);
    undoStack.push(bidder);
}

void processQueue()
{
    if(bidQueue.empty())
    {
        cout << "No Bids Pending\n";
        return;
    }

    cout << "Processing Bid Of "
         << bidQueue.front() << endl;

    bidQueue.pop();
}

void undoBid()
{
    if(undoStack.empty())
    {
        cout << "Nothing To Undo\n";
        return;
    }

    cout << "Removed Bid Of "
         << undoStack.top() << endl;

    undoStack.pop();
}

/* ==========================================================
                        P3
            Searching + Sorting + Big O
========================================================== */

void displayItems()
{
    if(items.empty())
    {
        cout << "No Items Available\n";
        return;
    }

    cout << "\nAuction Items\n";

    for(auto item : items)
    {
        cout << "ID: " << item.id
             << " Name: " << item.name
             << " Price: " << item.basePrice
             << endl;
    }
}

/* Linear Search O(n) */

void linearSearchItem(int id)
{
    for(auto item : items)
    {
        if(item.id == id)
        {
            cout << "Found -> "
                 << item.name << endl;
            return;
        }
    }

    cout << "Item Not Found\n";
}

/* Binary Search O(log n) */

bool compareID(Item a, Item b)
{
    return a.id < b.id;
}

void binarySearchItem(int id)
{
    sort(items.begin(), items.end(), compareID);

    int l = 0;
    int r = items.size() - 1;

    while(l <= r)
    {
        int mid = (l + r) / 2;

        if(items[mid].id == id)
        {
            cout << "Found -> "
                 << items[mid].name << endl;
            return;
        }

        if(items[mid].id < id)
            l = mid + 1;
        else
            r = mid - 1;
    }

    cout << "Item Not Found\n";
}

/* Insertion Sort O(n²) */

void insertionSort()
{
    int n = items.size();

    for(int i=1;i<n;i++)
    {
        Item key = items[i];

        int j = i - 1;

        while(j >= 0 &&
              items[j].basePrice > key.basePrice)
        {
            items[j+1] = items[j];
            j--;
        }

        items[j+1] = key;
    }

    cout << "Insertion Sort Completed\n";
}

/* Merge Sort O(n log n) */

void merge(vector<int>& arr,int l,int m,int r)
{
    vector<int> temp;

    int i=l;
    int j=m+1;

    while(i<=m && j<=r)
    {
        if(arr[i] < arr[j])
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    while(i<=m)
        temp.push_back(arr[i++]);

    while(j<=r)
        temp.push_back(arr[j++]);

    for(int k=l;k<=r;k++)
        arr[k]=temp[k-l];
}

void mergeSort(vector<int>& arr,int l,int r)
{
    if(l>=r)
        return;

    int mid=(l+r)/2;

    mergeSort(arr,l,mid);
    mergeSort(arr,mid+1,r);

    merge(arr,l,mid,r);
}

/* ==========================================================
                        P4
          BST + BFS + DFS + Priority Queue
========================================================== */

struct TreeNode
{
    string category;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string c)
    {
        category = c;
        left = right = NULL;
    }
};

TreeNode* root = NULL;

TreeNode* insertCategory(TreeNode* root,string cat)
{
    if(root == NULL)
        return new TreeNode(cat);

    if(cat < root->category)
        root->left = insertCategory(root->left,cat);
    else
        root->right = insertCategory(root->right,cat);

    return root;
}

void inorder(TreeNode* root)
{
    if(root == NULL)
        return;

    inorder(root->left);
    cout << root->category << " ";
    inorder(root->right);
}

vector<int> graph[20];

void BFS(int start,int vertices)
{
    vector<bool> visited(vertices,false);

    queue<int> q;

    visited[start] = true;
    q.push(start);

    while(!q.empty())
    {
        int node = q.front();
        q.pop();

        cout << node << " ";

        for(int next : graph[node])
        {
            if(!visited[next])
            {
                visited[next] = true;
                q.push(next);
            }
        }
    }
}

void DFSUtil(int node,
             vector<bool>& visited)
{
    visited[node] = true;

    cout << node << " ";

    for(int next : graph[node])
    {
        if(!visited[next])
            DFSUtil(next,visited);
    }
}

void DFS(int start,int vertices)
{
    vector<bool> visited(vertices,false);

    DFSUtil(start,visited);
}

/* Priority Queue */

priority_queue<pair<int,string>> highestBid;

/* ==========================================================
                        MAIN
========================================================== */

int main()
{
    int choice;

    do
    {
        cout << "\n===== AUCTION PLATFORM =====\n";

        cout << "1. Add Item\n";
        cout << "2. Add Bidder\n";
        cout << "3. Display Bidders\n";
        cout << "4. Place Bid\n";
        cout << "5. Process Bid Queue\n";
        cout << "6. Undo Last Bid\n";
        cout << "7. Display Items\n";
        cout << "8. Linear Search\n";
        cout << "9. Binary Search\n";
        cout << "10. Insertion Sort\n";
        cout << "11. Add Category (BST)\n";
        cout << "12. Display Categories\n";
        cout << "13. Create Graph & BFS\n";
        cout << "14. Create Graph & DFS\n";
        cout << "15. Show Highest Bidder\n";
        cout << "16. Save Data To File\n";
        cout << "17. Merge Sort Demo\n";
        cout << "0. Exit\n";

        cin >> choice;

        switch(choice)
        {
        case 1:
        {
            Item item;

            cout << "Enter Item ID: ";
            cin >> item.id;

            cout << "Enter Item Name: ";
            cin >> item.name;

            cout << "Enter Base Price: ";
            cin >> item.basePrice;

            items.push_back(item);

            break;
        }

        case 2:
        {
            string name;

            cout << "Enter Bidder Name: ";
            cin >> name;

            addBidder(name);

            break;
        }

        case 3:
            displayBidders();
            break;

        case 4:
        {
            string bidder;
            int amount;

            cout << "Bidder Name: ";
            cin >> bidder;

            cout << "Bid Amount: ";
            cin >> amount;

            placeBidQueue(bidder);

            highestBid.push({amount,bidder});

            break;
        }

        case 5:
            processQueue();
            break;

        case 6:
            undoBid();
            break;

        case 7:
            displayItems();
            break;

        case 8:
        {
            int id;

            cout << "Enter ID: ";
            cin >> id;

            linearSearchItem(id);

            break;
        }

        case 9:
        {
            int id;

            cout << "Enter ID: ";
            cin >> id;

            binarySearchItem(id);

            break;
        }

        case 10:
            insertionSort();
            break;

        case 11:
        {
            string cat;

            cout << "Enter Category: ";
            cin >> cat;

            root = insertCategory(root,cat);

            break;
        }

        case 12:
            inorder(root);
            cout << endl;
            break;

        case 13:
        {
            int v,e;

            cout << "Vertices: ";
            cin >> v;

            cout << "Edges: ";
            cin >> e;

            for(int i=0;i<20;i++)
                graph[i].clear();

            for(int i=0;i<e;i++)
            {
                int u,vv;
                cin >> u >> vv;

                graph[u].push_back(vv);
                graph[vv].push_back(u);
            }

            cout << "BFS: ";
            BFS(0,v);
            cout << endl;

            break;
        }

        case 14:
        {
            int v,e;

            cout << "Vertices: ";
            cin >> v;

            cout << "Edges: ";
            cin >> e;

            for(int i=0;i<20;i++)
                graph[i].clear();

            for(int i=0;i<e;i++)
            {
                int u,vv;
                cin >> u >> vv;

                graph[u].push_back(vv);
                graph[vv].push_back(u);
            }

            cout << "DFS: ";
            DFS(0,v);
            cout << endl;

            break;
        }

        case 15:
        {
            if(highestBid.empty())
            {
                cout << "No Bids Yet\n";
            }
            else
            {
                cout << "Winner: "
                     << highestBid.top().second
                     << " Bid = "
                     << highestBid.top().first
                     << endl;
            }

            break;
        }

        case 16:
            saveToFile();
            break;

        case 17:
        {
            int n;

            cout << "How Many Bid Values? ";
            cin >> n;

            vector<int> bids(n);

            for(int i=0;i<n;i++)
                cin >> bids[i];

            mergeSort(bids,0,n-1);

            cout << "Sorted Values: ";

            for(int x : bids)
                cout << x << " ";

            cout << endl;

            break;
        }
        }

    } while(choice != 0);

    return 0;
}