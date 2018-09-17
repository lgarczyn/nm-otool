rm otool_diff ;
for f in /usr/bin/*
do
    echo $f
    echo $f >> otool_diff ;
    otool -t $f  > /tmp/a
    ./ft_otool $f > /tmp/b
    diff /tmp/a /tmp/b >> otool_diff
done