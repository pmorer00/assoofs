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



/*
 * Operaciones sobre el superbloque
 */
static const struct super_operations assoofs_sops = {
	.drop_inode = generic_delete_inode ,
};


/*
 * Inicialización del superbloque
 */
int assoofs_fill_super(struct super_block *sb, void *data, int silent){
	struct buffer_head *bh;
	struct assoofs_super_block_info *assoofs_sb_inf;
	struct inode *root_inode;
	int ret = 0;

	printk(KERN_INFO "[ASSOOFS] assoofs_fill_super request\n") ;

	// 1. - Leer la información persistente del superbloque del dispositivo de bloques
	bh = sb_bread(sb, ASSOOFS_SUPERBLOCK_BLOCK_NUMBER);
	assoofs_sb_inf = (struct assoofs_super_block_info *) bh->b_data;
	brelse(bh);

	// 2. - Comprobar los parámetros del superbloque
	if(assoofs_sb_inf->magic != ASSOOFS_MAGIC){
		ret = -1;
		printk(KERN_INFO "[ASSOOFS] Nº mágico del modulo incorrecto\n"); //Podría intentar mostrar los tamaños
	}
	if(assoofs_sb_inf->block_size != ASSOOFS_DEFAULT_BLOCK_SIZE){
		ret = -1;
		printk(KERN_INFO "[ASSOOFS] Tamaño de bloque del modulo incorrecto\n");  //Podría intentar mostrar los tamaños
	}

	// 3. - Escribir la información persistente leı́da del dispositivo de bloques en el superbloque sb , incluı́do el campo s_op con las operaciones que soporta
	sb->s_magic = ASSOOFS_MAGIC;
	sb->s_maxbytes = ASSOOFS_DEFAULT_BLOCK_SIZE;
	sb->s_ops = &assoofs_sops;
	sb->s_fs_info = assoofs_sb_inf;

	// 4. - Crear el inodo raı́z y asignarle operaciones sobre inodos (i_op) y sobre directorios (i_fop)
	root_inode = new_inode(sb);
	inode_init_owner(root_inode, NULL, S_IFDIR);
	root_inode->i_ino = ASSOOFS_ROOTDIR_INODE_NUMBER; //número de inodo
	root_inode->i_sb = sb; //puntero al superbloque
	root_inode->i_op = &assoofs_inode_ops; //dirección de una variable de tipo struct inode_operations previamente declarada
	root_inode->i_fop = &assoofs_file_operations; //dirección de una variable de tipo struct file_operations previamente declarada
	root_inode->i_atime = root_inode->i_mtime = root_inode->i_ctime = CURRENT_TIME ; //fechas.
	root_inode->i_private = assoofs_get_inode_info(sb, ASSOOFS_ROOTDIR_INODE_NUMBER); //Información persistente del inodo


	return ret;
}

/*
 * Montaje de dispositivos assoofs
 */
static struct dentry *assoofs_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data){
	struct dentry *ret = mount_bdev(fs_type, flags, dev_name, data, assoofs_fill_super());

	if(IS_ERR(ret))
		printk(KERN_INFO "[ASSOOFS] Exito al montar el registro assoofs\n");
	else
		printk(KERN_ERR "[ASSOOFS] Fallo al montar el registro assoofst\n");

	return ret;
}


/*
 * assoofs file system type
 */
static struct file_system_type assoofs_type = {
	.owner = THIS_MODULE ,
	.name = " assoofs " ,
	.mount = assoofs_mount ,
	.kill_sb = kill_litter_super ,
};


static int __init assoofs_init(void){
	int ret = register_filesystem(&assoofs_type);

	if(ret==0)
		printk(KERN_INFO "[ASSOOFS] Exito al registrar assoofs\n");
	else
		printk(KERN_ERR "[ASSOOFS] Fallo al registrar assoofs. Error [%d]", ret);

	return ret;
}


static void __exit assoofs_exit(void){
	int ret = unregister_filesystem(&assoofs_type);

	if(ret==0)
		printk(KERN_INFO "[ASSOOFS] Exito al sacar el registro assoofs\n");
	else
		printk(KERN_ERR "[ASSOOFS] Fallo al sacar el registro assoofs. Error [%d]", ret);
}


module_init(assoofs_init);
module_exit(assoofs_exit);
