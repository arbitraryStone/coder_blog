#!/bin/sh

if [ ! -d bin/module ]
then
    mkdir bin/module
else
    unlink bin/blog
    unlink bin/module/libblog.so
fi

cp stone/bin/stone bin/blog
cp lib/libblog.so bin/module/
cp stone/bin/orm bin/orm
cp -r stone/bin/conf bin/conf
