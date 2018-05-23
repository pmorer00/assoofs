# assoofs
Practica final ASSOO, sistema de ficheros assoofs

Fecha de entrega estimada: 11/Junio/2018



Correos{
  -From: ÁNGEL MANUEL GUERRERO, 18/Mayo/2018 - 17:15:
        Para todos los que os aparezca el siguiente error en vuestros equipos:
        ./arch/x86/include/asm/uaccess.h: In function ‘set_fs’:
        ./arch/x86/include/asm/uaccess.h:31:9: error: dereferencing pointer to incomplete type ‘struct task_struct’
          current->thread.addr_limit = fs;
        Si leéis el mensaje de error (sana costumbre, os lo recomiendo) el problema está en la librería uaccess.h. Para poder seguir trabajando, comentad la siguiente línea:
        #include <linux/uaccess.h>

        Por ahora no necesitaremos esa librería.

        Os adelanto que surgirán nuevos problemas del estilo, y que en la medida de lo posible os ayudaremos a resolverlos. Pero es imposible hacer frente a todas las configuraciones: distintas arquitecturas, distintas versiones de SO, distintos virtualizadores, etc.

        De modo, que para evitar malos entendidos os diré la configuración exacta bajo la se corregirán las prácticas y que se corresponderá con la configuración de los equipos del lab. Para que no tengáis que venir al lab, os proporcionaré una máquina virtual con las mismas condiciones. No quiere decir que siempre tengáis que trabajar ahí, pero si al menos probar vuestra práctica antes de entregarla.

        Salu2
        
        
  -From: ÁNGEL MANUEL GUERRERO, 22/Mayo/2018 - 10:43:
        Hola a todos,

        acabo de subir una versión modificada del guión de la práctica final. Habrá más cambios, estad atentos y pendientes, casi todo lo que necesitáis está en el guión. Además os recuerdo la importancia de mirar las referencias. En una de ellas hay incluso un sistema de ficheros completo y funcional.

        Además de desarrollar la práctica, os vamos a pedir que creéis un repositorio privado en github y que me invitéis a participar (mi id en github es am-guerrero). En clase os explicaremos el motivo. Sólo por hacerlo, y por utilizarlo (no me vale que lo hagáis al final), os premiaremos con un punto en la práctica final.

        Con respecto a los criterios de evaluación de la práctica se aplicarán los siguientes:

            80% de la nota corresponderá con las funcionalidades básicas.
            10% con la implementación de alguna de las partes opcionales.
            10% con el uso del repositorio .

        La definición de las funcionalidades básicas y las opciones, están detalladas en el guión. Cualquier duda al respecto, lo vemos en clase.
        
  -From: ÁNGEL MANUEL GUERRERO, 22/Mayo/2018 - 19:14 :
        En algunas versiones del kernel aparece este error:

        error: ‘CURRENT_TIME’ undeclared (first use in this function)
             inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;
                                                                ^

        Ocurre por que la macro CURRENT_TIME ha sido eliminada en versiones recientes. Para que desaparezca el error hay que sustituir las llamadas a la macro CURRENT_TIME:

        inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;

        Por llamadas ala función current_time(). La llamada tiene un argumento que se corresponde con el inodo al que quiera asignarle marca de tiempo:

        inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);

        Salu2.
}
