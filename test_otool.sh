rm otool_diff ;
for f in /usr/lib/* /usr/bin/* obj/*
do
    echo $f
    echo $f >> otool_diff ;
    otool -dh $f  > /tmp/otool_a
    ./ft_otool -dh $f > /tmp/otool_b
    diff /tmp/otool_a /tmp/otool_b >> otool_diff
done