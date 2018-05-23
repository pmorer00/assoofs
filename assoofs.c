/*
 * Descripcion del guión: Implementación de un módulo para que el kernel del SO pueda interactuar con un dispositivo de bloques con formato ASSOOFS
 * Aclaración propia: gracias a este archivo el kernel del SO será capaz de manejar el sistema de archivos construido en "mkassoofs.c" (assoofs)
 */

#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO  */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/fs.h>           /* libfs stuff           */
//#include <asm/uaccess.h>        /* copy_to_user          */
#include <linux/buffer_head.h>  /* buffer_head           */
#include <linux/slab.h>         /* kmem_cache            */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Moreno Roldan");

static int __init assoofs_init(void){
	int retRegFS;

	retRegiFS = register_filesystem(&assoofs_type);
	if(retRegiFS==0)
		printk(KERN_INFO "Successfully registered assoofs\n");
	else
		printk(KERN_ERR "Failed to register assoofs. Error %d.", retRegiFS);

	return retRegiFS;
}

static int __exit assoofs_exit(void){
	int retRegFS;
	retRegiFS = unregister_filesystem(&assoofs_type);

	if(retRegiFS==0)
		printk(KERN_INFO "Successfully unregistered assoofs\n");
	else
		printk(KERN_ERR "Failed to unregister assoofs. Error [%d]", retRegiFS);

	return retRegiFS;
}

module_init(assoofs_init);
module_exit(assoofs_exit);
