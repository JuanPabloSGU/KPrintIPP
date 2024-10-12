static int __init ipp_init(void);
static void __exit ipp_exit(void);
static int dev_open(struct inode *inode, struct file *file);
static int dev_release(struct inode *inode, struct file *file);
static ssize_t dev_read(struct file *file, char *buffer, size_t len, loff_t *offset);
static ssize_t dev_write(struct file *file, const char *buffer, size_t len, loff_t *offset);
