#ifndef __R2K_H
#define __R2K_H

static char *r2_devname = "r2k";

#define  R2_CLASS_NAME  "r2k"
static struct device *r2k_dev_ph;
static struct class *r2k_class;
static struct cdev *r2k_dev;
static dev_t devno;

#define ADDR_OFFSET(x)          (x & (~PAGE_MASK))

#define R2_TYPE 0x69
#define IOCTL_READ_KERNEL_MEMORY        0x1
#define IOCTL_WRITE_KERNEL_MEMORY       0x2
#define IOCTL_READ_PROCESS_ADDR         0x3
#define IOCTL_WRITE_PROCESS_ADDR        0x4
#define IOCTL_READ_PHYSICAL_ADDR        0x5
#define IOCTL_WRITE_PHYSICAL_ADDR       0x6
#define IOCTL_GET_PROC_MAPS             0x7
#define IOCTL_GET_KERNEL_MAP            0x8

struct r2k_data {
        int pid;
        unsigned long addr;
        unsigned long len;
        void __user *buff;
};

#define MAX_PHYS_ADDR	128

struct kernel_map_info {
	unsigned long start_addr;
	unsigned long end_addr;
	unsigned long phys_addr[MAX_PHYS_ADDR];
	int n_pages;
};

struct kernel_maps {
	int n_entries;
	int size;
};

struct r2k_map {
	struct kernel_maps kernel_maps_info;
	struct kernel_map_info *map_info;
};

extern int addr_is_writeable (unsigned long addr);
extern int addr_is_mapped (unsigned long addr);
extern int dump_pagetables (void);
extern int pg_dump (struct r2k_map *k_map);
#endif