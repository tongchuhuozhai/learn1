struct globalmem_dev {
	struct cdev cdev;	
	char mem[100];
};
