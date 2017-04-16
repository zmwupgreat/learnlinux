#include<linux/list.h>
#include<linux/init.h>
#include<linux/module.h>
struct list_head head=LIST_HEAD_INIT(head);
struct list_head *post;
struct num
{
	int num;
	char name;
	struct list_head node;
};
struct num *tmp;
void PRINT_list(void)
{
	list_for_each(post,&head)
	{
	tmp=list_entry(post,struct num,node);
	printk(KERN_EMERG "NUM:%d  NAME:%c\n\n",tmp->num,tmp->name);
	}
	printk(KERN_EMERG"----------------\n\n\n");
}
static int __init listtest_init(void)
{
	printk(KERN_EMERG "list on!");
	struct num num1;
	struct num num2;
	struct num num3;
	struct num num4;
	struct num num5;
	num1.num=1;
	num1.name='a';
	num2.num=2;
	num2.name='b';
	num3.num=3;
	num3.name='c';
	num4.num=4;
	num4.name='d';
	num5.num=5;
	num5.name='e';
	list_add(&(num1.node),&head);
	list_add(&(num2.node),&head);
	list_add(&(num3.node),&head);
	list_add(&(num4.node),&head);
	PRINT_list();
	list_replace(&(num2.node),&(num5.node));
	PRINT_list();
	list_add(&(num2.node),&head);
	PRINT_list();
	list_del(&(num5.node));
	PRINT_list();
}
static void __exit listtest_exit(void)
{
	printk(KERN_EMERG,"GOODBYE!\n");
}
module_init(listtest_init);
module_exit(listtest_exit);

