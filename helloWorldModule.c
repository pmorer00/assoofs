#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO  */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/fs.h>           /* libfs stuff           */
#include <asm/uaccess.h>        /* copy_to_user          */
#include <linux/buffer_head.h>  /* buffer_head           */
#include <linux/slab.h>         /* kmem_cache            */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Angel Manuel Guerrero Higueras");

static int __init init_hello(void)
{
    printk(KERN_INFO "Hello world\n");
    return 0;
}

static void __exit cleanup_hello(void)
{
    printk(KERN_INFO "Goodbye world\n");
}

module_init(init_hello);
module_exit(cleanup_hello);