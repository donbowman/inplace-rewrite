/*
Copyright 2017 Don Bowman

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void
doFile(int verbose, int progress, const char *file)
{
    char chunk[16 * 1024];
    int fdi, fdo;
    int n;
    if (verbose)
        printf("Processing '%s'\n", file);
    fdi = open(file, O_RDONLY, 0);
    if (fdi < 0)
    {
        strerror_r(errno, chunk, sizeof(chunk));
        fprintf(stderr, "Error processing in '%s' : %s\n", file, chunk);
        exit(1);
    }
    fdo = open(file, O_WRONLY, 0);
    if (fdo < 0)
    {
        strerror_r(errno, chunk, sizeof(chunk));
        close(fdi);
        fprintf(stderr, "Error processing out '%s' : %s\n", file, chunk);
        exit(1);
    }
    do
    {
        n = read(fdi, chunk, sizeof(chunk));
        if (n > 0)
        {
            if (progress)
            {
                printf(".");
                fflush(stdout);
            }
            write(fdo, chunk, n);
        }
    } while (n > 0);
    if (progress)
        printf("\n");
        fflush(stdout);
    close(fdi);
    close(fdo);
}

int
main(int argc, char **argv)
{
    int opt;
    int verbose = 0;
    int progress = 0;

    while (( opt = getopt(argc, argv, "vp")) != -1)
    {
        switch (opt)
        {
            case 'v': verbose = 1; break;
            case 'p': progress = 1; break;
            default:
                fprintf(stderr, "Usage: %s [-v] [-[] file [file...]\n", argv[0]);
                exit(1);
        }
    }
    for (opt = optind; opt < argc; opt++)
    {
        doFile(verbose, progress, argv[opt]);
    }
    exit(0);
}



