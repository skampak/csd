#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <asm/current.h>
#include <linux/types.h>
#include <linux/pid.h>
#include <linux/t_params.h>
#include <linux/pid_namespace.h>

asmlinkage long sys_get_remaining_time(int pid, struct t_params *t_arguments)
{
        struct pid *pid_struct2;
	struct task_struct *test2;
	int rm;
	unsigned int inf;

        if(pid==-1)
        {
                rm=current->remaining_time;
                inf=current->infinite;
        }else
	{
		pid_struct2=find_get_pid(pid);
		test2 = pid_task(pid_struct2,PIDTYPE_PID);
		rm=test2->remaining_time;
		inf=test2->infinite;
	}
	t_arguments->remaining_time=rm;
	t_arguments->infinite=inf;
        printk("Sofia Kampaki csd3221 get_total_time");
	return(0);
}
