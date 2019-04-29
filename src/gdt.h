#ifndef INCLUDE_GDT_H
#define INCLUDE_GDT_H

/**
 * The GDT struct. This holds information on the global descriptor table,
 * describing memory segmentation. In the operating system we have the
 * following basic segments:
 *
 *  Index | Offset | Name                | Address range           | Type | DPL
 * -------+--------+---------------------+-------------------------+------+-----
 *    0   |  0x0   | null descriptor     |                         |      |
 *    1   |  0x08  | kernel code segment | 0x00000000 - 0xFFFFFFFF |  RX  | PL0
 *    2   |  0x10  | kernel data segment | 0x00000000 - 0xFFFFFFFF |  RW  | PL0
 *
 *
 * We also have four priviledge levels, specified by the DPL field. These are
 * laid out as follows:
 *  - PL0: kernel
 *  - PL1: operating system processes
 *  - PL2: hardware drivers
 *  - PL3: userspace applications
 */
struct gdt {
	unsigned int address;
	unsigned short size;
} __attribute__((packed));

/**
 * The method used to create the global descriptor table. This calls an assembly
 * method to load the kernel code segment as a descriptor table.
 */
void createGDT(void);

#endif /* INCLUDE_GDT_H */
