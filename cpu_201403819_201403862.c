#include <linux/module.h> 
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h> 
#include <linux/hugetlb.h>
#include <linux/sched/signal.h>
 

#define modulo_cpu "cpu_201403819_201403862"
#define Carnets "201403819 - 201403862"
#define Nombres "Yoselin Lemus - Brandon Alvarez"
#define Curso "Sistemas Operativos 1"

struct task_struct *task;
struct task_struct *task_child;
struct list_head *list;


static int proc_llenar_archivo(struct seq_file *m, void *v) {
    seq_printf(m, "Carnets: %s\n", Carnets);
    seq_printf(m, "Nombres: %s\n", Nombres);
    for_each_process(task)
    {
        seq_printf(m, "PID : %d, Nombre : %s, Estado : %ld\n", task->pid, task->comm, task->state);
        list_for_each(list, &task->children)
        {
            task_child = list_entry(list, struct task_struct, sibling);
            seq_printf(m, "PID : %d, Nombre : %s, Estado : %ld\n", task_child ->pid, task_child->comm, task_child->state);
        }
    }
    return 0;
}

static int proc_al_abrir_archivo(struct inode *inode, struct  file *file) {
  return single_open(file, proc_llenar_archivo, NULL);
}

static struct proc_ops operacionesDeArchivo={
    .proc_open = proc_al_abrir_archivo,
    .proc_release = single_release,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
};

static int iniciar(void)
{
    proc_create(modulo_cpu,0,NULL,&operacionesDeArchivo);
    printk(KERN_INFO "Nombres: %s\n", Nombres);
    return 0;
}

static void terminar(void)
{
    remove_proc_entry(modulo_cpu,NULL);
    printk(KERN_INFO "Curso: %s\n", Curso);
}

module_init(iniciar);
module_exit(terminar);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yoselin Lemus - Brandon Alvarez");
MODULE_DESCRIPTION("Modulo con informacion de la memoria CPU");

