#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <asm/current.h>
#include <linux/types.h>
#include <linux/pid.h>

#include <linux/pid_namespace.h>

asmlinkage long sys_set_total_computation_time(int pid,unsigned int total_time)
{

	struct pid *pid_struct;
	
	struct task_struct *test;
	if(pid==-1)
	{
		current->total_computation_time=total_time;
		current->remaining_time=total_time;
		current->infinite=0;
		printk("the total time of the process is %d\n",current->total_computation_time);
	}else{
             pid_struct=find_get_pid(pid);
	     test = pid_task(pid_struct,PIDTYPE_PID);
             test->total_computation_time=total_time;
	}
	
	printk("Sofia Kampaki! 3221 set_total_computation_time");
	return((long)0);
}
