#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_ALERT */
#include <linux/init.h>  /* Needed for the macros */

static int __init hello_init(void)
{
 printk(KERN_EMERG "Hello, world\n");
  return 0;
  }
static void __exit hello_exit(void)
{
   printk(KERN_EMERG "Goodbye, world\n");
   }
   
   module_init(hello_init);
   module_exit(hello_exit);
