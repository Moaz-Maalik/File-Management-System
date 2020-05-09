#include <iostream>
#include <list>
#include<stdlib.h>
#include<fstream>
using namespace std;
class pioritynode
{
public:
    int key;
    int userid;
    char operationtype;
    pioritynode()   //constructor
    {
        key=-1;
        userid=-1;
    }
    friend istream& operator >>(istream&cin, pioritynode&node)   //overloads
	{
	    cout<<endl<<"Enter the Piority : ";
		cin >> node.key;
		cout<<endl<<"Enter the UserID : ";
		cin >> node.userid;
		cout<<endl<<"Enter the OperationType : ";
		cin>>node.operationtype;
		return cin;
	}

	friend ostream& operator <<(ostream&cout, pioritynode node)
	{
	    cout<<endl<<"Piority : ";
		cout<< node.key;
		cout<<endl<<"UserID : ";
        cout<< node.userid;
        cout<<endl<<"OperationType : ";
		cout<<node.operationtype;
		return cout;
	}
	pioritynode(const pioritynode& node)
	{
		key=node.key;
		userid=node.userid;
		operationtype=node.operationtype;
	}
	pioritynode& operator=(pioritynode node)
	{
		key = node.key;
		userid=node.userid;
		operationtype=node.operationtype;
		return *this;
	}
	bool operator>(pioritynode& node)
	{
		if(key>node.key)
        {
            return true;
        }
        return false;
	}
	bool operator<(pioritynode& node)
	{
		if(key<node.key)
        {
            return true;
        }
        return false;
	}

};
template<class T>
class priorityQueue
{
 public:
    T *que;
    int currentsize;
    int maxsize;
    T mini;
    priorityQueue()  //contructors
    {
        que=NULL;
        currentsize=0;
        maxsize=0;
    }
    priorityQueue(int maxsizee)
    {
        maxsize=maxsizee;
        currentsize=0;
        que=new T[maxsizee];
    }
    int leftchildindex(int index)
    {
        return (2 * index +1);
    }
    int rightchildindex(int index)
    {
        return (2 * index +2);
    }
    bool Last(int index)
    {
        if(index>=currentsize)
            {
                return true;
            }
        return false;
    }
    int parentindex(int index)
    {
        if(index % 2 == 0)
        {
            return (index /2) -1;
        }
        else
        {
            return (index/2);
        }


    }
    void reheapup(int i)
    {
        if(i == 0)
            return;

        int parent= parentindex(i);

        if(que[parent] < que[i])
        {

            swap(que[i],que[parent]);
            reheapup(parent);
        }
    }
    void reheapdown(int i)
    {
        int left = leftchildindex(i);
        int right = rightchildindex(i);

        if(Last(left))
            return;

        int largest = i;
        if(que[left] > que[i])
        {
            largest = left;
        }

        if(!Last(right) && (que[right] > que[largest]))
        {
            largest = right;
        }

        if(largest != i)
        {
            swap(que[i],que[largest]);
            reheapdown(largest);
        }
    }
    void BuildQueue(T* arr,int length)
    {
         for(int i=0;i<length;i++)
         {
             Insert(arr[i],length);
         }
    }
    T ExtractMax()
    {
        T maximum = que[0];
        que[0] = que[currentsize - 1];
        que[currentsize - 1].userid=-1;
        que[currentsize - 1].key=-1;
        que[currentsize - 1].operationtype='n';
        currentsize--;
        reheapdown(0);
        return maximum;
    }
    T FindMax()
    {
        if(que!=NULL)
            return que[0];
        cout<<endl<<"Que is empty"<<endl;
    }
    T FindMin()
    {
        return mini;
    }
    void Insert(T piority,int size)
    {
        if(que==NULL)
        {
            mini=piority;   //updating the minimum piority
            que=new T[size];
            maxsize=size;
            que[currentsize] = piority;
            reheapup(currentsize);
            currentsize++;
        }
        else
        {
            if(mini>piority)
            {
                mini=piority;    //updating the minimum piority
            }
            que[currentsize] = piority;
            reheapup(currentsize);
            currentsize++;
        }

    }
    int size()
    {
        return currentsize;
    }
    bool empty()
    {
        if(currentsize==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
class hashnode
{
public:
    int fileid;
    priorityQueue<pioritynode> *waitinglist;
    pioritynode *currentuser;
    int sizeofcurrentuser;
    hashnode()     //contructor
    {
        waitinglist=NULL;
        fileid=-1;
        currentuser=NULL;
        sizeofcurrentuser=0;

    }

};
template<class T>
class hashtable
{
public:
    list<T> table[500];
    hashtable()  //contructor
    {

    }
    int hashing(T obj)     //hasing with 500 table size
    {
        int returnvalue=obj.fileid%500;
        return returnvalue;
    }
    void insert(T obj)   //inserting
    {
        int position=hashing(obj);
        table[position].push_back(obj);
    }
    void printhashtable()  //this fuction contains all the checks to print
    {
        for(int i=0;i<500;i++)
        {
            if(!table[i].empty())
            {
                cout<<endl<<"H"<<i<<":"<<endl;
                list<hashnode>::iterator p = table[i].begin();
                while(p != table[i].end())
                    {
                        cout<<endl<<"    File "<<p->fileid<<" Access granted to";
                        if(p->currentuser==NULL)
                        {
                            cout<<" none";
                            cout<<endl<<"    Next none";
                            cout<<endl<<"    Waiting none";
                        }
                        else
                        {
                            for(int i=0;i<p->sizeofcurrentuser;i++)
                            {
                                cout<<" User "<<p->currentuser[i].userid<<",";
                            }
                            if(p->currentuser[0].operationtype=='r')
                            {
                                cout<<"Read";
                            }
                            if(p->currentuser[0].operationtype=='w')
                            {
                                cout<<"Write";
                            }
                            if(p->sizeofcurrentuser>=1)
                            {
                                pioritynode obj;
                                if(p->waitinglist==NULL)
                                {
                                    cout<<endl<<"    Next none";
                                    cout<<endl<<"    Waiting none";
                                }
                                else
                                {
                                    obj=p->waitinglist->FindMax();
                                    cout<<endl<<"    Next User "<<obj.userid<<",";
                                    if(obj.operationtype=='r')
                                    {
                                        cout<<"Read";
                                    }
                                    if(obj.operationtype=='w')
                                    {
                                        cout<<"Write";
                                    }
                                    cout<<endl<<"    Waiting "<<p->waitinglist->size()<<" users";
                                }


                            }
                            else
                            {
                                cout<<endl<<"    Next none";
                                cout<<endl<<"    Waiting none";
                            }

                        }
                        cout<<endl;
                        p++;
                    }
                    cout<<endl;
            }

        }

    }
    void RequestFileAccess(int fileId,int userId,char operationType,int piority)  //this fuction with grant access if file is present
    {
        int found=0;
        int position=fileId%500;
        list<hashnode>::iterator p = table[position].begin();
         while(p != table[position].end())
            {
                if(p->fileid==fileId)
                {
                    found=1;
                }
                p++;
            }
        if(found==0)
        {
            cout<<endl<<"File NOT FOUND"<<endl;
            return;
        }
        p = table[position].begin();
         while(p != table[position].end())
            {
                if(p->fileid==fileId)
                {
                    if(p->currentuser==NULL)
                    {
                        p->currentuser=new pioritynode[p->sizeofcurrentuser+1]; //ewgwgwrhwr
                        p->currentuser[p->sizeofcurrentuser].userid=userId;
                        p->currentuser[p->sizeofcurrentuser].key=piority;
                        p->currentuser[p->sizeofcurrentuser].operationtype=operationType;
                        p->sizeofcurrentuser++;
                        cout<<endl<<"The File : "<<fileId<<" is being used by the User : "<<userId<<endl;
                        return;
                    }

                    if(operationType== p->currentuser[0].operationtype && operationType!='w')
                    {
                        p->sizeofcurrentuser++;
                        pioritynode *temparr=new pioritynode[p->sizeofcurrentuser];
                        for(int i=0;i<p->sizeofcurrentuser-1;i++)
                        {
                            temparr[i]=p->currentuser[i];
                        }
                        temparr[p->sizeofcurrentuser-1].key=piority;
                        temparr[p->sizeofcurrentuser-1].operationtype=operationType;
                        temparr[p->sizeofcurrentuser-1].userid=userId;
                        delete[] p->currentuser;
                        p->currentuser=NULL;
                        p->currentuser=temparr;
                        for(int i=0;i<p->sizeofcurrentuser;i++)
                        {
                            cout<<endl<<i+1<<")The File : "<<fileId<<" is being used by the User : "<< p->currentuser[i].userid<<endl;
                        }

                        return;

                    }
                    pioritynode tobeinserted;
                    tobeinserted.userid=userId;
                    tobeinserted.key=piority;
                    tobeinserted.operationtype=operationType;
                    if(p->waitinglist==NULL)
                    {
                        p->waitinglist=new priorityQueue<pioritynode>;
                    }
                    p->waitinglist->Insert(tobeinserted,100);
                    cout<<endl<<"The User : "<<userId<<" has been added in the waiting list of File : "<<fileId<<endl;

                }
                p++;
            }

    }
    void ReleaseFile(int fileId,int userId)  // if file and user both are there then it will release the file
    {
        int found=0;
        int flag2=0;
        int position=fileId%500;
        list<hashnode>::iterator p = table[position].begin();
         while(p != table[position].end())
            {
                if(p->fileid==fileId)
                {
                    found=1;
                }
                p++;
            }
        if(found==0)
        {
            cout<<endl<<"File NOT FOUND"<<endl;
            return;
        }
        p = table[position].begin();
         while(p != table[position].end())
            {
                if(p->fileid==fileId)
                {
                    if(p->currentuser==NULL)
                    {
                        cout<<endl<<"No User has access to this File right now!!"<<endl;
                        return;
                    }
                    for(int i=0;i<p->sizeofcurrentuser;i++)
                    {
                        if(p->currentuser[i].userid==userId)
                        {
                            flag2=1;
                        }
                    }

                }
                p++;
            }
            if(flag2==0)
            {
                cout<<endl<<"User NOT FOUND"<<endl;
                return;
            }
        p = table[position].begin();
         while(p != table[position].end())
            {
                if(p->fileid==fileId)
                {
                    for(int i=0;i<p->sizeofcurrentuser;i++)
                    {
                        if(p->currentuser[i].userid==userId)
                        {
                            swap(p->currentuser[i],p->currentuser[p->sizeofcurrentuser-1]);
                            p->sizeofcurrentuser--;
                            if( p->sizeofcurrentuser==0)
                            {
                                p->currentuser=NULL;
                            }
                            else
                            {
                                pioritynode *temparr=new pioritynode[p->sizeofcurrentuser];
                                for(int i=0;i<p->sizeofcurrentuser;i++)
                                {
                                    temparr[i]=p->currentuser[i];
                                }
                                delete[]p->currentuser;
                                p->currentuser=NULL;
                                p->currentuser=temparr;
                            }
                            if(p->waitinglist->FindMax().operationtype=='w' && p->currentuser==NULL)
                            {
                                 pioritynode obj;
                                obj=p->waitinglist->ExtractMax();
                                int filenum=fileId;
                                int usernumber=obj.userid;
                                int piority=obj.key;
                                char operation=obj.operationtype;
                                this->RequestFileAccess(filenum,usernumber,operation,piority);
                                for(int i=0;i<p->sizeofcurrentuser;i++)
                                {
                                    cout<<endl<<i+1<<")The File : "<<fileId<<" is being used by the User : "<< p->currentuser[i].userid<<endl;
                                }
                                return;

                            }
                            while(p->waitinglist->FindMax().operationtype=='r')
                            {
                                pioritynode obj;
                                obj=p->waitinglist->ExtractMax();
                                int filenum=fileId;
                                int usernumber=obj.userid;
                                int piority=obj.key;
                                char operation=obj.operationtype;
                                this->RequestFileAccess(filenum,usernumber,operation,piority);
                            }
                            for(int i=0;i<p->sizeofcurrentuser;i++)
                                {
                                    cout<<endl<<i+1<<")The File : "<<fileId<<" is being used by the User : "<< p->currentuser[i].userid<<endl;
                                }
                            return;

                        }
                    }

                }
                p++;
            }



    }
    void deleteFile(int fileId)  //if file is present then it will delete the file
    {
        int found=0;
        int position=fileId%500;
        list<hashnode>::iterator p = table[position].begin();
         while(p != table[position].end())
            {
                if(p->fileid==fileId)
                {
                    found=1;
                }
                p++;
            }
        if(found==0)
        {
            cout<<endl<<"File NOT FOUND"<<endl;
            return;
        }
        p = table[position].begin();
         while(p != table[position].end())
            {
                if(p->fileid==fileId)
                {
                    if(p->currentuser==NULL)
                    {
                        table[position].erase(p);
                        return;
                    }
                    else
                    {
                        cout<<endl<<"The File cant be removed because its being used";
                        return;
                    }
                }
                p++;
            }

    }
    void loadfromFile()  //first count the lines then insert then if file is present
    {
        ifstream fin;
        fin.open("data.txt");
        int i=0;
        if (fin.is_open())
        {
            char a[100];
            while(!fin.eof())
            {
                fin.getline(a,100);
                i++;
            }
            fin.close();

        }
        else
        {
            cout << endl << "Failed to open File" << endl;
        }
        int j=0;
        fin.open("data.txt");
        if (fin.is_open())
        {
            while(j<i)
            {
                int filenum;
                fin>>filenum;
                //cout<<filenum;

                char comma;
                fin>>comma;

                int usernum;
                fin>>usernum;
                //cout<<usernum;

                fin>>comma;

                int piority;
                fin>>piority;
                //cout<<piority;

                fin>>comma;

                char operation;
                fin>>operation;
                //cout<<operation;
                this->RequestFileAccess(filenum,usernum,operation,piority);
                if(j==i-1)
                {
                    break;
                }
                j++;
            }

        }
        else
        {
            cout << endl << "Failed to open File" << endl;
        }

    }
};
int main()
{
    hashtable<hashnode> h;
    int choice;

    while(1)
    {
        cout<<endl<<"1)Print Hash Table";
        cout<<endl<<"2)Load Data from File";
        cout<<endl<<"3)Insert a File";
        cout<<endl<<"4)Delete a File";
        cout<<endl<<"5)Request an Access to a File";
        cout<<endl<<"6)Release The File"<<endl;
        cin>>choice;
        system("CLS");
        switch (choice)
        {
            case 1:
                {
                    h.printhashtable();
                    system("PAUSE");
                    break;

                }
            case 2:
                {
                    h.loadfromFile();
                    system("PAUSE");
                    break;

                }

            case 3:
                {
                    hashnode obj;
                    cout<<endl<<"Enter The File ID you want to insert : ";
                    cin>>obj.fileid;
                    h.insert(obj);
                    system("PAUSE");
                    break;

                }
            case 4:
                 {
                    int obj;
                    cout<<endl<<"Enter The File ID you want to Delete : ";
                    cin>>obj;
                    h.deleteFile(obj);
                    system("PAUSE");
                    break;

                }
            case 5:
                 {
                    int filenum;
                    cout<<endl<<"Enter The File ID you want to Access : ";
                    cin>>filenum;

                    int usernum;
                    cout<<endl<<"Enter The User ID who wants to  Access the File : ";
                    cin>>usernum;

                    char operation;
                    cout<<endl<<"Enter the Access type (r or w) : ";
                    cin>>operation;

                    int piori;
                    int choi;
                    cout<<endl<<"Enter the Piority"<<endl;
                    cout<<"Do you want to enter a number or enter Low or High (L and H)";
                    cout<<endl<<"1)Number   2)L and H";
                    cin>>choi;
                    if(choi==1)
                    {
                        cout<<endl<<"Enter the Number : ";
                        cin>>piori;
                    }
                    if(choi==2)
                    {
                        char c;
                        cout<<endl<<"Enter Low or High (l and h) : ";
                        cin>>c;
                        if(c=='h')
                        {
                            int position=filenum%500;
                            list<hashnode>::iterator p = h.table[position].begin();
                            while(p != h.table[position].end())
                                {
                                    if(p->fileid==filenum)
                                    {
                                       if(p->waitinglist!=NULL)
                                       {
                                           piori=p->waitinglist->FindMax().key;
                                       }
                                       else
                                       {
                                           piori=100;
                                       }
                                    }
                                    p++;
                                }
                        }
                        if(c=='l')
                        {
                            int position=filenum%500;
                            list<hashnode>::iterator p = h.table[position].begin();
                            while(p != h.table[position].end())
                                {
                                    if(p->fileid==filenum)
                                    {
                                       if(p->waitinglist!=NULL)
                                       {
                                           piori=p->waitinglist->FindMin().key;
                                       }
                                       else
                                       {
                                           piori=100;
                                       }
                                    }
                                    p++;
                                }
                        }
                    }

                    h.RequestFileAccess(filenum,usernum,operation,piori);

                    system("PAUSE");
                    break;

                }
            case 6:
                 {
                    int filenum;
                    cout<<endl<<"Enter The File ID you want to Release : ";
                    cin>>filenum;

                    int usernum;
                    cout<<endl<<"Enter The User ID who wants to Release the File : ";
                    cin>>usernum;

                    h.ReleaseFile(filenum,usernum);

                    system("PAUSE");
                    break;

                }
            default:

                break;
        }
        system("CLS");
    }












    return 0;
}
