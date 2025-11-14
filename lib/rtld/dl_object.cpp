#include "private.h"

dl_pool<sizeof(dl_object)> _dl_object_pool;
dl_pool<sizeof(dl_object_dep)> _dl_object_dep_pool;

void *dl_object::operator new(unsigned long) {
    return _dl_object_pool.alloc();
}
void dl_object::add_dependency(dl_object *dep) {
    this->dep = new dl_object_dep(this->dep, dep);
}

void *dl_object_dep::operator new(unsigned long) {
    return _dl_object_dep_pool.alloc();
}
