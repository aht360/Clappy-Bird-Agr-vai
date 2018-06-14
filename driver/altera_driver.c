#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Basic Driver PCIHello");
MODULE_AUTHOR("Patrick Schaumont");

//-- Hardware Handles

static void *hexport;  // handle to 32-bit output PIO
static void *butt;  // handle to 32-bit input PIO
static void *sw;   // handle to 16-bit input PIO
static void *redLed;  // handle to 32-bit output PIO
static void *greenLed;  // handle to 32-bit output PIO
static void *hexport2;  // handle to 32-bit output PIO

//-- Char Driver Interface
static int   access_count =  0;
static int   MAJOR_NUMBER = 91;

static int     char_device_open    ( struct inode * , struct file *);
static int     char_device_release ( struct inode * , struct file *);
static ssize_t char_device_read    ( struct file * , char *,       size_t , loff_t *);
static ssize_t char_device_write   ( struct file * , const char *, size_t , loff_t *);

static struct file_operations file_opts = {
      .read = char_device_read,
      .open = char_device_open,
     .write = char_device_write,
   .release = char_device_release
};

static int char_device_open(struct inode *inodep, struct file *filep) {
   access_count++;
   printk(KERN_ALERT "altera_driver: opened %d time(s)\n", access_count);
   return 0;
}

static int char_device_release(struct inode *inodep, struct file *filep) {
   printk(KERN_ALERT "altera_driver: device closed.\n");
   return 0;
}

static ssize_t char_device_read(struct file *filep, char *buf, size_t len, loff_t *off) {
  short push_buttons;
  size_t count = len;
  long switches;
  //  printk(KERN_ALERT "altera_driver: read %d bytes\n", len);
  if(len == 0){   //butao
    push_buttons = ioread32(butt);
    put_user(push_buttons, buf++);
  }else if(len == 1){
    switches = ioread32(sw);
    put_user((switches) & 0xFF, buf++);
    put_user((switches >> 8) & 0xFF, buf++);
    put_user((switches >> 16) & 0xFF, buf++);
  }

  return count;
}

static ssize_t char_device_write(struct file *filep, const char *buf, size_t type, loff_t *off) {
  char *ptr = (char *) buf;
  //  printk(KERN_ALERT "altera_driver: write %d bytes\n", len);

  if(type == 0) { //7 segmentos 
    unsigned k = *((int *) ptr);
    iowrite32(k, hexport);
  } else if(type == 1) { //led verde 
    unsigned k = *((int *) ptr);
    iowrite32(k, greenLed);
    
  } else if(type == 2) { //led vermelho 
    unsigned k = *((int *) ptr);
    iowrite32(k, redLed);
  } else if(type == 3) { //7 segmentos 2-2
    unsigned k = *((int *) ptr);
    iowrite32(k, hexport2);
  }

  
  return 4;
}

//-- PCI Device Interface

static struct pci_device_id pci_ids[] = {
  { PCI_DEVICE(0x1172, 0x0004), },
  { 0, }
};
MODULE_DEVICE_TABLE(pci, pci_ids);

static int pci_probe(struct pci_dev *dev, const struct pci_device_id *id);
static void pci_remove(struct pci_dev *dev);

static struct pci_driver pci_driver = {
  .name     = "alterahello",
  .id_table = pci_ids,
  .probe    = pci_probe,
  .remove   = pci_remove,
};

static unsigned char pci_get_revision(struct pci_dev *dev) {
  u8 revision;

  pci_read_config_byte(dev, PCI_REVISION_ID, &revision);
  return revision;
}

static int pci_probe(struct pci_dev *dev, const struct pci_device_id *id) {
  int vendor;
  int retval;
  unsigned long resource;

  retval = pci_enable_device(dev);
  
  if (pci_get_revision(dev) != 0x01) {
    printk(KERN_ALERT "altera_driver: cannot find pci device\n");
    return -ENODEV;
  }

  pci_read_config_dword(dev, 0, &vendor);
  printk(KERN_ALERT "altera_driver: Found Vendor id: %x\n", vendor);

  resource = pci_resource_start(dev, 0);
  printk(KERN_ALERT "altera_driver: Resource start at bar 0: %lx\n", resource);

  hexport = ioremap_nocache(resource + 0XC000, 0x20);
  sw  = ioremap_nocache(resource + 0XC020, 0x20);
  greenLed = ioremap_nocache(resource + 0XC080, 0x20);
  redLed = ioremap_nocache(resource + 0XC060, 0x20);
  butt = ioremap_nocache(resource + 0XC040, 0x20);
  hexport2 = ioremap_nocache(resource + 0XC0A0, 0x20);

  return 0;
}

static void pci_remove(struct pci_dev *dev) {
  iounmap(hexport);
  iounmap(sw);
  iounmap(butt);
  iounmap(redLed);
  iounmap(greenLed);
  iounmap(hexport2);
}


//-- Global module registration

static int __init altera_driver_init(void) {
   int t = register_chrdev(MAJOR_NUMBER, "de2i150_altera", &file_opts);
   t = t | pci_register_driver(&pci_driver);

   if(t<0)
      printk(KERN_ALERT "altera_driver: error: cannot register char or pci.\n");
   else
     printk(KERN_ALERT "altera_driver: char+pci drivers registered.\n");

   return t;
}

static void __exit altera_driver_exit(void) {
  printk(KERN_ALERT "Goodbye from de2i150_altera.\n");

  unregister_chrdev(MAJOR_NUMBER, "de2i150_altera");
  pci_unregister_driver(&pci_driver);
}

module_init(altera_driver_init);
module_exit(altera_driver_exit);
