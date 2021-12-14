// PICHENOT REY

#include "sfs_low_level.h"

/////////////////
// misc functions

// count number of free blocks in volume
int sfs_count_free_blocks()
{
    // block_t* b;
    int nb = 0;
    for (int i = 0; i < DATA_SIZE; i++){
        // b = sfs_get_block(i);
        if (sfs_block_in_use(i)){
            nb++;
        }
    }
    return nb;
}

// counte number of free inodes in volume
int sfs_count_free_inodes()
{
    inode_t* inode;
    int nb = 0;
    for (int i = ROOT_INODE; i <NB_INODES;i++){
        inode = sfs_get_inode(i);
        // si l'inode est free
        if ((inode->nlinks)==0){
            nb++;
        }
    }
    return nb;
}

// get a data block number from an inode
int sfs_get_data_block_nb_from_inode(int nb, int block_idx)
{
    // TODO check block_idx is a valid block (wrt nd->size)
    inode_t* nd = sfs_get_inode(nb);
    int block_nb;

    if (0 <= block_idx && block_idx < NB_DIRECT_BLOCKS) {
        block_nb = nd->blocks[block_idx];
    } else {
        errno = EINVAL;
        return -1;
    }
    return block_nb;
}

// count used blocks inside an inode
int sfs_count_used_blocks_inode(int nb)
{
    inode_t* nd = sfs_get_inode(nb);
    return nd->size / BLOCK_SIZE + (nd->size % BLOCK_SIZE != 0);
}

////////////////
// regular files

// look for a free inode and use it for a new empty file that is inserted in
// directory with inode ``parent_nb``
int sfs_create_empty_file(int parent_nb, const char* name)
{
    // TODO: check that parent_nb is a directory???
    int inode_nb = sfs_find_free_inode();
    if (inode_nb < 0) {
        // errno = ENOSPC;
        return -1;
    }
    inode_t* nd = sfs_get_inode(inode_nb);
    nd->type = S_IFREG;
    nd->nlinks = 1;
    nd->size = 0;

    if (sfs_add_entry(parent_nb, name, inode_nb) < 0) {
        // we need to free the inode...
        nd->nlinks = 0;
        // errno = EBADF, ENAMETOLONG, ENOTDIR, EEXIST, ENOSPC
        return -1;
    }

    return inode_nb;
}

// deallocate a sequence of blocks from an inode
int deallocate_datablocks(int nb, int first_block, int last_block)
{
    inode_t* nd = sfs_get_inode(nb);

    int n;
    for (int i = first_block; i <= last_block; i++) {
        if (i < NB_DIRECT_BLOCKS) {
            // direct access
            sfs_free_block(nd->blocks[i]);
        } else {
            // indirect access
            n = i - NB_DIRECT_BLOCKS;
            sfs_free_block(nd->blocks[n]);
        }
    }

    if (first_block < NB_DIRECT_BLOCKS && last_block >= NB_DIRECT_BLOCKS) {
        sfs_free_block(nd->blocks[INDIRECT_BLOCKS]);
    }
    return 0;
}

// allocate a sequence of blocks (filled with 0) from an inode
int allocate_datablocks(int nb, int first_block, int last_block)
{
    int new_block_idx;
    inode_t* nd = sfs_get_inode(nb);
    int* indirect_blocks = NULL;

    int allocated_blocks = 0; // not including indirect block

    // we may need to allocate an address block
    if (first_block < NB_DIRECT_BLOCKS && NB_DIRECT_BLOCKS <= last_block) {
        new_block_idx = sfs_find_free_block();
        if (new_block_idx < 0) {
            return -1; // errno = ENOSPC
        }
        sfs_use_block(new_block_idx);
        block_t* b = sfs_get_block(new_block_idx);
        memset(*b, -1, BLOCK_SIZE * sizeof(int));
        nd->blocks[INDIRECT_BLOCKS] = new_block_idx;
    }

    // if we need the indirect blocks, define it here
    if (last_block >= NB_DIRECT_BLOCKS) {
        indirect_blocks = (int*)sfs_get_block(nd->blocks[INDIRECT_BLOCKS]);
    }
    int n;
    for (int i = first_block; i <= last_block; i++) {
        new_block_idx = sfs_find_free_block();
        sfs_use_block(new_block_idx);

        if (i < NB_DIRECT_BLOCKS) {
            // direct access
            nd->blocks[i] = new_block_idx;
        } else {
            // indirect access
            n = i - NB_DIRECT_BLOCKS;
            indirect_blocks[n] = new_block_idx;
        }
    }
    return allocated_blocks;
}

// change size of an inode:
//   - if ``length`` is less than the size, the blocks at the end are
//   deallocated
//   - if ``length`` is greater than the size, some 0 filled blocks are
//   allocated at the end
int sfs_truncate_inode(int nb, int length)
{
    inode_t* nd = sfs_get_inode(nb);

    if (length < nd->size) {
        // we need to free all the blocks at the end

        // first block to free: ceiling(length/BLOCK_SIZE)
        int first_block = length / BLOCK_SIZE + (length * BLOCK_SIZE != 0);

        // last block to free: floor(size/BLOCK_SIZE)
        int last_block = nd->size / BLOCK_SIZE;

        deallocate_datablocks(nb, first_block, last_block);

        nd->size = length;

    } else if (nd->size < length) {
        // we need to allocate a bunch of blocks at the end
        block_t* b;

        // first block to allocate: ceiling(size/BLOCK_SIZE)
        int first_block = nd->size / BLOCK_SIZE + (nd->size % BLOCK_SIZE != 0);

        // last block to allocate: floor(length/BLOCK_SIZE)
        int last_block = length / BLOCK_SIZE;

        // TODO deal with errors in allocate_datablocks (if less blocks than
        // requested were allocated)
        allocate_datablocks(nb, first_block, last_block);

        // block of first new byte
        int start_block = nd->size / BLOCK_SIZE;

        // block of last new byte
        int stop_block = length / BLOCK_SIZE;

        if (start_block == stop_block) {
            // we only need to put some 0 inside the block
            b = sfs_get_block(sfs_get_data_block_nb_from_inode(nb, start_block));
            int start = nd->size % BLOCK_SIZE;
            int stop = length % BLOCK_SIZE;
            memset(*b + start, -1, stop - start);
            nd->size = length;
        } else {
            // we need to pad the last actual block with zeros
            b = sfs_get_block(sfs_get_data_block_nb_from_inode(nb, start_block));
            int start = nd->size % BLOCK_SIZE;
            int stop = BLOCK_SIZE;
            memset(*b + start, 0, stop - start);

            // we add 0s at the beginning of the future last actual block
            b = sfs_get_block(sfs_get_data_block_nb_from_inode(nb, stop_block));
            stop = length % BLOCK_SIZE;
            memset(*b, 0, stop);
        }
    }
    nd->size = length;

    return nd->size;
}

// read some bytes from a single block inside an inode
int sfs_read_from_block(int nb, int block_idx, int offset, byte* buf, int size)
{
    block_t* b;

    if (offset + size > BLOCK_SIZE) {
        errno = EINVAL;
        return -1;
    }
    // we get the appropriate data block to read from
    int block_nb = sfs_get_data_block_nb_from_inode(nb, block_idx);
    if (block_nb < 0) {
        return -1;
    }
    b = sfs_get_block(block_nb);

    memcpy((byte*)buf, (byte*)b + offset, size);

    return size;
}

// read from an inode
int sfs_read_from_inode(int nb, int offset, void* buf, int nbyte)
{
    if (nb < ROOT_INODE || nb >= NB_INODES) {
        errno = EBADF;
        return -1;
    }
    if (offset < 0) {
        errno = EINVAL;
        return -1;
    }
    // the inode structure corresponding to n
    inode_t* nd = sfs_get_inode(nb);
    if (nd->type != S_IFREG) {
        errno = EISDIR;
        return -1;
    }

    int bytes_read = 0;     // number of bytes read from disk
    int nb_to_read = nbyte; // number of bytes to read from the current block

    int nb_current_block = offset / BLOCK_SIZE; // number of the block we're currently reading
                                                // from (relative to the inode table)
    int current_offset = offset % BLOCK_SIZE;   // current offset with respect to the current
                                                // bloc: it is either
    //    - offset % BLOCK_SIZE for the first read operation
    //    - 0 for the remaining read operations

    // adjust nbyte to stop at the end of the file
    nbyte = offset + nbyte > nd->size ? nd->size - offset : nbyte;

    while (1) {
        // if there are more than "BLOCK_SIZE" bytes to read, we'll need to
        // split the reading across several blocks
        // More precisely, given the current offset (either the original
        // offset, or 0), we decide how many bytes to read from the current
        // block...
        nb_to_read = (current_offset + nbyte) > BLOCK_SIZE ? BLOCK_SIZE - current_offset : nbyte;
        if (nb_to_read < 0) {
            break;
        }
        // we read the bytes we want from the data block
        // memcpy((byte *) buf + bytes_read, (byte *) b + current_offset,
        // nb_to_read);

        int nb_read = sfs_read_from_block(nb, nb_current_block, current_offset, (byte*)buf + bytes_read, nb_to_read);

        // FIXME if (nb_read < 0) {}

        bytes_read += nb_read; // increase number of bytes read from the disk
        nbyte -= nb_read;      // decrease number of remaining bytes to read
        current_offset = 0;    // from now on, the offset relative to the current
                               // block will be 0
        nb_current_block++;    // we'll need to read from the following block
                               // next...

        if (nb_read < nb_to_read) {
            return bytes_read;
        }
        if (nbyte == 0)
            // if no more bytes need to be read, we are finished!
            break;
    }

    return bytes_read;
}

// write some bytes to a single block inside an inode
// NOTE:
//   - the block is allocated if necessary...
//   - block_idx corresponds to the block number __in the file__ (0, 1, ...)
//     In particular, it cannot be an address block.
//   - offset corresponds to the offset __inside the block__ for the write operation
int sfs_write_to_block(int nb, int block_idx, int offset, const byte* buf, int size)
{
    inode_t* nd = sfs_get_inode(nb);
    block_t* b;

    if (block_idx > NB_DIRECT_BLOCKS + BLOCK_SIZE / (int)sizeof(int)) {
        // the file becomes too big!
        errno = EFBIG;
        return -1;
    }
    if (offset + size > BLOCK_SIZE) {
        errno = EINVAL;
        return -1;
    }

    int first_unused_block = nd->size / BLOCK_SIZE + (nd->size % BLOCK_SIZE != 0);
    if (block_idx >= first_unused_block) {
        if (sfs_truncate_inode(nb, block_idx * BLOCK_SIZE + offset + size) < 0) {
            return -1;
        }
        nd->size = block_idx * BLOCK_SIZE + offset + size;
    }

    if (0 <= block_idx && block_idx < NB_DIRECT_BLOCKS) {
        // direct access block
        b = sfs_get_block(nd->blocks[block_idx]);
    } else {
        errno = EINVAL;
        return -1;
    }

    // we can at last write the bytes we want to the data block!
    memcpy((byte*)b + offset, (byte*)buf, size);
    return size;
}

// write to an inode
int sfs_write_to_inode(int nb, int offset, const void* buf, int nbyte)
{
    if (nb < ROOT_INODE || nb >= NB_INODES) {
        errno = EBADF;
        return -1;
    }
    if (offset < 0) {
        errno = EINVAL;
        return -1;
    }
    // TODO: if nb is not a regular file ??? EBADF???

    // the inode structure corresponding to n
    inode_t* nd = sfs_get_inode(nb);

    // if the offset is beyond the end of file, we extend the file with
    // truncate
    // TODO extend to offset + nbyte to simplify allocating new blocks???
    if (offset > nd->size) {
        if (sfs_truncate_inode(nb, offset) < 0)
            return -1;
    }

    int bytes_written = 0;   // number of bytes written to disk
    int nb_to_write = nbyte; // number of bytes to write to the current block

    int nb_current_block = offset / BLOCK_SIZE; // number of the block we're currently writing
                                                // to (relative to the inode table)
    int current_offset = offset % BLOCK_SIZE;   // current offset with respect to the current
                                                // bloc: it is either
    //    - offset % BLOCK_SIZE for the first write operation
    //    - 0 for the remaining write operations

    while (1) {
        // if there are more than "BLOCK_SIZE" bytes to write, we'll need to
        // split the writing across several blocks
        // More precisely, given the current offset (either the original
        // offset, or 0), we decide how many bytes to write to current
        // block...
        nb_to_write = (current_offset + nbyte) > BLOCK_SIZE ? BLOCK_SIZE - current_offset : nbyte;

        int nb_written = sfs_write_to_block(nb, nb_current_block, current_offset, (byte*)buf + bytes_written, nb_to_write);
        // TODO if (nb_written < 0) { }

        bytes_written += nb_written; // increase number of bytes written to the disk
        nbyte -= nb_written;         // decrease number of remaining bytes to write
        current_offset = 0;          // from now on, the offset relative to the current
                                     // block will be 0
        nb_current_block++;          // we'll need to write inside the following block
                                     // next...

        if (nd->size < offset + bytes_written) {
            nd->size = offset + bytes_written; // increase size accordingly
        }

        if (nbyte == 0)
            // if no more bytes need to be written, we are finished!
            break;
    }

    return bytes_written;
}

// free data blocks from an inode corresponding to a regular file
int sfs_deallocate_inode(int nb)
{
    inode_t* nd = sfs_get_inode(nb);

    // last block to free: floor(size/BLOCK_SIZE)
    int last_block = nd->size / BLOCK_SIZE + (nd->size % BLOCK_SIZE != 0) - 1;

    deallocate_datablocks(nb, 0, last_block);

    nd->nlinks = 0;
    return 0;
}
//let me go under a bus. Please.  
//
//                    (Sure Man )
//                    |__ )  
//       %%% %%%%%%%            |#|
//     %%%% %%%%%%%%%%%        |#|####
//   %%%%% %         %%%       |#|=#####   
//  %%%%% %   @    @   %%      | | ==####
// %%%%%% % (_  ()  )  %%      | |    ===##
// %%  %%% %  \_    | %%       | |       =##
// %    %%%% %  ubuntu  %%     | |         ==#
//       %%%% %%%%%%%%%        | |           V

// FIXME: TODO: should take the filename as well
int sfs_unlink_inode(int nb, const char* name, int parent_nb)
{
    inode_t* nd = sfs_get_inode(nb);
    if (nd->type != S_IFREG) {
        errno = EPERM;
        return -1;
    }
    if (sfs_remove_entry(parent_nb, name) < 0) {
        // errno = EBADF, ENAMETOOLONG, ENOTDIR, ENOENT
        return -1;
    }
    
    nd->nlinks = nd->nlinks - 1;

    if (nd->nlinks == 0){
        sfs_deallocate_inode(nb);
    }

    return 0;
}

// add a physical link to an existing inode inside a directory
int sfs_link_inode(int parent_nb, int nb, const char* name)
{
    if (sfs_add_entry(parent_nb, name, nb) < 0) {
        // errno = EBADF, ENAMETOOLONG, ENOTDIR, ENOENT
        return -1;
    }
    // À FAIRE
    inode_t* nd = sfs_get_inode(nb);

    nd->nlinks++;

    return 0;
}

//////////////
// directories

// add an entry for inode ``n`` with name ``name`` inside inode ``dir_n``
int sfs_add_entry(int dir_n, const char* name, int inode_nb)
{
    if (dir_n < ROOT_INODE || dir_n >= NB_INODES) {
        errno = EBADF;
        return -1;
    }
    if (strlen(name) > SFS_NAME_MAX) {
        errno = ENAMETOOLONG;
        return -1;
    }

    inode_t* dir = sfs_get_inode(dir_n);
    if (dir->type != S_IFDIR) {
        errno = ENOTDIR;
        return -1;
    }

    block_t* b;
    dir_entry_t* entries;

    int idx = -1;  // possible index for the new entry
    int found = 0; // number of entries with same name found

    int i, k;

    for (i = 0; i < dir->size / BLOCK_SIZE; i++) {
        b = sfs_get_block(dir->blocks[i]);
        entries = (dir_entry_t*)b;
        for (k = 0; k < ENTRIES_PER_BLOCK; k++) {
            if ((entries[k].inode_nb == 0) && (idx == -1)) {
                idx = i * ENTRIES_PER_BLOCK + k;
            }

            if ((entries[k].inode_nb > 0) && (0 == strcmp(name, entries[k].name))) {
                found += 1;
            }
        }
    }

    // there shouldn't be more than 1 entry with the same name!
    assert(found < 2);

    // if there already is an entry with the name ``name``, abort
    if (found == 1) {
        errno = EEXIST;
        return -1;
    }

    if (idx == -1) {
        // if we haven't found an index for the new entry, we need to allocate
        // one more block for new entries
        if (dir->size >= NB_DIRECT_BLOCKS * BLOCK_SIZE) {
            // the directory cannot get more entries!
            errno = EMLINK;
            return -1;
        }
        // look for an unused block, and use it as a new entry block
        int nb = sfs_find_free_block();
        if (nb < 0) {
            errno = ENOSPC;
            return -1;
        }
        sfs_use_block(nb);
        entries = (dir_entry_t*)sfs_get_block(nb);
        for (i = 0; i < ENTRIES_PER_BLOCK; i++) {
            entries[i].inode_nb = 0;
        }
        dir->blocks[dir->size / BLOCK_SIZE] = nb;
        dir->size += BLOCK_SIZE;

        // define the corresponding index
        idx = dir->size / BLOCK_SIZE - 1;
    }
    // we can now put the entry...
    entries = (dir_entry_t*)sfs_get_block(dir->blocks[idx / ENTRIES_PER_BLOCK]);
    entries[idx % ENTRIES_PER_BLOCK].inode_nb = inode_nb;
    strncpy(entries[idx % ENTRIES_PER_BLOCK].name, name, SFS_NAME_MAX + 1);
    entries[idx % ENTRIES_PER_BLOCK].name[SFS_NAME_MAX] = 0;
    return idx;
}

// remove entry from a directory given by its inode
int sfs_remove_entry(int dir_n, const char* name)
{
    if (dir_n < ROOT_INODE || dir_n >= NB_INODES) {
        errno = EBADF;
        return -1;
    }
    inode_t* dir = sfs_get_inode(dir_n);
    if (dir->type != S_IFDIR) {
        errno = ENOTDIR;
        return -1;
    }

    block_t* b;
    dir_entry_t* entries;

    int i, k;

    for (i = 0; i < dir->size / BLOCK_SIZE; i++) {
        b = sfs_get_block(dir->blocks[i]);
        entries = (dir_entry_t*)b;
        for (k = 0; k < ENTRIES_PER_BLOCK; k++) {
            if (strcmp(entries[k].name, name) == 0) {
                entries[k].inode_nb = 0;
                return 0;
            }
        }
    }
    // if we reached this point, the dir did not contain name
    errno = ENOENT;
    return -1;
}

// find an entry inside a directory (given by its inode) and returns the
// corresponding inode number
int sfs_find_entry(int dir_nb, const char* name)
{
    if (dir_nb < ROOT_INODE || dir_nb >= NB_INODES) {
        errno = EBADF;
        return -1;
    }
    inode_t* dir = sfs_get_inode(dir_nb);
    if (dir->type != S_IFDIR) {
        errno = ENOTDIR;
        return -1;
    }
    if (strlen(name) > SFS_NAME_MAX) {
        errno = ENAMETOOLONG;
        return -1;
    }
    int nb = -1;
    block_t* b;
    dir_entry_t* entries;
    for (int i = 0; i < dir->size / BLOCK_SIZE; i++) {
        b = sfs_get_block(dir->blocks[i]);
        entries = (dir_entry_t*)b;
        for (int k = 0; k < ENTRIES_PER_BLOCK && nb < 0; k++) {
            if ((entries[k].inode_nb > 0) && (0 == strcmp(name, entries[k].name))) {
                nb = entries[k].inode_nb;
            }
        }
    }
    if (nb < 0)
        errno = ENOENT;
    return nb;
}

// initializes a new directory by putting the "."->``self`` and
// ".."->``parent`` inodes
int sfs_dir_init(int parent, int self)
{
    // look for an unused block, and use it as a new entry block
    int nb = sfs_find_free_block();
    if (nb < 0)
        return -1; // error: ENOSPC
    sfs_use_block(nb);

    dir_entry_t* entries = (dir_entry_t*)sfs_get_block(nb);
    for (int i = 0; i < ENTRIES_PER_BLOCK; i++) {
        entries[i].inode_nb = 0;
    }
    entries[0].inode_nb = self;
    strcpy(entries[0].name, ".");

    entries[1].inode_nb = parent;
    strcpy(entries[1].name, "..");

    return nb;
}

// create a new directory inside an inode
int sfs_mkdir_inode(int parent_nb, const char* name)
{
    int inode_nb = sfs_find_free_inode();
    if (inode_nb < 0) {
        // errno = ENOSPC;
        return -1;
    }
    inode_t* nd = sfs_get_inode(inode_nb);
    nd->type = S_IFDIR;
    nd->nlinks = 2;

    // look for an unused block, and use it as a new entry block
    int nb = sfs_dir_init(parent_nb, inode_nb);
    if (nb < 0) {
        // errno = ENOSPC;
        return -1;
    }

    nd->blocks[0] = nb;
    nd->size = BLOCK_SIZE;

    if (sfs_add_entry(parent_nb, name, inode_nb) < 0) {
        // we need to free the inode...
        nd->nlinks = 0;
        // errno = EBADF, ENAMETOLONG, ENOTDIR, EEXIST, ENOSPC
        return -1;
    }

    inode_t* parent = sfs_get_inode(parent_nb);
    parent->nlinks++;

    return inode_nb;
}

// free the data block from an inode corresponding to an empty directory
int sfs_unlink_dir(int nb)
{
    inode_t* nd = sfs_get_inode(nb);
    block_t* b;
    dir_entry_t* entries;

    for (int i = 0; i < nd->size / BLOCK_SIZE; i++) {
        b = sfs_get_block(nd->blocks[i]);
        entries = (dir_entry_t*)b;
        for (int k = 0; k < ENTRIES_PER_BLOCK; k++) {
            if (entries[k].inode_nb > 0 && 0 != strcmp(entries[k].name, ".") && 0 != strcmp(entries[k].name, "..")) {
                errno = ENOTEMPTY;
                return -1;
            }
        }
    }
    return 0;
}

// remove a directory
int sfs_unlink_dir_inode(int dir_n, const char* dir_name, int parent_nb)
{
    inode_t* nd = sfs_get_inode(dir_n);
    if (nd->type != S_IFDIR) {
        errno = ENOTDIR;
        return -1;
    }

    if (sfs_unlink_dir(dir_n) < 0) {
        return -1;
    }

    if (sfs_remove_entry(parent_nb, dir_name) < 0) {
        return -1;
    }
    nd->nlinks = 0;
    return 0;
}

/////////////////
// symbolic links

// look for a free inode, and make it into a symbolic link to ``path``
// return the inode number that was used...
int sfs_writelink_inode(const char* target)
{
    int nb = sfs_find_free_inode();
    if (nb < 0) {
        return -1;
    }

    inode_t* nd = sfs_get_inode(nb);
    nd->type = S_IFLNK;
    nd->nlinks = 1;

    // À FAIRE

    return nb;
}

int sfs_symlink_inode(int parent_nb, const char* target, const char* name)
{
    int nb = sfs_writelink_inode(target);
    if (nb < 0) {
        return -1;
    }
    inode_t* nd = sfs_get_inode(nb);

    if (sfs_add_entry(parent_nb, name, nb) < 0) {
        // we need to free the inode...
        nd->nlinks = 0;
        if (nd->size > 0) {
            sfs_free_block(nd->blocks[0]);
        }
        // errno = EBADF, ENAMETOLONG, ENOTDIR, EEXIST, ENOSPC
        return -1;
    }
    return 0;
}

// get the target of an inode corresponding to a symbolic link
int sfs_readlink_inode(int nb, char* buf, int bufsize)
{
    inode_t* nd = sfs_get_inode(nb);
    if (nd->type != S_IFLNK) {
        errno = EINVAL;
        return -1;
    }

    // À FAIRE
    return 0;
}

///////
// path

// decomposes a path and return the corresponding inode number
int localize_rec(int nb, const char* path, int counter)
{
    // TODO error ELOOP
    if (counter < 0) {
        errno = ELOOP;
        return -1;
    }

    int new_nb;
    char path_copy[SFS_PATH_MAX + 1];
    strncpy(path_copy, path, SFS_PATH_MAX + 1);
    char *component, *next_component;
    char* strtok_ptr;

    component = strtok_r(path_copy, "/", &strtok_ptr);

    while (1) {
        if (component == NULL) {
            break;
        }
        next_component = strtok_r(NULL, "/", &strtok_ptr);
        if (strlen(component) > SFS_NAME_MAX) {
            errno = ENAMETOOLONG;
            return -1;
        }

        new_nb = sfs_find_entry(nb, component);
        if (new_nb == -1) {
            // errno = EBADF, ENOTDIR, ENOENT, ENAMETOOLONG
            return -1;
        }
        inode_t* nd = sfs_get_inode(new_nb);
        if (nd->type == S_IFLNK && next_component != NULL) {
            char buf[SFS_PATH_MAX];
            if (sfs_readlink_inode(new_nb, buf, SFS_PATH_MAX) < 0) {
                // TODO errno???
                return -1;
            }
            new_nb = localize_rec(nb, buf, counter - 1);
            if (nb < 0) {
                // TODO errno ???
                return -1;
            }
        }
        nb = new_nb;
        component = next_component;
    }
    return nb;
}

int sfs_localize(const char* path)
{
    // TODO: deal with relative path
    if (path[0] != '/') {
        return -1;
    }

    return localize_rec(ROOT_INODE, path, 256);
}

// vim: foldmethod=syntax textwidth=1000
