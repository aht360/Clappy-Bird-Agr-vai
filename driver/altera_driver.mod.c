#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x6ffcc1a3, "module_layout" },
	{ 0xb3fe3e99, "pci_unregister_driver" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x926bdeb2, "__pci_register_driver" },
	{ 0xd224f665, "__register_chrdev" },
	{ 0x436c2179, "iowrite32" },
	{ 0x3af98f9e, "ioremap_nocache" },
	{ 0xef237555, "pci_bus_read_config_dword" },
	{ 0xecf47114, "pci_bus_read_config_byte" },
	{ 0xf9e546fe, "pci_enable_device" },
	{ 0xc3aaf0a9, "__put_user_1" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xe484e35f, "ioread32" },
	{ 0xedc03953, "iounmap" },
	{ 0x50eedeb8, "printk" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("pci:v00001172d00000004sv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "B36988EAFF1F5B730730893");
