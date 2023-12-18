#include<pthread.h>
#include<iostream>
#include<windows.h>

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int ready = 0;
boolean flag = true;
using namespace std;

void* producer(void*arg)
{
    for (int i = 0; i < 5; i++) //в таком цикле, потому что не хотелось прерывать выполнение бесконечного
    {
        pthread_mutex_lock(&lock);
        if (ready == 1)
        {
            pthread_mutex_unlock(&lock);
        }
        Sleep(1000);
        ready = 1;
        cout << "provided" << endl;
        pthread_cond_signal(&cond1); //условная переменная
        pthread_mutex_unlock(&lock);
    }
    flag = false;
        return nullptr;
}

void* consumer(void*arg) 
{
    while (flag)
    {
        pthread_mutex_lock(&lock);
        while (ready == 0)
        {
            if (!flag) break;
            pthread_cond_wait(&cond1, &lock); 

        }
        ready = 0;
        cout << "consumed" << endl;
        pthread_mutex_unlock(&lock);
    }
        return nullptr;
}

int main() {
    pthread_t pt, ct;

    pthread_create(&pt, nullptr, producer, nullptr);
    pthread_create(&ct, nullptr, consumer, nullptr);

    pthread_join(pt, nullptr);
    pthread_join(ct, nullptr);

    return 0;
}
