/***
 * @Author: MaoziSakura
 * @Date: 2026-04-30
 * @FilePath: /AbstractLinkedList/tests/fork_process.cpp
 * @LastEditTime: 2026-04-30
 * @Description:
 ***/

#include "custom_test.hpp"
#include <iostream>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

union semun
{
    int val;
    struct semid_ds* buf;
    unsigned short* array;
    // semun() = default;
    // semun(int val) : val(val) {}
    // semun(struct semid_ds* buf) : buf(buf) {}
    // semun(unsigned short* array) : array(array) {}
};

void custom_semop(int sem_id, short op_val);

int fork_test()
{
    // 创建进程信号量, 信号量元素为1
    int sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0666);
    std::cout << "sem_id " << sem_id << std::endl;
    // 初始化进程信号量
    semun sem_flg;
    sem_flg.val = 1;
    if (semctl(sem_id, 0, SETVAL, sem_flg) == -1)
    {
        perror("semctl error");
        std::cout << "semctl init error \n";
        exit(-1);
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        std::cout << "子进程进入睡眠" << std::endl;
        sleep(10);
        std::cout << "子进程结束睡眠" << std::endl;
        std::cout << "子进程运行中" << std::endl;
        custom_semop(sem_id, short(-1));
        std::cout << "子进程申请成功, 继续执行" << std::endl;
        exit(0);
    }
    else
    {
        std::cout << "父进程申请信号量" << std::endl;
        custom_semop(sem_id, short(-1));
        std::cout << "父进程申请成功, 继续执行" << std::endl;
        sleep(15);
        std::cout << "父进程释放信号量" << std::endl;
        custom_semop(sem_id, short(1));
        std::cout << "父进程释放成功, 继续执行" << std::endl;
        int stat;
        std::cout << "等待子进程" << std::endl;
        wait(&stat);
        std::cout << "子进程执行完成, 子进程状态值" << stat << std::endl;
    }

    return 0;
}

void custom_semop(int sem_id, short op_val)
{
    sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = op_val;
    sem_buf.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_buf, size_t(1)) == -1)
    {
        std::cout << "semop 申请异常" << std::endl;
        exit(-1);
    }
}