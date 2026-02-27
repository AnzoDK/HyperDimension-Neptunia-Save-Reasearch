#include <pthread.h>
#include <iostream>
#include <mutex>
#include <unistd.h>
#include <semaphore.h> /*Wow this is so useful*/
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

sem_t* g_semaphore = 0x0;
int main()
{
    g_semaphore = sem_open("/TestSemaphore", O_CREAT | O_EXCL, O_RDWR, 0);
    if(g_semaphore == SEM_FAILED)
    {
        if(errno == EEXIST)
        {
            std::cout << "Semaphore already exists!"<< std::endl;
            exit(1);
        }
         std::cout << "Semaphore failed to create... " << "error was: " << strerror(errno) << std::endl;
    }
    std::string x = "";
    std::cin >> x;
    std::cout << x;
    sem_close(g_semaphore);
    int unlinkRes = sem_unlink("/TestSemaphore");
    sem_destroy(g_semaphore);
}