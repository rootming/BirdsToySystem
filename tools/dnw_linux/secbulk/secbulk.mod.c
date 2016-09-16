#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
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
	{ 0x2ab9dba5, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x1559ef2f, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x457c11a1, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x55b9699c, __VMLINUX_SYMBOL_STR(mutex_trylock) },
	{ 0x9097c7cf, __VMLINUX_SYMBOL_STR(usb_find_interface) },
	{ 0x23beab60, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x96a6952c, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0x600ef125, __VMLINUX_SYMBOL_STR(usb_register_dev) },
	{ 0x20705009, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x8733c9e1, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb2903916, __VMLINUX_SYMBOL_STR(usb_bulk_msg) },
	{ 0xb5419b40, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0x1e12b70c, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x23a05c79, __VMLINUX_SYMBOL_STR(usb_deregister_dev) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbcore";

