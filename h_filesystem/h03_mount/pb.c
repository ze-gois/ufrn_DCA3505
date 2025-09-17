#define FUSE_USE_VERSION 31
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fuse.h>

static int mifs_getattr(const char *path, struct stat *stbuf,
                        struct fuse_file_info *fi)
{
        if (strcmp(path, "/teste.txt") != 0) {
                return -ENOENT;
        }

        *stbuf = (struct stat) {
                .st_mode = S_IFREG | 0444,
                .st_nlink = 1,
                .st_size = 10,
        };

        return 0;
}

int main(int argc, char **argv)
{
        if (argc != 3) { 
                fprintf(stderr, "Uso: %s <imagem> <diretorio>\n", argv[0]);
                exit(1);
        }

        static const struct fuse_operations mifs_ops = {
                .getattr = mifs_getattr,
        };
        struct fuse_args args = FUSE_ARGS_INIT(0, NULL);
        fuse_opt_add_arg(&args, argv[0]);
        fuse_opt_add_arg(&args, argv[2]);
        return fuse_main(args.argc, args.argv, &mifs_ops, NULL);
}
