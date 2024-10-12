static int __init printer_init(void);
static void __exit printer_exit(void);
static ssize_t write_pdl(struct file *file, const char *buffer, size_t len, loff_t *offset);
