
// In Unix-like operating systems such as Linux, the `fork()` system call is used to create a new process, which is called a child process. The `fork()` system call creates a new process by duplicating the existing process.
// After the `fork()` call, both the parent and the child processes continue execution from the next instruction following the `fork()` call. The `fork()` system call is specific to Unix-like operating systems and may not work on Windows. 
// The `fork()` system call is a basic building block for creating new processes in Unix-like operating systems, and it is used extensively in process management and multitasking.


#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Error: Fork failed" << std::endl;
        return 1;
    } else if (pid == 0) {
        std::cout << "Child process: My PID is " << getpid() << std::endl;
        std::cout << "Child process: My parent's PID is " << getppid() << std::endl;

        // Perform child-specific operations here

        return 0;
    } else {
        std::cout << "Parent process: I have a child with PID " << pid << std::endl;
        std::cout << "Parent process: My PID is " << getpid() << std::endl;

        // Perform parent-specific operations here

        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}
