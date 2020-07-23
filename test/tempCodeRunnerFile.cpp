oreTest(void *ptr)
// {
//     int flag = *(int *)ptr;
 
//     HANDLE semaphore = CreateSemaphore(NULL, 2, 2, (LPCWSTR)"streamSemaphore");
 
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