#include <iostream>
#include <fstream>
#include <windows.h>
#include <process.h>
 
using namespace  std;
 
// void semaphoreTest(void *ptr)
// {
//     int flag = *(int *)ptr;
 
//     HANDLE semaphore = CreateSemaphore(NULL, 2, 2, "streamSemaphore");
 
//     WaitForSingleObject(semaphore, INFINITE);
 
//     ofstream fileStream("c:/test.txt", ios_base::app);
 
//     for (int i = 0; i < 5; ++i)
//     {
//         Sleep(1000);
//         fileStream<<flag;
//         fileStream<<' '<<flush;
 
//         //cout<<flag<<' ';
//     }
 
//     fileStream.close();
 
//     ReleaseSemaphore(semaphore, 1, NULL);
//     CloseHandle(semaphore);
// }
 
 
int main()
{
    // std::cout<<"szm"<<std::endl;
    // int flag[] = {1, 2, 3};
 
    // for (int i = 0; i < 3; ++i)
    // {
    //     _beginthread(semaphoreTest, 0, &flag[i]);
    // }
    
    // Sleep(INFINITE);

    int count = 10;
    while (true)
    {
        if(--count > 0)
        {
            cout<<count<<endl;
        }       
        else
        {
            break;
        }
         
    }
    

        
}