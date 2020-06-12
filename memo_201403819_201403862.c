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

#define modulo_memoria "memo_20143819_201403862"
#define Carnets "201403819 - 201403862"
#define Nombres "Yoselin Lemus - Brandon Alvarez"
#define Curso "Sistemas Operativos 1"

struct sysinfo i;

static int proc_llenar_archivo(struct seq_file *m, void *v) {
  #define S(x) ((x) << (PAGE_SHIFT -10))
  si_meminfo(&i);
    seq_printf(m, "Carnets: %s\n", Carnets);
    seq_printf(m, "Nombres: %s\n", Nombres);
    seq_printf(m, "Memoria total: %8lu MB\n",S(i.totalram/1024));
    seq_printf(m, "Memoria libre: %8lu MB\n",S(i.freeram/1024));
    seq_printf(m, "Memoria utilizada: %8lu %%\n",S((i.freeram)*100)/S(i.totalram));        
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
  proc_create(modulo_memoria,0,NULL,&operacionesDeArchivo);
    printk(KERN_INFO "Carnets: %s\n", Carnets);
    return 0;
}


static void terminar(void)
{
  remove_proc_entry(modulo_memoria,NULL);
  printk(KERN_INFO "Curso: %s\n", Curso);
}


module_init(iniciar);
module_exit(terminar);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yoselin Lemus - Brandon Alvarez");
MODULE_DESCRIPTION("Modulo con informacion de la memoria CPU");
