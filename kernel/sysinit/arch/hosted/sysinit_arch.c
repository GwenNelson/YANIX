#include <yanix/kmain.h>
#include <yanix/bootinfo.h>

int main(int argc, char** argv) {
	yanix_bootinfo_t bootinfo;
	kmain(bootinfo);
}
