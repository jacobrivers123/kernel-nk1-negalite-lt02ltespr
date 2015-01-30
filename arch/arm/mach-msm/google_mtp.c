#include <linux/module.h>
#include <linux/kobject.h>
#include "acpuclock.h"

void set_mtp_type(unsigned int val);
unsigned int get_mtp_type(void);

static ssize_t store_enable_google_mtp(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	unsigned int ret = -EINVAL;
	unsigned int value = 0;

	ret = sscanf(buf, "%u", &value);
	if (ret != 1)
		return -EINVAL;

	set_mtp_type(value);
	return count;
}

static ssize_t show_enable_google_mtp(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", get_mtp_type());
}

static struct kobj_attribute enable_google_mtp_attr =
	__ATTR(enable_google_mtp, 0666, show_enable_google_mtp, store_enable_google_mtp);

static struct attribute *acpuclock8930ab_attributes[] = {
	&enable_google_mtp_attr.attr,
	NULL,
};

static struct attribute_group acpuclock8930ab_attr_group = {
	.attrs = acpuclock8930ab_attributes,
	.name = "Negalite",
};

